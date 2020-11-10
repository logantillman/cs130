// Lab6
// COSC 130
// Logan Tillman
// This program decrypts messages by using a data key and an index key
// 2-15-19

#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

struct Decrypt
{
	char data;
	int index;
};

int main(int argc, char **argv) 
{
	FILE *fout;
	int filesize;
	int counter = 0;
	char dkey = *argv[2];
	int nkey = atoi(argv[3]);

	// Error checks the command line to make sure the user entered the right ammount of arguments
	if (argc != 4)
	{
		printf("Usage: <filename> <dkey> <nkey>\n");
		return -1;
	}

	// Opens the file for reading only
	fout = fopen(argv[1], "rb");
	
	// Checks to see if the file opened correctly
	if (fout == nullptr)
	{
		perror("Error");
		return -1;
	}

	// Gets the size of the whole file and divides by 8 to tell us how many letters we have
	fseek(fout, 0, SEEK_END);
	filesize = ftell(fout);
	filesize /= 8;

	// Allocates memory to the message struct with the amount of letters in the file
	Decrypt *message = new Decrypt[filesize];
	
	// This is where the result is stored and printed
	char result[filesize];

	// Starts the file at the beginning
	fseek(fout, 0, SEEK_SET);
	
	// Reads in the bytes to their correct locations within the struct
	while (counter < filesize)
	{
		fread(&message[counter].data, 1, 1, fout);
		fseek(fout, 3, SEEK_CUR);	// Skips the 3 padding bytes
		fread(&message[counter].index, 1, 4, fout);
		++counter;	// Keeps track of which letter we're on
	}

	// Decodes the letters and the indexes
	for (int i = 0; i < filesize; i++)
	{
		message[i].data ^= dkey;
		message[i].index ^= nkey;

		// Prints if the index is out of range
		if (message[i].index > filesize || message[i].index < 0)
		{
			printf("%s %d\n", "Error, invalid index of", message[i].index);
			return -1;
		}
	}

	// Assigns the letters in the correct order to the result array
	for (int i = 0; i < filesize; i++)
	{
		int order_index = message[i].index;
		result[order_index] = message[i].data;
	}

	// Prints the result string
	printf("%s\n", result);

	// Deletes the assigned memory
	delete[] message;

	// Closes the file
	fclose(fout);
return 0;
}
