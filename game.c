#include "game.h"

int main()
{
  int board[BOARD_HEIGHT * BOARD_WIDTH] = { EMPTY };
  int x, y;

  board[(BOARD_HEIGHT * 3) + (BOARD_WIDTH / 2) - 1] = BLACK;
  board[(BOARD_HEIGHT * 3) + (BOARD_WIDTH / 2)] = WHITE;
  board[(BOARD_HEIGHT * 4) + (BOARD_WIDTH / 2) - 1] = WHITE;
  board[(BOARD_HEIGHT * 4) + (BOARD_WIDTH / 2)] = BLACK;

  for(y = 0; y < BOARD_HEIGHT; y++)
    {
      printf("|");

      for(x = 0; x < BOARD_WIDTH; x++)
	{
	  switch(board[(y * BOARD_HEIGHT) + x])
	    {
	    case BLACK:
	      printf("%c|", B_STONE);
	      break;

	    case WHITE:
	      printf("%c|", W_STONE);
	      break;

	    case EMPTY:
	      printf("%c|", E_SPACE);
	      break;
	    }
	}

      printf("\n");
    }

  return 0;
}
