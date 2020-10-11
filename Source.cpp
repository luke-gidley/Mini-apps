#include <iostream>  //These import the neccassary libaries for the project.
#include <time.h>
#include <string>
#include <chrono>
#include <Windows.h>
#include <limits>
#include <sstream>
#include <assert.h>


using namespace std;
using namespace std::chrono;

//below is prototyping for the functions/methods.
void menu();
bool countingGame();
void keepCounting();
void numberConversion();
void denaryToBinary(int number);
int numberSize(int number, int size);
int mostSigCalc(int size, int type);
void displayArray(const char data[], int size);
void denaryToHexadecimal(int number);
void binaryToDecimal();
void HexadecimalToDenary();
void UPCCalculator();
void dataEntry(char data[], string numberToChange, const int MAX_LENGTH, int toEnter);
void arrayFiller(char data[], int fill);
int findNumbers(const char data[], const int MAX_NUMBER, bool even);
void UPCCHecker();

//This is the menu function, I tested it through the use of entering the correct inputs first, then when they all worked I tested what would happen if I put in the wrong input.
//This is what the default handles, with it returning you to the beginning of the menu.
//It is then wrapped in a nice do-while loop so that everytime an app ends it will reenter the loop and ask again.

void menu()  //menu function, returns a boolean to allow for the game loop to be exited, when the menu returns the gameloop closes.
{
	bool quit = false;  //this boolean is to define when the menu has been exited.
	int choice;  //integer variable for the users choice.

	do {

		cout << "\nmini apps";										//displays the menu with all options.
		cout << "\n------------------------";
		cout << "\nPlease select an option:";
		cout << "\n 1) Keep Counting Game";
		cout << "\n 2) Number Conversion Tool";
		cout << "\n 3) Universal Product Code (UPC) Calculator";
		cout << "\n 4) Universal Product Code (UPC) Checker";
		cout << "\n 9) Quit\n";
		cout << "\n Please enter an option: ";
		
		
		cin >> choice;
		cin.clear();
		cin.ignore(10000, '\n');


		switch (choice)
		{
		case 1:			//switch statement depending on what choice is made.
		{
			keepCounting(); break;
		}
		case 2:
		{
			numberConversion(); break;
		}
		case 3:
		{
			UPCCalculator(); break;
		}
		case 4:
		{
			UPCCHecker(); break;
		}
		case 9:
		{
		quit = true; break;
		}
		default:
		{
		cout << "\ninvalid input";

		}
		}		
	} while (quit == false);   // do-while loop, while the program has not been exited, keep asking what it is that is wanted.
}

//three methods/functions below are for the counting game.

//This is the game loop for the countingGame.
//It is a simple for loop iterating through the amount of questions asked.
//It will generate a random number to be added to the previous answer, it also generates a random number to decide whether to add or subtract, with the possibility of going into the negatives.
//Every iteration it will check if the given answer and actual answer are the same using a different function, if they aren't it will end the game and tell you the correct answer.
//If you get it right the answer will be the first number of the next question and if you get everything right it will display the time taken.
//I tested it by purposely getting questions wrong, timing myself, and putting in invalid inputs.

bool countingGame()
{
	int value1 = (rand() % 10) +1;
	int userValue;
	bool correct;
	
	for (int i = 0; i < 8; i++)
	{
		int value2 = (rand() % 10) + 1;
		int addOrSub = rand() % 2;
		if (addOrSub == 0) // if it is 0 it adds.
		{
			
			cout << "\nQuestion " << i+1 << " " << value1 << "+" << value2 << ":";
			value1 = value1 + value2;
			cin >> userValue;
			correct = (userValue==value1);

		}
		else // no other option for the variable to take so we minus here.
		{
			cout << "\nQuestion " << i+1 << " " << value1 << "-" << value2 << ":";
			value1 = value1 - value2;
			cin >> userValue;
			correct = (userValue==value1);
		}
		if (!correct)
		{
			cout << "wrong!\n The correct answer was: " << value1;
			return false;
		}
	}
	return true;
}


//This is the starting function for the counting game, it has a do while loop waiting for an enter press, but needs a 2 second pause to stop it using the one from the menu.
//I tested this by clicking enter as quick as possible, along with timing the time to complete the quiz


