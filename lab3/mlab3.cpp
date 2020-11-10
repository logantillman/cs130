#include <iostream>
using namespace std;

/* int multiply(int multiplicand, int multiplier)
{
	int result = 0;
	
	while (multiplier)
	{
		if (multiplier & 1)
		{
// no plus			result += multiplicand;
		}

		multiplier <<= 1;

		multiplicand >>= 1;

	}

	result = 0;
}
*/
// cin = carry in
// cout = carry out

int add(int left, int right)
{
//	int top = 0b000_1011;
//	int bottom = 0b0000_1101;
	int result = 0;

	int rmdt = top & 1;
	int rmdb = bottom & 1;

	int sum = rmdt ^ rmdb;
	int carry_out = rmdt & rmdb;
	int carry_in = (rmdt | rmdb) & carry_out;
	result
		top >>= 1;
		bottom >>= 1;




//	sum = rmdt ^ rmdb;
//	carry_out = rmdt & rmdb;
	
//	right shift to move
//	FIXME figure out carry in

}


int main()
{

	int left;
	int right;
	double result;

	cout << "Enter two numbers to add: ";
	cin >> left >> right;

	cout << "Result: " << result << '\n';

return 0;
}

