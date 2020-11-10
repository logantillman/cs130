// mlab2
// Logan Tillman
// CS130
// 1-17-19
// This lab consisted of writing out the functions for setting, clearing, and testing numbers at the bit level

#include <cstdio>

// This function will set the index at any given number to 1
int Set(int number, int index);

// This function will set the index at any given number to 0
int Clear(int number, int index);

// This function will return the value of the index at any number
int Test(int number, int index);

int main()
{

	int i = 0;
	i = Set(i, 0);
	printf("%d\n", i);

	i = Set(i, 3);
	printf("%d\n", i);

	i = Clear(i, 0);
	printf("%d\n", i);

	printf("%d\n", Test(i,0));
	printf("%d\n", Test(i, 3));

	return 0;
}

int Set(int number, int index)
{
	// Performs a left shift on 1 to line up it up with the index
	// Uses the OR bitwise operator to flip the new index on while keeping track of the ones that are already 1
	return number | (1 << index);
}

int Clear(int number, int index)
{
	// Uses a right shift to line up the indexes
	// Then uses bitwise NOT to flip the index to a 0
	// Finally uses the bitwise AND to keep the 1's the same while changing the index to a 0
	return number & ~(1 << index);
}

int Test(int number, int index)
{
	// Uses a right shift to line up the indexes
	// Then uses bitwise AND to determine if the value at the index is a 1 or 0
	return (number >> index) & 1;
}