void keepCounting()
{
	

	cout << "\nYou will be presented with 8 addition questions.\nAfter the first question, the left hand operand is the result of the previous addition.\n";
	cout << "Press enter to start";
	system("pause");
	auto start = high_resolution_clock::now();	//Grabs the clock at its current point.
	bool won = countingGame();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start); // After both grabs of the clock, it takes the start from the end to find the time taken. 
	if (won)
	{
		cout <<"\nYou answered all the questions in: "  << duration.count() << " seconds";
	}
}


// next eight methods/functions are for the number conversion tool.

//this method is the menu for the conversion tool.
//It controls which converter you want to use, along with allowing you to covert multiple numbers by asking you at the end.
//I tested it by giving it wrong inputs, which the default handles.
//It calls the required functions depending on which is chosen.
//It has a nested while loop to allow you to use it again.

void numberConversion()		
{
	int number;			//these variables are needed from the beginning and to be in a large scope.
	int choice;
	bool done = false;
	bool check = false;
	char anotherAttempt;


	do {											//this is the menu loop.
		cout << "Number Conversion Tool";
		cout << "\n 1) Decimal converter";
		cout << "\n 2) Binary converter";
		cout << "\n 3) Hexadecimal converter";
		cout << "\n Please choose an option: ";
		cin >> choice;
		switch (choice)								//Switch statement for the menu. 
		{
		case 1:
		{
			cout << "\nPlease enter a decimal number: ";
			cin >> number;
			denaryToBinary(number);
			denaryToHexadecimal(number);
			break;
		}
		case 2:
			binaryToDecimal(); break;
		case 3:
			HexadecimalToDenary();	break;
		default:
			cout << "\nInvalid Input"; break;		
		}
		do {																	// this loop is nested inside the other one to check if you want to convert another number or not.
			cout << "\nDo you want to convert another number? (Y/N) : ";
			cin >> anotherAttempt;
			if (anotherAttempt == 'N' || anotherAttempt == 'n')
			{
				done = true;
				check = true;
			}
			else if (anotherAttempt == 'Y' || anotherAttempt == 'y')
				check = true;
			else
				cout << "Invalid Input";
		} while (!check);
	} while (!done);
}    

//This method converts decimal numbers to binary numbers. 
//It does this with a set length of an array of up to 64, even though this will not ever be reached as a 64bit binary number is bigger than what an int can hold.
//It uses the numberSize function to work out how long the number will be.
//It uses the mostSigCalc function to work out what the most significant bit at each iteration is.

void denaryToBinary(int number)		
{
	const int MAX_NUMBER = 64;				// this sets the max amount of space 
	char digits[MAX_NUMBER];
	int size = numberSize(number, 2) - 1;
	int mostSig = mostSigCalc(size, 2);
	for (int i = 0; i < size + 1 && i < MAX_NUMBER; i++)		// this for loop creates the array that needs to be printed by the index array function.
	{
		if (mostSig <= number)
		{
			digits[i] = '1';
			number = number - mostSig;
		}
		else
		{
			digits[i] = '0';
		}
		mostSig /= 2; 
	}
	cout << "\nBinary: ";
	displayArray(digits, size);
}  

//This function calculates the amount of digits for the number in question.
//If you pass in 2 as the type it will return the amount of coloumns for the binary number, if you pass in 16 it will return the amount of coloumns for a hex number.

int numberSize(int number, int type)	
{
	int baseTwoSize = 1;
	while (number > 1)
	{
		number = number / type;
		baseTwoSize += 1;
	}
	return baseTwoSize;
}

//This calculates the most significant bit, aka the one furthest to the left.
//The reason for this is it allows me to have a base number to compare to for each coloumn which is then halved.
//In the same way as the numberSize function, it requires an iput of the type of number you want, but also requires the amount of coloumns.
//It needs the amount of coloumns as it is doing the type to the power of the size.

int mostSigCalc(int size, int type)		
{
	int mostSig = 1;
	for (int i = 0; i < size; i++)
		mostSig *= type;
	return mostSig;
}

void displayArray(const char data[], int size)	// this function prints the array, the name is perfect.	
{
	for (int i = 0; i < size+1; i++)
		cout << data[i];
}

