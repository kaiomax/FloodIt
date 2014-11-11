#include "game.h"

int main() {
	FloodIt game;
	int input, new_value;

	setup(&game);

	draw(game);

	while(input != 'q') {
		input = getchar();
		if (input >= '0' && input <= '5') {
			new_value = input - '0';
			fill(&game.table, 0, 0, game.table[0][0], new_value);
			draw(game);
		}
	}
}
