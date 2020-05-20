#include <thread>
#include <stdio.h>  
#include <stdlib.h>
#include <iostream>

struct sum
{
	int left_sum, right_sum, cross_sum;
	int sumof;
	int max_left, max_right;
}Sum_type;

/* int FIND_MAX_SUBARRAY(int Array[], int low, int mid){
	Sum_type.left_sum = -1;
	Sum_type.right_sum = -1;

	if (mid == size/2)
	{
		for (int i = low; i < mid; i++)
		{
			Sum_type.sum = Sum_type.sum + Array[i];
			if (Sum_type.sum > Sum_type.left_sum)
			{
				Sum_type.left_sum = Sum_type.sum;
				Sum_type.max_left = i;
			}
		}
	}

	else
	{
		for (int i = low; i < mid; i++)
		{
			Sum_type.sum = Sum_type.sum + Array[i];
			if (Sum_type.sum > Sum_type.right_sum)
			{
				Sum_type.right_sum = Sum_type.sum;
				Sum_type.max_right = i;
			}
		}
	}

}
*/
int *FIND_MAX_CROSSING_SUBARRAY(int Array[],int low, int mid, int high){

	Sum_type.sumof = 0;
	Sum_type.left_sum = 0;
	Sum_type.right_sum = 0;
	Sum_type.max_left = 0;
	Sum_type.max_right = 0;

	for (int i = mid; i >= low; i--)
	{
		Sum_type.sumof = Sum_type.sumof + Array[i];
		if (Sum_type.sumof > Sum_type.left_sum)
		{
			Sum_type.left_sum = Sum_type.sumof;
			Sum_type.max_left = i;
		}
	}

	Sum_type.sumof = 0;

	for (int j = mid + 1; j <= high; j++)
	{
		Sum_type.sumof = Sum_type.sumof + Array[j];
		if (Sum_type.sumof > Sum_type.right_sum)
		{
			Sum_type.right_sum = Sum_type.sumof;
			Sum_type.max_right = j;
		}
	}

	Sum_type.cross_sum = Sum_type.left_sum + Sum_type.right_sum;

	return 0;
}

int ReadFile(const char *file, int size, int *mem){
	FILE *input;
	errno_t err;
	err = fopen_s(&input, file, "r");

	if (err = fopen_s(&input, file, "r") != 0){
		char temp[80];
		fprintf(stderr, "cannot open file '%s': %s\n", file, strerror_s(temp,err));
		exit(0);
	}

	for (int i = 0; i < size; i++)
		fscanf_s(input, "%d", &mem[i]);

	for (int i = 0; i < size; i++)
		printf("%d", mem[i]);

	fclose(input);

	return *mem;
}

 int main(){
	char filename[80];
	int size = 0;

	printf("\n");
	printf_s("%s", "Please input the file name: ");
	std::cin >> filename;
	
	printf("%s\n", "Amount of datapoints: ");
	std::cin >> size;
	
	int *mem = (int*)calloc(size, sizeof(int));


	ReadFile("help.txt", size, mem);

	FIND_MAX_CROSSING_SUBARRAY(mem, 0, size / 2, size);

	if (size == 1)
		printf("Maximum price yield is: %d . On day: %d \n", mem[1], size);
	else if (Sum_type.left_sum >= Sum_type.right_sum && Sum_type.left_sum >= Sum_type.cross_sum)
		printf("L Maximum price yield is: %d .When buying on day: %d , and selling on day: %d\n", Sum_type.left_sum, Sum_type.max_left, size / 2);
	else if (Sum_type.right_sum >= Sum_type.left_sum && Sum_type.right_sum >= Sum_type.cross_sum)
		printf("R Maximum price yield is: %d .When buying on day: %d , and selling on day: %d\n", Sum_type.right_sum, size / 2, Sum_type.max_right);
	else
		printf("C Maximum price yield is: %d .When buying on day: %d , and selling on day: %d\n", Sum_type.cross_sum, Sum_type.max_left, Sum_type.max_right + 1);

	delete mem;

	system("pause");

	return 0;

}
