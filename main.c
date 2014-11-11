#include "game.h"

int main() {
	FloodIt game;
	int input;
	
	setup(&game);

	draw(game);

	while(1) {
		scanf("%d", &input);
		fill(&game.table, 0, 0, game.table[0][0], input);
		draw(game);
	}
}
