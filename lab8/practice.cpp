#include <cstdio>
using namespace std;

struct PERSON
{
	char name[51];
	int age;
	char gender;
}	

PERSON *Search(PERSON people[], int num_people, const char *name, int age, char gender);
//int Median(const int array[], int array_size, int *buffer);

int main()
{
	char command = 'g';

	while (command != 'q')
	{
		printf("Enter");
	}


	

return 0;
}

PERSON *Search(PERSON people[], int num_people, const char *name, int age, char gender)
{
	for (int i = 0; i < num_people; i++)
	{
		if(people[i].name == name)
		{
			if(people[i].age == age)
			{
				if(people[i].gender == gender)
				{
					return people[i];
				}
			}
		}

	}
	return nullptr;
}

//int Median(const int array[], int array_size, int *buffer)
//{
//
//}
