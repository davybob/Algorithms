#include <stdio.h>
#include <stdlib.h>

#define SIZEOF(x) (int)(sizeof(x) / sizeof(int))

void CountingSort(int *InArray,int *OutArray, int maxsize, int sizeofArray){
	int *C = (int*)calloc(maxsize + 1, sizeof(int));
	for (int i = 1; i < sizeofArray; i++)
	{
		C[InArray[i]] = C[InArray[i]] + 1;
	}
	for (int i = 1; i < maxsize + 1; i++)
	{
		C[i] = C[i] + C[i - 1];
	}
	for (int i = sizeofArray - 1; i > -1; i--)
	{
		OutArray[C[InArray[i]]] = InArray[i];
		C[InArray[i]] = C[InArray[i]] - 1;
	}
}

int findmax(int *Array, int maxsize){
	int temp = Array[1];
	for (int i = 0; i < maxsize; i++)
	{
		if (Array[i] > Array[i + 1])
		{
			if (temp < Array[i])
			{
				temp = Array[i];
			}
		}
	}
	return temp;
}

int main(){
	int InArray[] = { 2, 5, 3, 0, 2, 3, 0, 3, 8, 9, 2 };
	size_t maxsize = SIZEOF(InArray);
	int *OutArray = (int*)calloc(maxsize, sizeof(int));

	CountingSort(InArray, OutArray, findmax(InArray, maxsize), maxsize);

	for (int i = 0; i < maxsize; i++)
	{
		printf("%i ", OutArray[i]);
	}

	system("pause");
	return 0;
}