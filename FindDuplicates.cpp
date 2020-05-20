#include <stdio.h>
#include <stdlib.h>

#define COUNT(x) (int)(sizeof(x) / sizeof(x[0])) //finds the size of an array

int FindDup(int *in, int size){ //finds any duplicates in an array
	int count = 0;
	int num = 0;
	
	for (int i = 0; i < size-1; i++) //loops through the array !n to find any duplicates 
	{
		for (int j = 1 + i; j < size; j++)
		{
			if (in[i] == in[j] && (in[i] != 0 || in[j] != 0)) //if duplicates are found, count the amount and the type of the duplicate 
			{
					num = in[i];
					in[j] = 0;
					count += 1;
			}
		}
		if (count > 0 ) //if found print out the type and amount of duplicates, then reset the count.
		{
			printf("The number: %i occures %i times. \n", num, count + 1);
			count = 0;
			num = 0;
		}
	}

	return count;
}

int main(){
	int Input[] = { 2, 6, 5, 3, 1, 2, 7, 5, 2, 2, 7, 5 };

	int count = FindDup(Input, COUNT(Input));

	system("pause");
	return 0;
}