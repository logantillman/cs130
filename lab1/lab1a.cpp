//Lab 1A
//COSC130
//For this lab, I wrote the function definitions that convert characters to integers, strings to integers, and vice versa
//Logan Tillman
//1-16-19
//
#include <iostream>
#include <string>
using namespace std;

//Prototypes for the functions that you will write
int  CharToInt(char v);
char IntToChar(int v);
int StringToInt(string val);
string IntToString(int val);

int main(int argc, char *argv[])
{
        string sresult;
        int left;
        int right;
        char op;

        if (4 != argc) {
                printf("Usage: %s <left> <op> <right>\n", argv[0]);
                return -1;
        }
        //Notice that this calls your StringToInt. So, make sure you debug
        //StringToInt() to make sure that left and right get a proper
        //value.
        left = StringToInt(argv[1]);
        right = StringToInt(argv[3]);
        op = argv[2][0];
        //Calculate based on the op. Notice that this calls IntToString,
        //so debug your IntToString() function to make sure that sresult
        //is given the proper result. This assumes your StringToInt already
        //works.
        switch (op)
        {
                case 'x':
                        sresult = IntToString(left * right);
                        break;
                case '/':
                        sresult = IntToString(left / right);
                        break;
                case '+':
                        sresult = IntToString(left + right);
                        break;
                case '-':
                        sresult = IntToString(left - right);
                        break;
                case '%':
                        sresult = IntToString(left % right);
                        break;
                default:
                        sresult = IntToString(left);
                        break;
        }

        //Remember, printf is the only output function you may use for this lab!
        //The format string is %d %c %d = %s. This means that the first argument
        //is %d (decimal / integer), %c (character), %d (decimal /integer),
        //%s (string). Notice that because printf() is a C-style function, you
        //must pass strings as character arrays. We can convert a C++ string
        //to a character array (C-style string) by using the c_str() member function.
        printf("%d %c %d = %s\n", left, op, right, sresult.c_str());
        return 0;
}

// This function takes a character and converts it to an integer
int CharToInt(char v)
{
	int i = 0;

	// Since '0' is the value 48 on the ASCII table, subtracting 48 from the character value will give you the integer value
	// EX. The integer 1 has the character value of 49. Therefore 49 - '0' (which is 48) = 1
	i = v - '0';

	return i;
}

// This function takes an integer and converts it to a char
char IntToChar(int v)
{
	char c;

	// This is the same premise as above, adding '0' (48) to an integer value will give you the integer's char value
	c = v + '0';
	
	return c;
}

// This function takes a string and converts it to an integer
int StringToInt(string val)
{
	int result = 0;

	bool negative = false;	// I created a bool variable to keep track if the number given is negative

	val.c_str();	// Converts the string to a c style string to be able to read the individual characters

	for(int i = 0; val[i] != '\0'; i++)	// Loops through the c style string and converts it into an integer
	{
		int num = 0;	// Temporary variable used to store each number read

		if (val[i] == '-')	// Checks to see if the first character is '-', if sp, it'll set the bool to true and continue the loop
		{
			negative = true;
			continue;
		}

		num = CharToInt(val[i]);	// This will take the character at i in the c style string and convert it to an integer

		// This is what I use to check if any numbers have already gone through the loop. If the result is 0,
		// that means the number currently stored in num is the first number to be added to the result.
		if (result == 0)
		{
			result = num;
		}

		// This will execute if it's no longer on the first number in the string.
		// For example, if the number to convert is 4321, this will execute after the 4 was read in and stored in result
		else if (result != 0)
		{
			// Takes the current result and multiplies it by 10, then adds the current number to it.
			// Going off my example, if the current result is 4, it'll multiply it by 10 and add the next number (3) to it
			result = (result * 10) + num;
		}

	}

	// Executes after the loop is done. If negative was updated to true, it'll multiply the resultant integer by -1
	if (negative == true)
		result = result * -1;

return result;
}

// This function takes an integer and converts it into a string
string IntToString(int val)	
{
	string numberString;	// This is the resultant string

	char numberChar;	// This is the character that will be added to the string

	bool negative = false;	// Keeps track if the initial number is negative
	
	if (val == 0)	// Checks to see if the number passed through is 0
	{
		numberString = numberString + '0';	// If the number is 0, it'll add it to the string and return it
		return numberString;
	}

	while (val != 0)	// Otherwise, this willl execute while val is not 0
	{
		if (val < 0)	// Checks to see if the number is a negative
		{
			negative = true; // If so, it'll update the bool to true

			val = val * -1;	//Then I convert it to a positive number to avoid mistakes in my math
		}

		int num = val % 10;	// This will strip the last number from the integer

		val = val / 10;	// Divides the value by 10 to get rid of the integer taken off previously

		numberChar = IntToChar(num);	// Converts the integer taken off to a character

		numberString = numberChar + numberString;	// Adds the character to the start of the current string
	}

	if (negative == true)	// Executes if the initial number was a negative
	{
		numberString = '-' + numberString;	// Adds a '-' to the beginning of the string
	}

return numberString;
}
