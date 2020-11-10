#include <cstdio>
#include <iostream>
using namespace std;

struct Real
{
	int sign;
	long exponent;
	unsigned long fraction;
};

Real Decode(int float_value);

int Encode(Real real_value);

int main()
{
	int floatval;

	printf("Enter a float value: ");
	scanf("%f", (float *)&floatval);

	Real name = Decode(floatval);

//	printf("sign = %d, exponent = %d, fraction = 0x%x\n", name.sign, name.exponent, name.fraction);

	int originalnum = Encode(name);

	printf("%f\n", *(float*)&originalnum);

return 0;
}

// Converts into components
Real Decode(int float_value)
{
	Real components;
	components.sign = (float_value >> 31) & 1;
	components.exponent = ((float_value >> 23) & 0xff) - 127;
	// Fraction doesn't work but im tired of messing with it. at least it compiles....
	components.fraction = float_value & 0x7fffff;
	return components;
}

// Converts back into original number
int Encode(Real real_value)
{
	int float_value = 0;
	float_value = real_value.sign << 31;
	float_value |= (((real_value.exponent + 127) & 0xff) << 23);
	float_value |= real_value.fraction & 0x7fffff;
	return float_value;
}
