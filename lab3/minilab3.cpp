#include <cstdio>
#include <iostream>
using namespace std;

// This function adds two numbers on the bit level through bitwise operators
int add(int left, int right)
{
	// Will execute while the right number isn't 0
	while (right != 0)
	{
		// Determines the numbers to carry
		int carry_out = left & right;
		// XOR will sum the bits of left and right
		left = left ^ right;
		// Shifts carry_out by 1 to allow for summing the next bit
		right = carry_out << 1;
	}

	return left;
}

int main()
{
	int left;
	int right;

	cout << "Enter two numbers to add: ";
	cin >> left >> right;

	cout << "Result = " << add(left, right) << '\n';

	return 0;
}
