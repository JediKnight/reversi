#include "game.h"

void dispboard(int *b)
{
  int x, y;

  printf("\033[2J");
  printf("  1 2 3 4 5 6 7 8\n");

  for(y = 0; y < BOARD_HEIGHT; y++)
    {
      printf("%d|", y + 1);

      for(x = 0; x < BOARD_WIDTH; x++)
	{
	  switch(b[getpos(x, y)])
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
}

int main()
{
  int board[BOARD_HEIGHT * BOARD_WIDTH] = { EMPTY };
  int stone = BLACK;
  int x, y;

  board[(BOARD_HEIGHT * 3) + (BOARD_WIDTH / 2) - 1] = BLACK;
  board[(BOARD_HEIGHT * 3) + (BOARD_WIDTH / 2)] = WHITE;
  board[(BOARD_HEIGHT * 4) + (BOARD_WIDTH / 2) - 1] = WHITE;
  board[(BOARD_HEIGHT * 4) + (BOARD_WIDTH / 2)] = BLACK;

  /* main loop */
  while((scanempty(board, (sizeof(board) / sizeof(board[0])))) > 0)
    {
    inputpos:
      dispboard(board);

      printf("x: ");
      x = getchar() - 48;
      bufclear();
      if(x < 1 || x > 8) goto inputpos;

      printf("y: ");
      y = getchar() - 48;
      bufclear();
      if(y < 1 || y > 8) goto inputpos;

      if(board[getpos((x - 1), (y - 1))] == EMPTY &&
	 scanmycolor(board, stone, (x -1), (y -1)) != 0)
	board[getpos((x - 1), (y - 1))] = stone;

      stone = reverse(stone);
    }

  return 0;
}
