// Lab3
// COSC130
// This lab is a calculator for +, -, and * through the bitwise operators
// Logan Tillman
// 1-25-19

#include <cstdio>
using namespace std;

// This is a function that will store the sign a number
int sign(int value);

// This function will perform the twos compliment on a number (turns - to + or + to -)
int twos(int value);

// Adds two numbers through bitwise operators
int add(int left, int right);

// Subtracts two numbers through bitwise operators
int sub(int left, int right);

// Multiplies two numbers through bitwise operators
int mul(int left, int right);

int main(int argc, char *argv[])
{
	if (argc < 4) {
		printf("Usage: %s <num> <op> <num>\n", argv[0]);
		return -1;
	}

	int left;
	int right;
	char op;
	int result;

	sscanf(argv[1], "%d", &left);
	sscanf(argv[2], "%c", &op);
	sscanf(argv[3], "%d", &right);

	switch (op)
	{
		case '+':
			result = add(left, right);
			break;
		case '-':
			result = sub(left, right);
			break;
		case 'x':
			result = mul(left, right);
			break;
		default:
			printf("Unknown operation '%c'\n", op);
			return -2;
	}

	printf("%d %c %d = %d\n", left, op, right, result);

	return 0;
}

// This function keeps track of the sign of a number
int sign(int value)
{
	// Shifts the value to the right by 31 to line it up with 1
	// Then &'s it with 1 to see if the value is 1 (negative) or 0 (positive)
	return (value >> 31) & 1;
}

// Performs the two's compliment on a number
int twos(int value)
{
	// Performs the one's compliment by flipping the number (+ to -) or (- to +)
	int flip = ~(value);

	// Then adds one to make it the twos compliment
	int result = add(flip, 1);
	return result;
}

// This function adds two numbers using bitwise operators
int add(int left, int right)
{
	int carry = 0;
	int sum = 0;

	// This function loops through all of the bits and performs the addition
	for(int i = 0; i < 32; i++)
	{
		// Lines up the left and right most bit
		int l = (left >> i) & 1;
		int r = (right >> i) & 1;

		// Takes the sum by XOR'ing the left, right, and carry
		int s = l ^ r ^ carry;
		
		// Calculates the carry
		carry = (l & r) | (r & carry) | (l & carry);

		// Totals up the sum to be returned
		sum = sum | (s << i);
	}
	return sum;
}

// Function that subtracts two numbers
int sub(int left, int right)
{
	// Takes the right number and flips it to a negative	
	int flip = twos(right);

	// Then adds the left number and the flipped number
	return add(left, flip);
}

// Function that multiplies two numbers
int mul(int left, int right)
{
	int result = 0;

	// These keep track of the negative signs of the numbers
	int leftnegative = sign(left);
	int rightnegative = sign(right);

	// If either of the numbers are negatives it will flip them to a positive
	if (leftnegative)
	{
		left = twos(left);
	}

	if (rightnegative)
	{
		right = twos(right);
	}

	// Executes until the right number is 0
	while (right)
	{
		// Executes while right & 1 is 1
		if (right & 1)
		{
			// Adds the result and the left number
			result = add(result, left);
		}
		// Shifts both of the numbers by 1 to move through the bits
		right >>= 1;
		left <<= 1;
	}

	// Re-adds the negatives, if both were negative, it performs the twos compliment twice thus giving a positive
	// If only one is negative, it flips the result by the twos compliment once
	if (leftnegative)
	{
		result = twos(result);
	}

	if (rightnegative)
	{
		result = twos(result);
	}

	return result;
}
