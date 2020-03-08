// SEASHELL_READONLY

#include <stdbool.h>

// This will be 12, but you know our feelings on magic numbers
extern const int HOUSE_COUNT;

struct oware_board {
  int houses[12]; 
  int scores[2];
  int turn;
};
// requires: turn is 1 or 2
//           houses and scores add to 48


// All times are O(1) since the board has a fixed size.
// All struct oware_board * are required to be valid (not NULL)

// oware_new_game(board) sets board up for a new game
//   i.e. sets each house to 4, scores to 0, and turn to 1
// effects: board is mutated
void oware_new_game(struct oware_board *board);

// oware_seed_count(board, player) returns how many seeds are in player's houses
//  (NOT how many they have captured!)
// requires: player is 1 or 2
int oware_seed_count(const struct oware_board *board, int player);

// oware_valid_move(board, house) returns true if the player whose turn it is
//  can pick the given house, false otherwise.
// requires: house is between 0 (house A) and 11 (house L)
bool oware_valid_move(const struct oware_board *board, int house);

// oware_make_move(board, house) picks the given house and sows its seeds
// requires: house is between 0 (house A) and 11 (house L)
//           the move is a legal move (oware_valid_move returns true)
// effects: houses and turn will be updated
//          scores may be updated
void oware_make_move(struct oware_board *board, int house);

// oware_game_over(board) returns true if the game is over, false if not
//  a game is over if it cannot continue (current player has no valid moves)
//  or if a player has already won (has captured more than half of the seeds)
bool oware_game_over(const struct oware_board *board);

// oware_end_game(board) ends the game by capturing all houses for the player
//  that owns them.
// effects: houses and scores will be updated
void oware_end_game(struct oware_board *board);

// oware_draw(board) prints the board and current scores.
//  Player 1 is drawn at the bottom, and Player 2 on top.
// effects: prints output
void oware_draw(const struct oware_board *board);
