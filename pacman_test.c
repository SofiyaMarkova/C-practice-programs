/* your name | votre nom  */

#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"

const int moves[] = { NORTH, EAST, SOUTH, WEST, NORTH };

int main() {

	int pacman_location[2]; //array store pacman location for row (0) and col (1)
	char game_board[N_ROWS][N_COLS];

	initialize_game(game_board, pacman_location);

	for (int i = 0; i < sizeof(moves) / sizeof(int); i++) {
		play(game_board, moves[i], pacman_location, i);
		if (game_is_over(game_board)) {
			break;
		}
	}

	return EXIT_SUCCESS;
}

