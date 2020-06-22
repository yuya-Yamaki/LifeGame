#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#define FIELD_WIDTH 24
#define FIELD_HEIGHT 24


int cells[2][FIELD_HEIGHT][FIELD_WIDTH];
int current;
int cursorX, cursorY;

int getAdjacentLivesCount(int _x, int _y)
{
	int count = 0;
	for(int y = -1; y <= 1; y++){
		for (int x = -1; x <= 1; x++) {
			if ((x == 0) && (y == 0))continue;
			int x2 = (FIELD_WIDTH+_x + x) % FIELD_WIDTH;
			int y2 = (FIELD_HEIGHT+_y + y) % FIELD_HEIGHT;
			count += cells[current][y2][x2];
		}
	}
	return count;
}

int main()
{
	while (1) {
		system("cls");
		for (int y = 0; y < FIELD_HEIGHT; y++) {
			for (int x = 0; x < FIELD_WIDTH; x++) {
				if ((x == cursorX) && (y == cursorY))
				{
					printf("");
				}
				else
				{
					printf("%s", cells[current][y][x] ? "¡":"E");
				}
			}
			printf("\n");
		}
		switch (_getch()) {
		case 'w': cursorY--; break;
		case 's': cursorY++; break;
		case 'a': cursorX--; break;
		case 'd': cursorX++; break;
		case ' ': cells[current][cursorY][cursorX] ^= 1; break;//'^=' equal 'XOR'F0->1, 1->0;
		case '\r': 
			for (int y = 0; y < FIELD_HEIGHT; y++) {
				for (int x = 0; x < FIELD_WIDTH; x++) {
					int n = getAdjacentLivesCount(x, y);
					int next = cells[current][y][x];
					if (cells[current][y][x]) {
						if (n <= 1 || n >= 4)next = 0;
					}
					else
					{
						if (n == 3)next = 1;
					}
					cells[current ^ 1][y][x] = next;
				}
			}
			current ^= 1;
			break;

		case 'q':return 1; break;
		}
	}
}