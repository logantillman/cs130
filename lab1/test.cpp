#include <iostream>
using namespace std;

int main()
{	

/*	string s = "-980706";
	int val = 0;
	bool negative = false;
	s.c_str();

	for (int i = 0; s[i] != '\0'; ++i)
	{
		int num = 0;
		
		if(s[i] == '-')
		{
			negative = true;
			continue;
		}

		num = s[i] - '0';

		if(val != 0)
		{
			val = (val * 10) + num;
		}

		else if (val == 0)
		{
			val = num;
		}

//		if (negative == true)
//		{
//			val = (val * -1);
//		}

	}

	if (negative == true)
		val = val * -1;

	cout << "val = " << val << '\n';
*/

	int val = 0;
	string output;
	bool negative = false;

	if (val == 0)
	{
		output = output + '0';
	}

	while(val != 0)
	{
		if (val < 0)
		{
			negative = true;
			val *= -1;
		}
		int num = val % 10;
		val = val / 10;
		char c;
		c = num + '0';
		output = c + output;
	}

	if (negative == true)
	{
		output = '-' + output;
	}

	cout << "output = " << output << '\n';


return 0;
}