//This method converts a decimal number to a hex number.
//It does this by doing the modulus of the number, and depending on the remainer will either append the number to the string, or it will choose which letter needs to be appended to the string.
//It then reverses the string as it has created it backwards.
//It was tested in context by passing denary numbers into it, then seeing what it threw out, which I would then adjust to make it work, with different new numbers and the old ones.

void denaryToHexadecimal(int number)
{
	int size = numberSize(number, 16) - 1;
	int currentDigit;
	string hex;
	for (int i = 0; i < size; i++)
	{
		currentDigit = number % 16;		// Takes the mod of the number to then add to the string.
		number = number / 16;		    // Prepares the number for the next coloumn.

		switch (currentDigit)
		{
		case 10:
			hex.append("A"); break;
		case 11:
			hex.append("B"); break;
		case 12:
			hex.append("C"); break;
		case 13:
			hex.append("D"); break;
		case 14:
			hex.append("E"); break;
		case 15:
			hex.append("F"); break;
		default:
			 hex.append(to_string(currentDigit)); break;
		}
		}

	reverse(hex.begin(), hex.end());	//finds the beggining and end of the string, then reverses between them.
	cout << "\nHexadecimal: " << hex;
}

//this method converts binary to decimal.
//this is done by taking the input as a string, then iterating through it.
//before iterating it will find the most significant number.
//it iterates through the amount of coloumns that are required.
//on each iteration it checks if it is a 1, if it is it adds whatever the current most signifcant bit is to the total, then outside of the if check divides the most signifcant bit by 2.

void binaryToDecimal()		
{
	string number;	//taken as a string as it allows for much easier manipulation.
	int total = 0;
	bool valid = false;
	do {
		cout << "enter a binary number: ";
		cin >> number;
		for (int i = 0; i < number.length(); i++)
		{
			if (number.at(i) > '1')
			{
				cout << "\nInvalid Input";
				break;
			}
		}
		valid;
		
	} while (!valid);
	int mostSig = mostSigCalc(number.length()-1, 2);
	
	for (int i = 0; i < number.length(); i++)
	{
		if (number.at(i) == '1')	
		{
			total = total + mostSig;
		}
		mostSig /= 2;
	}
	cout << "Decimal: " << total;
	denaryToHexadecimal(total);  // this is then called to change the number further to hex.
}

//this method converts from hex to decimal.
//It does this through iterating through the input taken as a string.
//It then checks which character was entered, depending on whether it is a capital, lowercase, or just a number.
//Depending on that it will choose which branch to use to calculate the value.
//It was tested through putting many different hex numbers in. 

void HexadecimalToDenary() 
{
	string hexCode;
	int total = 0;
	cout << "enter a hex number: ";
	cin >> hexCode;
	char ASCIItoCovert;
	int ASCIICoverted;

	for (int i = 0; i < hexCode.length(); i++)
	{
		ASCIItoCovert = hexCode.at(i);

		char x = hexCode.at(i);
		if (x >= 'A' && x <= 'F')
		{
			ASCIICoverted = ASCIItoCovert - 55;
		}
		else if (x >= 'a' && x <= 'f')
		{
			ASCIICoverted = ASCIItoCovert - 87;
		}
		else
			ASCIICoverted = ASCIItoCovert - 48;

		total = total + ((mostSigCalc(hexCode.length() - i, 16) * ASCIICoverted));
	}
	total /= 16;
	cout << "decimal number: " << total;
	denaryToBinary(total);
}

//this method takes an input, and creates the final digit of the UPC from it.
//It does this by first assigning the input to an array, filling up any slots before it.
//It then does the calculation with the use of an extra function, then adds the result to the end of the array.
//When testing I would calculate the number before hand, then put the number in. Some adjustments were made, along with the passing in of an even bool to tell what type of number it wants.

