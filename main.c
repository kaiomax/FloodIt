#include <stdio.h>
#include <stdlib.h>
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
            (*game).table[i][j] = rand() % 6;	
}

void draw(FloodIt game) {
	int i, j;

	for (i = 0; i < TABLE_ORDER; ++i) {
		for (j = 0; j < TABLE_ORDER; ++j) {
			printf("%d  ", game.table[i][j]);
		}
		printf("\n");
	}
}

int main() {
	FloodIt game;

	setup(&game);

	draw(game);
}