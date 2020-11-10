// mlab5
// COSC130
// Logan Tillman
// This mini lab is supposed to read lines and ignore the ~'s
// 2-7-19

#include <cstdio>
#include <sstream>
#include <vector>
using namespace std;
int main()
{
	vector<string> lines;
	char words[1000];
	FILE *fout;
	fout = fopen("myfile.txt", "rb");

	// Error checks the file
	if (fout == nullptr)
	{
		perror("myfile.txt");
	}	

	// Starts at the beginning of the file
	fseek(fout, 0, SEEK_SET);

	// Reads the file and pushes it back into the vector (I dont know how to stop at ~)
	fread(words, 1, sizeof(words), fout);
	lines.push_back(words);
	fclose(fout);

	// Loops to print the entry # and the lines
	for (int i = 0; i < (int)lines.size(); ++i)
	{
		printf("Entry %d:\n", (i+1));
		printf("%s", lines.at(i).c_str());
	}
return 0;
}
