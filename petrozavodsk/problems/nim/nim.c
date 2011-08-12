/*
 ============================================================================
 Name        : nim.c
 Author      : Alex Davydow
 Description : Solution for the Nim problem (idea 15)
 Language    : c99
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum _Player {first, second} Player;

const char *winner_string[] = {"First", "Second"};
const char *draw_string = "Draw";

int main(void) {
	// input
	int n;
	scanf("%d", &n);
	int boards[n];
	for (int i = 0; i < n; ++i) {
		scanf("%d", &boards[i]);
	}
	// At first we will look at simpler game: one who can't make a move --- loses,
	// so no draw available.
	int sprague_grundy = 0;
	for (int i = 0; i < n; ++i) {
		sprague_grundy ^= boards[i] / 5;
	}
	Player candidate = (sprague_grundy == 0 ? second : first);
	// Now we know that candidate can at least guarantee a draw.
	// So we can look at the following game: candidate is trying to win, when his
	// opponent do his best to achieve a draw situation.
	bool draw = false;
	if (candidate == second) {
		for (int i = 0; i < n; ++i) {
			if (boards[i] != 5) {
				draw = true;  // we can achieve a draw;
			}
		}
	} else {
		int bad_board = -1;
		for (int i = 0; i < n; ++i) {
			if (boards[i] == 5) {
				continue;
			}
			if (bad_board == -1 && boards[i] % 5 == 0) {
				bad_board = boards[i];
			} else {
				draw = true;  // we can achieve a draw;
			}
		}
	}
	if (draw) {
		printf("%s\n", draw_string);
	} else {
		printf("%s\n", winner_string[candidate]);
	}
 	return EXIT_SUCCESS;
}
