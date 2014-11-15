#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_ORDER 14

enum game_status {LOSER, WINNER};

typedef struct {
	int moves;
	int table[TABLE_ORDER][TABLE_ORDER];
	enum game_status status;

} FloodIt;

void setup(FloodIt *game) {
	int i, j;

	game -> moves = 25;
	game -> status = LOSER;

	srand(time(NULL));

    for (i = 0; i < TABLE_ORDER; ++i)
        for (j = 0; j < TABLE_ORDER; ++j)
            game -> table[i][j] = rand() % 6;
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

	printf("Jogadas restantes: %d\n", game.moves);
}

void fill(int *table, int row, int col, int target, int new_value) {
	if(row > 13 || col > 13 || col < 0 || row < 0)
		return;

	if(table[row * TABLE_ORDER + col] == target) {
		table[row * TABLE_ORDER + col] = new_value;
		fill(table, row, col - 1, target, new_value);
		fill(table, row + 1, col, target, new_value);
		fill(table, row, col + 1, target, new_value);
		fill(table, row - 1, col, target, new_value);
	}
}

void winner_check(FloodIt *game) {
	int i, j;

	for (i = 0; i < TABLE_ORDER; ++i) {
		for (j = 0; j < (TABLE_ORDER - 1); ++j) {
			if (game -> table[i][j] != game -> table[i][j+1])
				return;
		}
	}

	game -> status = WINNER;
}

void status(FloodIt game) {
	if (game.moves == 0 && game.status == LOSER)
		printf("\nPERDEU!\n");

	if (game.status == WINNER)
		printf("\nGANHOU!\n");
}

void save(FloodIt game) {
	char table_data[TABLE_ORDER * TABLE_ORDER];
	int row, col, item = 0;

	for (row = 0; row < TABLE_ORDER; ++row)
		for (col = 0; col < TABLE_ORDER; ++col)
        	// (char)(((int)'0')+INT) - Convert int to the correspondent in the ASCII chart
			table_data[item++] = (char)(((int)'0')+game.table[row][col]); 	

	FILE *data;
	data = fopen("data.txt", "w");

	if (data != NULL) {
		fprintf(data, "%d %s", game.moves, table_data);
		fclose(data);
	}

	printf("Jogo salvo!\n");
	exit(0);
}

void load(FloodIt *game) {
	char table_data[TABLE_ORDER * TABLE_ORDER];
	int moves, row, col, item = 0;

	FILE *data;
	data = fopen("data.txt", "r");

	if (data != NULL) {
		fscanf(data, "%d %s", &moves, &table_data);
		fclose(data);
	}

	game -> moves = moves;

	for (row = 0; row < TABLE_ORDER; ++row)
		for (col = 0; col < TABLE_ORDER; ++col)
			game -> table[row][col]	= table_data[item++] - '0';
}