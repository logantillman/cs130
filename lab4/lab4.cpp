// Lab 4
// COSC 130
// Logan Tillman
// 2-4-19

#include <cstdio>
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
Real Normalize(Real value);
Real Multiply(Real left, Real right);
Real Add(Real left, Real right);
Real Twos(Real value);

int main(int argc, char *argv[])
{
     int left, right;
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
	return 0;
}
//Implement the following functions

// Decode takes an integer and converts it into components
Real Decode(int float_value)
{
	Real components;

	// Seperates the sign from the value
	components.sign = (float_value >> 31) & 1;

	// Obtains the exponent of the value
	components.exponent = ((float_value >> 23) & 0xff) - 127;
	
	// Gets the fraction from the value and adds the implicit 1 to the 23rd bit
	components.fraction = float_value & 0x7fffff;
	components.fraction = components.fraction | (1 << 23);

	return components;
}

// This takes a Real struct and converts it back into an integer
int Encode(Real real_value)
{
	int num;

	// Sets the sign to the 31st bit
	num = real_value.sign << 31;

	// Sets the exponent back with the bias taken into account
	num |= (((real_value.exponent + 127) & 0xff) << 23);

	// Sets the 23 fraction bits back into their spots
	num |= real_value.fraction & 0x7fffff;

	return num;
}

// This function takes a Real struct and shifts it back into a 1.0 number
Real Normalize(Real value)
{
	// This will shift the fraction right and add to the exponent until theres a 1 in the 23rd bit and nothing else beyond
	while (value.fraction & 0xffffffffff000000)
	{
		value.fraction >>= 1;
		value.exponent += 1;
	}

	// This shifts the fraction left until theres 1 one in the 23rd bit
	while (!(value.fraction & 0xffffffffff000000))
	{
		value.fraction <<= 1;
		value.exponent -= 1;
	}

	// Drops the implicit 1
	value.fraction = value.fraction & 0x7fffff;

return value;
}

// This function multiplies two Real structs
Real Multiply(Real left, Real right)
{
	// After multiplying, shift >> 23 (bc 23 x 23 can give 46 bit number, but we can only have 23 bit)
	// Send to normalize after all done
	Real product;
	int leftnegative = left.sign;
	int rightnegative = right.sign;
	product.sign = 0;
	product.exponent = 0;
	product.fraction = 0;

	// Determines if the left struct has a sign of 1
	if (leftnegative)
	{
		// Performs the twos compliment on the number
		left.sign = 0;
		left = Twos(left);
	}

	// Determines if the left struct has a sign of 1
	if (rightnegative)
	{
		// Performs the twos compliment on the number
		right.sign = 0;
		right = Twos(right);
	}

	// Will multiply until the right fraction = 0
	while (right.fraction)
	{
		if (right.fraction & 1)
		{
			product = Add(product, left);
		}

		right.fraction >>= 1;
		left.fraction <<= 1;
	}

	// Shifts the fraction right 23 so it'll drop off the extra bits
	product.fraction >>= 23;

	// Normalizes the product
	Normalize(product);

	// Re-performs the twos compliment if the number was a negative
	if (leftnegative)
	{
		product.sign ^= 1;
		product = Twos(product);
	}

	// Re-performs the twos compliment if the number was a negative
	if (rightnegative)
	{
		product.sign ^= 1;
		product = Twos(product);
	}

return product;
}

// This function will add two Real structs
Real Add(Real left, Real right)
{
	Real sum;
	sum.sign = 0;
	sum.exponent = 0;
	sum.fraction = 0;
	int carry = 0;

	// Determines the sign by comparing the exponents
	if (left.exponent > right.exponent)
	{
		sum.sign = left.sign;
	}

	else if (left.exponent < right.exponent)
	{
		sum.sign = right.sign;
	}

	// If the exponents are the same, it takes the sign of the greater fraction
	else if (left.exponent == right.exponent)
	{
		if (left.fraction > right.fraction)
		{
			sum.sign = left.sign;
		}

		if (left.fraction < right.fraction)
		{
			sum.sign = right.sign;
		}

		sum.exponent = left.exponent;
	}

	// These two while loops will match the exponents before adding
	while (left.exponent > right.exponent)
	{
		sum.exponent = left.exponent;
		right.fraction <<= 1;
		right.exponent += 1;
	}

	while (left.exponent < right.exponent)
	{
		sum.exponent = right.exponent;
		left.fraction <<= 1;
		left.exponent += 1;
	}

	// Loops through and adds all of the bits
	for(int i = 0; i < 64; i++)
    {
        // Lines up the left and right most bit
        long l = (left.fraction >> i) & 1;
        long r = (right.fraction >> i) & 1;

        // Takes the sum by XOR'ing the left, right, and carry
        long s = l ^ r ^ carry;

        // Calculates the carry
        carry = (l & r) | (r & carry) | (l & carry);

        // Totals up the sum to be returned
        sum.fraction = sum.fraction | (s << i);
    }

	Normalize(sum);

return sum;
}

// This function performs the twos compliment
Real Twos(Real value)
{
	Real result;
	Real one;	// The real struct for the number 1
	Real flip;	// The real struct for the flipped numbers
	one.sign = 0;
	one.fraction = 0;
	one.exponent = 1;
	result.sign = value.sign;
	flip.sign = 0;
	flip.exponent = ~(value.exponent);
	flip.fraction = ~(value.fraction);

	// Adds the one to the flipped numbers
	result = Add(flip, one);

return result;
}
