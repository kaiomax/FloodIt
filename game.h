#include <stdio.h>
#include <time.h>

#define TABLE_ORDER 14

typedef struct {
	int turns_left;
	int table[TABLE_ORDER][TABLE_ORDER];
} FloodIt;

void setup(FloodIt *game) {
	int i, j;

	srand(time(NULL));

    for (i = 0; i < TABLE_ORDER; ++i)
        for (j = 0; j < TABLE_ORDER; ++j)
            game->table[i][j] = rand() % 6;	
}

void draw(FloodIt game) {
	int i, j;

	system("clear");

	for (i = 0; i < TABLE_ORDER; ++i) {
		for (j = 0; j < TABLE_ORDER; ++j) {
			printf("%d  ", game.table[i][j]);
		}
		printf("\n");
	}
}

void fill(int *table, int row, int col, int target, int new_value) {
	if(row > 13 || col > 13 || col < 0 || row < 0)
		return;

	if(table[row*14+col] == target) {
		table[row*14+col] = new_value;
		fill(table, row, col - 1, target, new_value);
		fill(table, row + 1, col, target, new_value);
		fill(table, row, col + 1, target, new_value);
		fill(table, row - 1, col, target, new_value);
	}
}