void UPCCalculator()
{
	bool valid = false;
	int number;
	const int MAX_LENGTH = 7;
	char digits[MAX_LENGTH];
	int finalDig;
	bool done = false;
	char anotherAttempt;
	cout << "This calculator will take a 6-digit product code\nand generate a trailing 7th check digit to produce\nthe final 7-digit UPC.\n";
	do {
		do {

			cout << "Please give a number";
			cin >> number;
			string numberToChange = to_string(number);

			if (numberToChange.length() < 7)
				valid = true;

			arrayFiller(digits, 6 - numberToChange.length());
			dataEntry(digits, numberToChange, MAX_LENGTH, 6 - numberToChange.length()); 

		} while (!valid);
		finalDig = ((3 * (findNumbers(digits, MAX_LENGTH, false)) + findNumbers(digits, MAX_LENGTH, true)) % 10);
		if (finalDig == 0)
			digits[6] = '0';
		else
			digits[6] = (10 - finalDig) + 48;
		cout << "\nUPC number: ";
		displayArray(digits, MAX_LENGTH - 1);
		cout << "\n Do you want to check another number? (Y/N): ";
		cin >> anotherAttempt;
		if (anotherAttempt == 'N' || anotherAttempt == 'n')
			done = true;
		else if (anotherAttempt == 'Y' || anotherAttempt == 'y')
			done = false;
		else
			cout << "Invalid Input";
	} while (!done);
}

//This method adds the data to array, at the point after it has had the zeros put at the beginning.
//Tested through checking with breakpoints whats been put into the array.

void dataEntry(char data[], string numberToChange, const int MAX_LENGTH, int toEnter)
{
	int i = 0;
	for (toEnter; toEnter < MAX_LENGTH-1; toEnter++)
	{
		data[toEnter] = numberToChange.at(i);
		i++;
	}
}

//This method fills the beginning of an array with zeros.
//Tested by passing in arrays with varying amounts of zeros required.

void arrayFiller(char data[], int fill)
{
	for (int i = 0; i < fill; i++)
	{
		data[i] = '0';
	}
}

//This function calculates the number for the calculator.
//It does this by use of a for loop, then through checks, finds if the current number is even or odd, what the passed in even or odd check is and if the running total is even or odd.
//It does this by taking the values and doing the mod of them, then depending on output it will process it with the ASCII table as all passed in items are chars.
//Tested by passing in numbers to just add together, lead to the even or odd bool.

int findNumbers(const char data[], const int MAX_NUMBER, bool even)
{
	int total = 0;
	for (int i = 0; i < MAX_NUMBER - 1; i++)
	{
		if ((data[i] - 48) % 2 == 0 && total % 2 == 0 && even == true)
			total = total + data[i] - 48;
		else if (even == false && (data[i] - 48) % 2 == 1)
			total = total + data[i] - 48;
	}
	return total;
}

//Very similar to the calculator, but with some differences including it needs a 7 length input and nothing else, it also does the same calculation but then compares it to the last digit of the input.
//It then tells you whether or not the UPC is valid by comparing the given number to the calculated one, then asks if you want to check another number.
//It was tested though me knowing what I wanted as the output from multiple numbers, then I would check this against what the method gave me.

void UPCCHecker()
{
	string input;
	char anotherAttempt;
	const int MAX_LENGTH = 7;
	char digits[MAX_LENGTH];
	bool valid = false;
	bool done = false;
	int finalDig = 0;
	do {
		do {
			cout << "\nPlease enter the number to be checked: ";
			cin >> input;
			if (input.length() == 7)
			{
				valid = true;
			}
			else
				cout << "invalid input";
		} while (!valid);

		for (int i = 0; i < 7; i++)
		{
			digits[i] = input.at(i);
		}

		finalDig = ((3 * (findNumbers(digits, 7, false)) + findNumbers(digits, 7, true)) % 10);
		if (finalDig > 0)
			finalDig = 10 - finalDig;
		if (finalDig == (digits[6] - 48))
			cout << "\nUPC is valid";
		else
			cout << "\nUPC is not valid";
		
		cout << "\n Do you want to check another number? (Y/N): ";
		cin >> anotherAttempt;
			
		if (anotherAttempt == 'N' || anotherAttempt == 'n')
		{
			done = true;	
		}
		else if (anotherAttempt == 'Y' || anotherAttempt == 'y')
		{
			continue;
		}
		else
			cout << "Invalid Input";

			
	} while (!done);
}



int main()
{
	srand((int) time(NULL));
	menu(); // starts the app.
	cout << "\nBye\n\n"; //exiting statement.
	
	system("pause");
	return 0;
}