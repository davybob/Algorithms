import math
import random
def nGram(sentence, n):
	#split the sentence into elements.
	words = sentence.split(" ")
	#calculate the length of the sentence.
	total = len(words) - n
	#array to fill with elements.
	grams = []
	#Fill the empty array with the elements from the sentence.
	for x in range(0,total):
		seq = ''
		for y in range(x, x + n):
			seq += words[y]  + ' '
		grams.append(seq)

	return grams

def MarkovChain():
	#Input text
	text = ''
	x = nGram(text, 2)
	#Create a random sentence from the elements
	for j in range(0,9):
		seq = ''
		r = x[math.floor(random.random() * len(x))]
		seq += r + ' '
		ar.append(seq)
	#print the output
	print(ar)

MarkovChain()