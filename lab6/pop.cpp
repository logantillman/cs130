#include <cstdio>

int main(int argc, char *argv[])
{
	int num1, num2;

	if (argc != 4)
	{
		printf("Enter 4 u dumbass\n");
		return -1;
	}

	num1 = sscanf(argv[1], "%d", &num1);
	num2 = sscanf(argv[3], "%d", &num2);

	printf("%d %d\n", num1, num2);


return 0;
}
