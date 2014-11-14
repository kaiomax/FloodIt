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
	system("clear");
	if (game.moves == 0 && game.status == LOSER)
		printf("PERDEU!\n");

	if (game.status == WINNER)
		printf("GANHOU!\n");
}

void save(FloodIt game) {
	char name[10], table_data[TABLE_ORDER * TABLE_ORDER];
	int i, j, c = 0;

    for (i = 0; i < TABLE_ORDER; ++i)
        for (j = 0; j < TABLE_ORDER; ++j)
        	// (char)(((int)'0')+INT) - Convert int to the correspondent in the ASCII chart
        	table_data[c++] = (char)(((int)'0')+game.table[i][j]); 	

	printf("Digite seu nome (limite máximo de caracteres: 10): ");
	scanf("%10s", &name);

	FILE *data;
	data = fopen("data.txt", "a");

	if (data != NULL) {
		fprintf(data, "%s %d %s\n", name, game.moves, table_data);

		fclose(data);
	}

	printf("Jogo salvo!\n");
	exit(0);
}
