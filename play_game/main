//
//  main.c
//  Oware
//
//  Created by Christinaflz on 2020-03-08.
//  Copyright © 2020 Christinaflz. All rights reserved.
//

#include "oware.h"
#include <stdio.h>


int main(void) {
  struct oware_board board;
  oware_new_game(&board);

  while (!(oware_game_over(&board))) {
    oware_draw(&board);
    if (board.turn == 1) {
      printf("Player 1, enter house ID (A - F)\n");
    } else {
      printf("Player 2, enter house ID (G - L)\n");
    }

    char c;
    if (scanf(" %c", &c) != 1) {
      break;
    }
    if (c >= 'A' && c <= 'Z') {
      c += ('a' - 'A');
    }
    if (c >= 'a' && c <= 'l') {
      if (!oware_valid_move(&board, c - 'a')) {
        printf("Illegal Move!\n");
      } else {
        oware_make_move(&board, c - 'a');
      }
    } else {
      printf("Invalid House ID\n");
    }
  }
  oware_end_game(&board);
  int score = board.scores[0] - board.scores[1];
  printf("Game Over\n");
  if (score == 0) {
    printf("It's a tie!\n");
  } else if (score > 0) {
    printf("Player 1 Wins!\n");
  } else {
    printf("Player 2 Wins!\n");
  }


}

