#include <cstdio>

int Add(int left, int right);
int Subtract(int left, int right);
int Multiply(int left, int right);
int Divide(int left, int right);
int Modulo(int left, int right);

int main(int argc, char **argv)
{
	int right = 0;
	int left = 0;
	char op;
	int result = 0;

	if (argc < 4)
	{
		printf("Not enough arguments\n");
		return -1;
	}

	if (argc > 4)
	{
		printf("Too many arguments\n");
		return -1;
	}	

	sscanf(argv[1], "%d", &left);
	sscanf(argv[2], "%c", &op);
	sscanf(argv[3], "%d", &right);

	if (op == '+')
		result = Add(left, right);
	if (op == '-')
		result = Subtract(left, right);
	if (op == 'x')
		result = Multiply(left, right);
	if (op == '/')
		result = Divide(left, right);
	if (op == '%')
		result = Modulo(left, right);

	printf("%d %c %d %c %d\n", left, op, right, '=', result);

return 0;
}

int Add(int left, int right)
{
	int result;
	result = left + right;
	return result;
}

int Subtract(int left, int right)
{
	int result;
	result = left - right;
	return result;
}

int Multiply(int left, int right)
{
	int result;
	result = left * right;
	return result;
}

int Divide(int left, int right)
{
	int result;
	result = left / right;
	return result;
}

int Modulo(int left, int right)
{
	int result;
	result = left % right;
	return result;
}
