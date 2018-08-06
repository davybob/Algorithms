#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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
	int Number;
	std::cout << "Please state amount of numbers to be sorted: ";
	std::cin >> Number;
	int *InArray = (int*)calloc(Number, sizeof(int));
	std::cout << "\nPlease Input an array of numbers (seperated by spaces) to be sorted: ";
	for (int i = 0; i < Number; i++)
	{
		std::cin >> InArray[i];
	}

	int *OutArray = (int*)calloc(Number, sizeof(int));

	CountingSort(InArray, OutArray, findmax(InArray, Number), Number);

	for (int i = 0; i < Number; i++)
	{
		printf("%i ", OutArray[i]);
	}

	system("pause");
	return 0;
}
