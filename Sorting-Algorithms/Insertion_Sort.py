# standard library 
import sys

def ReadFile(filename):
	with open(filename) as file:
		data = file.read()
		data = data.split(' ')
		Input = data
		Input = list(map(int, Input))
		file.close()
	return Input

def sort(Input, size):
	for x in range( size):
		for y in range(size):
			if Input[x] < Input[y]:
				temp = Input[y]
				Input[y] = Input[x]
				Input[x] = temp
	print (Input)
def main():
	file = input("Please enter file to sort: ")
	Input = ReadFile(file)
	
	#Input = [1,5,3,2,9, 6, 6, 0]

	size = len(Input)
	sort(Input, size)


main()
