// Extra Credit
// COSC 130
// This lab is supposed to read in machine code and translate it into assembly commands but I didn't get very far
// I'm hoping the work I did is at least worth something
// Logan Tillman
// 3-14-19

#include <cstdio>
#include <string>
using namespace std;
int main(int argc, char *argv[])
{
	FILE* input;
	FILE* output;
	int filesize;
	int buffer;
	int *commands;
	int rd = 0;
	int rs1 = 0;
	int rs2 = 0;
	int imm = 0;
	int inds = 0;
	string op;

	// Checks the command line to make sure the right amount of arguments were entered
	if (argc < 3 || argc > 4)
	{
		printf("Usage: ./<labname> <input file> <output file> <*optional* a or x>\n");
			return -1;
	}
	
	// Opens the file to read from and gets the size of it
	input = fopen(argv[1], "rb");
	fseek(input, 0, SEEK_END);
	filesize = ftell(input);
	fseek(input, 0, SEEK_SET);
	
	// Assigns dynamic memory of the file size
	commands = new int [filesize];

	// Reads in all of the lines from the input file
	int i = 0;
	while (fread(&buffer, 1, sizeof(int), input) != 0)
	{
		commands[i] = buffer;
		i++;
	}

	// Closes the input file
	fclose(input);

	// If no write file is specified it will output to the console
	if (argv[2][0] != '-')
	{
		output = fopen(argv[2], "w");
	}
	else
	{
		output = stdout;
	}

	//	Loops through the machine code and grabs the rd, rs1, rs2, and immediate to determine the op
	for (int i = 0; i < filesize; i++)
	{
		int opcode;
		opcode = (commands[i] & 0x0000007f);
	
		if (opcode == 0b0110111)
		{
			rd = (commands[i] & 0x00000f80);
			imm = (commands[i] & 0xfffff000);
			op = "LUI";
		}

		if (opcode == 0b1101111)
		{
			rd = (commands[i] & 0x00000f80);
			imm = 0;	// im not even going to attempt this immediate
			op = "JAL";
		}

		if (opcode == 0b1100111)
		{		
			rd = (commands[i] & 0x00000f80);
			inds = (commands[i] & 0x00007000);
			rs1 = (commands[i] & 0x000f8000);
			imm = (commands[i] & 0xfff00000);
			op = "JALR";
		}

		if (opcode == 0b0000011)
		{
			rd = (commands[i] & 0x00000f80);
			inds = (commands[i] & 0x00007000);
			rs1 = (commands[i] & 0x000f8000);
			imm = (commands[i] & 0xfff00000);
			switch(inds)
			{
				case(0b000): op = "LB";
					break;
				case(0b001): op = "LH";
					break;
				case(0b010): op = "LW";
					break;
			}
		}

		if (opcode == 0b0100011)
		{
			imm = (commands[i] & 0x00000f80);
			inds = (commands[i] & 0x00007000);
			rs1 = (commands[i] & 0x000f8000);
			rs2 = (commands[i] & 0x01f00000);
			switch(inds)
			{
				case(0b000): op = "SB";
					break;
				case(0b001): op = "SH";
					break;
				case(0b010): op = "SW";
					break;
			}
		}

		if (opcode == 0b0010011)
		{
			rd = (commands[i] & 0x00000f80);
			inds = (commands[i] & 0x00007000);
			rs1 = (commands[i] & 0x000f8000);
			imm = (commands[i] & 0xfff00000);
			switch(inds)
			{
				case(0b000): op = "ADDI";
					break;
				case(0b100): op = "XORI";
					break;
				case(0b110): op = "ORI";
					break;
				case(0b111): op = "ANDI";
					break;
			}

		}

		if (opcode == 0b0110011)
		{
			inds = (commands[i] & 0x00007000);
			rs1 = (commands[i] & 0x000f8000);
			rs2 = (commands[i] & 0x01f00000);
			switch(inds)
			{
				case(0b000):
					if ((commands[i] & 0xfe000000) == 0b0000000)
					{
						op = "ADD";
					}
					else
						op = "SUB";
					break;
				case(0b001):
					op = "SLL";
					break;
				case(0b100):
					op = "XOR";
					break;
				case(0b101):
					if ((commands[i] & 0xfe000000) == 0b0000000)
					{
						op = "SRL";
					}
					else
						op = "SRA";
					break;
				case(0b110):
					op = "OR";
					break;
				case(0b111):
					op = "AND";
					break;
			}
			
		}

		else
		{
			// Prints invalid if none of the commands are found
			printf("inv		invalid\n");
			continue;
		}

		// My attempt at printing the outcomes
		printf("%s %d %d %d %d\n", op.c_str(), rd, rs1, rs2, imm);
	}

	//	Closes the output file
	fclose(output);

	// Delets the dynamic memory
	delete [] commands;
return 0;
}
