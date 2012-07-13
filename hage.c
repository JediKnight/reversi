#include "hage.h"

void dispboard(int *b, int s)
{
  int x, y;

  printf("\033[2J");

  switch(s)
    {
    case BLACK:
      printf("stone: BLACK(b)\n");
      break;

    case WHITE:
      printf("stone: WHITE(w)\n");
      break;
    }

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
