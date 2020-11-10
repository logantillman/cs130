#include <iostream>
#include <cstdio>
using namespace std;

struct Real
{
     //sign bit
     int sign;
     //UNBIASED exponent
     long exponent;
     //Fraction including implied 1 at bit index 23
     unsigned long fraction;
};

Real Decode(int float_value);
int Encode(Real real_value);
void Normalize(Real value);
//Real Multiply(Real left, Real right);
//Real Add(Real left, Real right);
void Print(Real value);

int main(int argc, char *argv[])
{
/*     int left, right;
     char op;
     int value;
     Real rLeft, rRight, result;
     if (argc < 4) {
          printf("Usage: %s <left> <op> <right>\n", argv[0]);
          return -1;
     }
     sscanf(argv[1], "%f", (float *)&left);
     sscanf(argv[2], "%c", &op);
     sscanf(argv[3], "%f", (float *)&right);
     rLeft = Decode(left);
     rRight = Decode(right);
     if (op == 'x') {
          result = Multiply(rLeft, rRight);
     }
     else if (op == '+') {
          result = Add(rLeft, rRight);
     }
     else {
          printf("Unknown operator '%c'\n", op);
          return -2;
     }
     value = Encode(result);
     printf("%.3f %c %.3f = %.3f (0x%08x)\n",
            *((float*)&left),
            op,
            *((float*)&right),
            *((float*)&value),
            value
           );
*/
/*	Real test;
	test.sign = 0;
	test.exponent = 9;
	test.fraction = 0b111_0101_1001_0000_0000_0000_0000_0000;
*/
	int test = 2;
	Real wassup = Decode (test);
	int steptwo = Encode (wassup);
	Normalize(wassup);

	return 0;
}

Real Decode(int float_value)
{
    Real components;

    components.sign = (float_value >> 31) & 1;
    components.exponent = ((float_value >> 23) & 0xff) - 127;
    components.fraction = float_value & 0x7fffff;
    components.fraction = components.fraction | (1 << 23);

	cout << "Current Sign: " << components.sign << '\n';
	cout << "Current Exponent: " << components.exponent << '\n';
	printf("%08lx\n", components.fraction);

    return components;
}
int Encode(Real real_value)
{
    int num;

    num = real_value.sign << 31;
    num |= (((real_value.exponent + 127) & 0xff) << 23);
    num |= real_value.fraction & 0x7fffff;

	cout << "Number after Encode: " << num << '\n';

	return num;
}
void Normalize(Real value)
{
    while (value.fraction & 0xffffffffff000000)
    {
        value.fraction >>= 1;
        value.exponent += 1;
    }
/*
    while (((value.fraction >> 23) & 0xffffffffffffffff) < 1)
    {
        value.fraction <<= 1;
        value.exponent -= 1;
	}
*/
	value.fraction = value.fraction & 0x7fffff;

Print(value);
}

void Print(Real value)
{
	cout << "Normalized Sign: " << value.sign << '\n';
	cout << "Normalized Exponent: " << value.exponent << '\n';
//	cout << "Fraction: " << value.fraction << '\n';
	printf("%08lx\n", value.fraction);
}
