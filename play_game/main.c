
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "oware.h"

const int HOUSE_COUNT = 12;

// see oware.h
void oware_new_game(struct oware_board *board) {
  assert(board);
  for (int i = 0; i < 12; ++i) {
    board->houses[i] = 4;
  }
  for (int i = 0; i < 2; ++i) {
    board->scores[i] = 0;
  }
  board->turn = 1;
}

// see oware.h
int oware_seed_count(const struct oware_board *board, int player) {
  assert(player == 1 || player == 2);
  assert(board);
  int result = 0;
  if (player == 1) {
    for (int i = 0; i < 6; ++i) {
      result += board->houses[i];
    }
  }
  if (player == 2) {
    for (int i = 6; i < 12; ++i) {
      result += board->houses[i];
    }
  }
  return result;// REPLACE ME
}

// own_hourse(board, house) determines if the house is owed by the player
// requires: board is valid 
//           house is between 0 (house A) and 11 (house L)
static bool own_house(const struct oware_board *board, int house) {
  assert(board);
  if (board->turn == 1) {
    return (0 <= house && house <= 5);
  } else  {
    return (6 <= house && house <= 11);
  }
}

// valid_oppo_no_seed(board, house) determines if the move 
//  is valid when the opponent has no seed
// requires: board is valid 
//           house is between 0 (house A) and 11 (house L)
static bool valid_oppo_no_seed(const struct oware_board *board, int house) {
  assert(board);
  assert(0 <= house && house <= 11);
  if (board->turn == 1) {
    if (oware_seed_count(board, 2) == 0) {
      return board->houses[house] >= 6 - house;
    }
  } else {
    if (oware_seed_count(board, 1) == 0) {
      return board->houses[house] >= 12 - house;
    }
  }
  return true;
}

// see oware.h
bool oware_valid_move(const struct oware_board *board, int house) {
  assert(board);
  assert(0 <= house && house <= 11);
  return (own_house(board, house) && 
          board->houses[house] > 0 &&
          valid_oppo_no_seed(board, house));  
}

// see oware.h
void oware_make_move(struct oware_board *board, int house) {
  assert(oware_valid_move);
  assert(board);
  assert(0 <= house && house <= 11);
  int player = board->turn;
  int seed = board->houses[house];
  board->houses[house] = 0;
  int i = house + 1;
  int dis = 0;

  while (seed > 0) {
    if (i == 12) {
      i = 0;
    }
    if (dis != 11) {
      ++board->houses[i];
      --seed;
      ++i;
      ++dis;
    } else {
      ++i;
      ++dis;
    }
  }
  int last = i - 1;
  if (last == -1) {
    last = 11;
  }
  // capture seed if possible and set board->house to 0
  int backwards = last;
  while (1) {   
    if (backwards == -1) {
      backwards = 11;
    }
    if ((board->houses[last] == 2 || 
         board->houses[last] == 3) 
        && (own_house(board,last))) {
      break;
    }  
    if (board->houses[backwards] == 2 || 
        board->houses[backwards] == 3) {
      if (player == 1 && 
          (6 <= backwards && backwards <= 11)) {
        if (oware_seed_count(board, 2) == 
            board->houses[backwards]) {
          break;
        } else {
          board->scores[0] += board->houses[backwards];
          board->houses[backwards] = 0;
        }
      }  
      if (player == 2 && 
          (0 <= backwards && backwards <= 5)) {
        if (oware_seed_count(board, 1) == 
            board->houses[backwards]) {
          break;
        } else {
          board->scores[1] += board->houses[backwards];
          board->houses[backwards] = 0;
        }
      }
    } else {
      break;
    }
    --backwards;
  }

  if (player == 1) {
    board->turn = 2;
  } else {
    board->turn = 1;
  }
}

// see oware.h
bool oware_game_over(const struct oware_board *board) {
  assert(board);
  if (board->scores[0] >= 25 || 
      board->scores[1] >= 25) {
    return true;
  }
  int result = 1;
  if (board->turn == 1) {
    for (int i = 0; i < 6; ++i) {
      if (oware_valid_move(board, i)) {
        result = 0;
      } 
    }
  } else {
    for (int i = 6; i < 12; ++i) {
      if (oware_valid_move(board, i)) {
        result = 0;
      } 
    }
  }
  return result; // REPLACE ME
}


// see oware.h
void oware_end_game(struct oware_board *board) {
  assert(board);
  board->scores[0] += oware_seed_count(board,1);
  board->scores[1] += oware_seed_count(board,2);
  for (int i = 0; i < 12; ++i) {
    board->houses[i] = 0;
  }
}





// draw_lines() draws a +--+ line on the screen
// effects: outputs a line of text

static void draw_lines(void) {
  for (int i = 0; i < HOUSE_COUNT / 2; ++i) {
    printf("+--"); 
  }
  printf("+\n");
}

// draw_labels(player) draws the house labels for player
//  (A-F for player 1, G-L for player 2)
// requires: player is 1 or 2
// effects: ouputs a line of text

static void draw_labels(int player) {
  for (int i = 0; i < HOUSE_COUNT / 2; ++i) {
    int house;
    if (player == 1) {
      house = i;
    } else {
      house = HOUSE_COUNT - i - 1;
    }
    printf(" %c ", 'A' + house); 
  }
  printf("\n");
}

// see oware.h
void oware_draw(const struct oware_board *board) {
  draw_labels(2);
  draw_lines();
  for (int i = 0; i < HOUSE_COUNT / 2; ++i) {
    printf("|%2d", board->houses[HOUSE_COUNT - 1 - i]); 
  }
  printf("|\n");
  draw_lines();
  for (int i = 0; i < HOUSE_COUNT / 2; ++i) {
    printf("|%2d", board->houses[i]); 
  }
  printf("|\n");
  draw_lines();
  draw_labels(1);
  printf("\n");
  printf("Player 1: %d\n", board->scores[0]);
  printf("Player 2: %d\n", board->scores[1]); 
}
