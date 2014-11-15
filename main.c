#include "game.h"

int main() {
	FloodIt game;
	int input, new_value;

	setup(&game);

	draw(game);

	while(input != 'q' && game.moves && game.status == LOSER) {
		input = getchar();
		if (input >= '0' && input <= '5') {
			new_value = input - '0';
			fill(&game.table, 0, 0, game.table[0][0], new_value);
			game.moves--;
			winner_check(&game);
			draw(game);
		}
		if (input == 's') {
			save(game);
		}
		if (input == 'o') {
			load(&game);
			draw(game);
		}
	}

	status(game);
}
