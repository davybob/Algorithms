#include <iostream>

int main(){
	int Input[] = {1, 2, 6, 9, 8, 2, 5};
	int size = (sizeof(Input)/sizeof(int));
	int temp = 0;
	for (int i = 0; i < size; i++)
	{

		int key = Input[i];
			temp = Input[i];
		for (int j = 0; j < (size); j++)
		{
			if (key <= Input[j])
				{
				temp = Input[j];
				Input[j] = Input[i];
				Input[i] = temp;
				}

		}
	}

	for (int i = 0; i < size; i++)
	{
		std::cout << Input[i];
	}

	return 0;
}
