#include <math.h>
#include <thread>
#include <stdio.h>  
#include <stdlib.h> 

int *left(int *l, int size, int Input[]){

	memcpy(l, Input, (size / 2) * sizeof(int));
	l[(size / 2) + 1] = '@';

	for (int j = 0; j < (size / 2); j++)
	{
		int temp;
		for (int i = j + 1; i < (size / 2); i++)
		{
			if (l[i] < l[j])
			{
				temp = l[j];
				l[j] = l[i];
				l[i] = temp;
			}
		}
	}
	return l;
}
int *right(int *r, int size, int Input[]){

	memcpy(r, Input + (size/2), (size / 2) * sizeof(int));
	r[(size / 2) + 1] = '@';

	for (int j = 0; j < (size / 2); j++)
	{
		int temp;
		for (int i = j + 1; i < (size / 2); i++)
		{
			if (r[i] < r[j])
			{
				temp = r[j];
				r[j] = r[i];
				r[i] = temp;
			}
		}
	}
	return r;
}

int *MERGE(int Input[], int size){

	int *l = (int*)calloc((size / 2) + 1, sizeof(int));
	int *r = (int*)calloc((size / 2) + 1, sizeof(int));

	std::thread first (left,l,size,Input);
	std::thread second (right, r, size, Input);

	first.join();
	second.join();

	int a = 0, b = 0;

	for (int i = 0; i < size; i++)
	{
		if (l[a] <= r[b])
		{
			Input[i] = l[a];
			a = a + 1;
		}
		else if (r[b] <= l[a])
		{
			Input[i] = r[b];
			b = b + 1;
		}
		if (l[a] == '@')
		{
			memcpy(Input + i, r + b, (size / 2) - b - 1);
			break;
		}
		else if (r[b] == '@')
		{
			memcpy(Input + i, l + i, (size / 2) - a - 1);
			break;
		}

	}
	
	return 0;
}


 int main(){

	int Input[] = { 2, 5, 6, 1, 2, 3, 4, 5, 9, 11 };
	int size = (sizeof(Input) / sizeof(int));

	MERGE(Input, size);


	for (int i = 0; i < size; i++)
	{
		printf("%d, ", Input[i]);

	}
	system("pause");

	return 0;

}
