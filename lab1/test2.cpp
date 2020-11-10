#include <iostream>
using namespace std;

int main()
{
	string s = "9876";
	int val;
	s.c_str();

	for(int i = 0; s[i] != '\0'; i++)
	{
		char c = s[i];
		int num = c - '0';
		val = val + num;
	}

	cout << "val = " << val << '\n';

	return 0;
}
