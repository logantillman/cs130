// Lab5
// COSC 130
// This lab is a text based MUD game where the user tries to reach the end room through navigating the rooms
// Logan Tillman
// 2-15-19

#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

// Struct for setting up the rooms
struct Room
{
	string roomnum;
	string roomdesc;

	// Setting the initial location to -1 for validity checking later
	int n = -1;
	int e = -1;
	int s = -1;
	int w = -1;
};

int main(int argc, char **argv)
{
	ifstream fin;
	stringstream sout;
	string line;
	char command = 'a';
	int numrooms = 0;
	int tildecount = 0;
	int position = 0;
	int i = 0;	// i is the counter for which room we're reading in

	// Error checks the command line
	if (argc != 2)
	{
		printf("Usage ./lab5 <filename>\n");
		return -1;
	}

	// Opens the file
	fin.open(argv[1]);

	// Error checks the file
	if (!fin)
	{
		perror(argv[1]);
		return 1;
	}

	// Counts the tildes to determine how many rooms are in the file
	while (getline(fin, line))
	{
		if (line == "~")
		{
			sout.clear();
			sout.str("");
			++tildecount;
		}
		else
		{
			sout << line << '\n';
		}

		// Increases the room count by one once it reaches three ~'s in a file
		if (tildecount == 3)
		{
			++numrooms;
			tildecount = 0;
		}
	}

	// Assigns dynamic memory with the size corresponding to the amount of rooms
	Room *rooms = new Room[numrooms];

	// Restarts the file from the start for the next while loop
	fin.clear();
	fin.seekg(0, ios::beg);

	// Loops through to read and store the information from the file	
	while (getline(fin, line))
	{
		if (line == "~")
		{
			// Stores the room number
			if (tildecount == 0)
			{
				rooms[i].roomnum = sout.str();
			}
			
			// Stores the description of the room
			else if (tildecount == 1)
			{
				rooms[i].roomdesc = sout.str();
			}

			// Stores the possible moves of the room
			else if (tildecount == 2)
			{
				// Uses a temporary variable and turns it into a c style string
				string temp = sout.str();
				temp.c_str();

				// Loops through each character of the possible moves
				for (int j = 0; j < (int)temp.size(); ++j)
				{
					char check = temp[j];
					string numberstring;
					int numberint;

					// Sets the room number to 2 + the current index
					numberstring = numberstring + temp[j+2];

					// If the character read is one of these directions, it will execute
					if (check == 'n' || check == 's' || check == 'e' || check == 'w')
					{
						// Checks to see if the possible move has a double digit room number (since im reading it in as chars I need to account for double digits)
						if (temp[j+3] != ' ')
						{
							numberstring = numberstring + temp[j+3];
						}

						// Converts the string into a int
						numberint = stoi(numberstring);
					}

					// Assigns the correct room number to the directions
					switch (check)
					{
						case('n'):
							rooms[i].n = numberint;
							break;
						case('e'):
							rooms[i].e = numberint;
							break;
						case('s'):
							rooms[i].s = numberint;
							break;
						case('w'):
							rooms[i].w = numberint;
							break;
						default:
							continue;
					}
				}
			}
			sout.clear();
			sout.str("");
			++tildecount;
		}
		else
		{
			sout << line << '\n';
		}
		if (tildecount == 3)
		{
			++i;	// i in this case is used to determine which room we're reading
			tildecount = 0;
		}
	}


	// Executes until the user types 'q' to quit
	while (command != 'q')
	{
		// Gets the command from the user
		scanf("%c", &command);

		// Prints out the room information
		if (command == 'l')
		{
			string exits = "Exits: ";
			printf("%s%s", rooms[position].roomnum.c_str(), rooms[position].roomdesc.c_str());
			
			// These if statements determine which exits are possible to print out
			if (rooms[position].n != -1)
			{
				exits += "n ";
			}
			if (rooms[position].e != -1)
			{
				exits += "e ";
			}
			if (rooms[position].s != -1)
			{
				exits += "s ";
			}
			if (rooms[position].w != -1)
			{
				exits += "w ";
			}
			printf("%s\n", exits.c_str());
			continue;
		}

		// Checks to see if north is a valid move, if not, it rejects it
		else if (command == 'n')
		{
			if (rooms[position].n == -1)
			{
				printf("You can't go NORTH!\n");
				continue;
			}
			printf("You moved NORTH.\n");
			position = rooms[position].n;
			continue;
		}

		// Checks to see if east is a valid move
		else if (command == 'e')
		{
			if (rooms[position].e == -1)
			{
				printf("You can't go EAST!\n");
				continue;
			}
			printf("You moved EAST.\n");
			position = rooms[position].e;
			continue;
		}

		// Checks if south is a valid move
		else if (command == 's')
		{
			if (rooms[position].s == -1)
			{
				printf("You can't go SOUTH!\n");
				continue;
			}	
			printf("You moved SOUTH.\n");
			position = rooms[position].s;
			continue;
		}

		// Checks if west is a valid move
		else if (command == 'w')
		{
			if (rooms[position].w == -1)
			{
				printf("You can't go WEST!\n");
				continue;
			}
			printf("You moved WEST.\n");
			position = rooms[position].w;
			continue;
		}
	}

	// Deletes the memory assigned once the user types 'q'
	delete[] rooms; 

	// Closes the file once done
	fin.close();
return 0;
}
