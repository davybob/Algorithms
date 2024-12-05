/*
 * A simple program to create a spiral of stars.
 * Given n stars create a spiral, for example with n = 10 we get:
 *				  * * * *
 *					    *
 *					*   *
 *					* * *
 * Note that the spiral corresponds to the sequence {1,2,3,4}
 * For a matrix of 100*100 at most 1225 stars can be created (includes spaces between stars)
 */

#include <iostream>
#include <string>

#define DOWN 0
#define RIGHT 1
#define UP 2
#define LEFT 3

#define MAXSIZE 100

void move(char matrix[MAXSIZE][MAXSIZE], int direction, int spaces, int& posx, int& posy) {
	/* Add a row/column of * to the matrix starting at position posx, posy */
	for (int i = 0; i < spaces; ++i) {
		if (direction == DOWN) {
			matrix[posx][posy] = '*';
			posy -= 2;
		}
		else if (direction == RIGHT) {
			matrix[posx][posy] = '*';
			posx += 2;
		}
		else if (direction == UP) {
			matrix[posx][posy] = '*';
			posy += 2;
		}
		else if (direction == LEFT) {
			matrix[posx][posy] = '*';
			posx -= 2;
		}
	}
}

void create_spiral(char matrix[MAXSIZE][MAXSIZE], int stars, int posx, int posy) {
	/* Create the spiral. Initial posx, posy should be the center of the matrix. */
	int s = 1;
	int direction = RIGHT;
	while (stars > 0) {
		std::cout << stars << " " << s << "\n";
		if (stars < s)
			move(matrix, direction, stars, posx, posy);
		else
			move(matrix, direction, s, posx, posy); 
		direction = (direction + 1) % 4;
		stars -= s;
		++s;
	}
}

void print(char matrix[MAXSIZE][MAXSIZE]) {
	/* Print the resulting spiral */
	char buffer[MAXSIZE + 2];
	bool has_content = false;

	buffer[MAXSIZE + 1] = '\0';
	buffer[MAXSIZE] = '\n';
	
	for (int i = 0; i < MAXSIZE; ++i) {
		for (int j = 0; j < MAXSIZE; ++j) {		
			buffer[j] = matrix[i][j];
			if (buffer[j] == '*')
				has_content = true;
		}
		if (has_content)
			std::cout << buffer;
		has_content = false;
	}
}

void initialise_buffer(char matrix[MAXSIZE][MAXSIZE]) {
	/* Initial the matrix to all ' '*/
	for (int i = 0; i < MAXSIZE; ++i) {
		for (int j = 0; j < MAXSIZE; ++j) {
			matrix[i][j] = ' ';
		}
	}
}

int main(int argc, char* argv[]) {
  
	if (argc != 2) {
		std::cout << "Usage: [# of stars]\n"; 
		return -1;
	}

	int stars = std::stoi(argv[1]);

	char matrix[MAXSIZE][MAXSIZE];
	
	initialise_buffer(matrix);
	create_spiral(matrix, stars, MAXSIZE/2, MAXSIZE/2);
	print(matrix);

	return 0;
}
