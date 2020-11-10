#include <cstdio>

int main()
{
	int size = 5;
	int array[size] = {1, 3, 9, 4, 12};
	int temp;
	int result = 0;
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");

	for (int i = 0; i < (size-1); i++)
	{
		for (int j = i+1; j < size; j++)
		{
			int temp;
			if (array[i] > array[j])
			{
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}

	if ((size % 2) == 0)
	{
		int num = (size/2);
		int temporary;
		temporary = array[num-1] + array[num];
		result = (temporary/2);
		printf("Result = %d\n", result);
	}
	else
	{
		int num = (size/2);
		int temporary;
		temporary = array[num];
		result = temporary;
	printf("Result = %d\n", result);
	}
/*	else
	{
		int medtemp = size / 2;
		medtemp = array[medtemp];
		result = medtemp;
		printf("Result = %d\n", result);
	}
*/
	for (int i = 0; i < size; i++)
	{
		printf("%d ", array[i]);
	}

	printf("\n");
return 0;
}
