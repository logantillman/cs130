// Lab 2
// COSC 130
// This is a lab that will edit a vector of integers at the bit level using bitwise operators.
// Logan Tillman
// 1-24-19

#include <cstdio>
#include <vector>
#include <string>
using namespace std;

// This function will take a bit and return the index it resides in
int Index(int bit);

// This function will take a bit and return the bit index of the number
int BitIndex(int bit);

class BITSET
{
public:
	
	// Constructor that sets the initial size of the vector to 1
	BITSET ()
	{
		data.resize(1);
	}

	// Sets the bit to 1 at the desired bit location
	void Set(int bit);

	// Sets the bit to 0 at the desired location
	void Clear(int bit);

	// Returns the value of bit
	bool Test(int bit) const;

	// Converts the index given to its binary value
	string to_binary(unsigned int index) const;

private:

	// Stores all of the integers that will be set
	vector<int> data;
};

int main()
{
	char command;
	int bit;
	BITSET bs;

	// Exectues until the user types 'q' for quit
	while (command != 'q')
	{
		// Asks the user to enter a command until they enter a valid one
		printf("%s", "Please enter a command: ");
		scanf(" %c", &command);

		if (command == 't')
		{
			scanf(" %d", &bit);

			// Returns true and prints 1 if the bit is a 1
			if (bs.Test(bit) == true)
			{
				printf("%d \n", 1);
			}
		
			// Returns false and prints 0 if the bit is a 0
			else
			{
				printf("%d \n", 0);
			}
		}
		
		// Sets the desired bit to a 1
		else if (command == 's')
		{
			scanf(" %d", &bit);
			bs.Set(bit);
		}

		// Clears the desired bit (sets it to 0)
		else if (command == 'c')
		{
			scanf(" %d", &bit);
			bs.Clear(bit);
		}
		
		// Command to print the desired bit
		else if (command == 'p')
		{
			scanf(" %d", &bit);

			// The user really enters in the index they want to print, but I just changed the name to make it less confusing
			int index = bit;
	
			// If the to_binary function returns an empty string, it'll print that the string doesn't exist
			if ((bs.to_binary(index)).size() == 0)
			{
				printf("%s%d%s", "Set #", index, " does not exist.");
			}
				// Converts the vector at the index to a binary string and prints it as a c style string
				printf("%s\n", bs.to_binary(index).c_str());
		}

	}

return 0;
}

// Sets the desired bit to a 1
void BITSET::Set(int bit)
{
	// Finds the index of the bit by / 32
	unsigned int index = Index(bit);

	// Finds the bit index of the bit by % 32
	int bitIndex = BitIndex(bit);

	// Compares the data size to the index + 1 to see if the vector needs to be resized
	if (data.size() <= (index + 1))
	{
		// Resizes the vector and fills it with 0's
		data.resize((index + 1), 0);
	}

	// Shifts 1 to the left to line up with the bit index, then bitwise OR's it to update the 0 to 1, while keeping track of the 1's
	data.at(index) = data.at(index) | (1 << bitIndex);
}

// Clears the bit (sets it to 0)
void BITSET::Clear(int bit)
{
	int index = Index(bit);
	int bitIndex = BitIndex(bit);

	// Left shifts 1 to line up with the bit to clear, bitwise NOT's it to change the 1 to a 0. AND's it to keep the 1's while changing the bit from a 1 to 0
	data.at(index) = data.at(index) & ~(1 << bitIndex);

	// Loop that checks to see if the sets in the vector are 0 after clearing
	for(int i = data.size() - 1; i >= 0; i--)
	{	
			// Starts at the end of the vector, if the last set is 0, it'll erase it and check the next one
			if ((data.at(i)) == 0)
			{	
				data.pop_back();
			}
		
			// If it runs into a set that isn't 0, it'll break out of the loop
			else
			{
				break;
			}
	}
}

// This function returns the value of the bit
bool BITSET::Test(int bit) const
{
	unsigned int index = Index(bit);
	int bitIndex = BitIndex(bit);

	// If the desired bit is out of range, it'll return false
	if (data.size() < (index + 1))
	{
		return false;
	}
	
	// Otherwise, it'll right shift the number to line up with 1, then AND returns its value
	return (data.at(index) >> bitIndex) & 1;
}

// Function that returns the index of a bit
int Index(int bit)
{
	return bit / 32;
}

// Function that returns the bit index of the bit
int BitIndex(int bit)
{
	return bit % 32;
}

// Function that converts a set to a binary string
string BITSET::to_binary(unsigned int index) const
{

	// If the set is out of range, it'll return an empty string
	if ((index + 1) > data.size())
	{
		string empty;
		return empty;
	}

	string binary;
	int num_at_index = data.at(index);
	int space_counter = 0;

	// Loops through the bits backwards
	for(int i = 31; i >= 0; i--)
	{
		// This determines when to add a space to the string (every 4th time it loops)
		if (space_counter == 4)
		{
			binary = binary + ' ';
			space_counter = 0;
		}

		// Lines up the bit with 1, then AND's it to determine if it's a 1 or 0
		int num_to_compare = num_at_index >> i;
		num_to_compare &= 1;

		// Converts the 1 or 0 to a character and adds it to the string
		char stringChar = num_to_compare + '0';
		binary = binary + stringChar;

		// Increases the counter for spaces
		++space_counter;
	}

	

	return binary;
}

