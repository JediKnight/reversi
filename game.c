#include "game.h"

void dispboard(int *b)
{
  int x, y;

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
  /* int x, y, tmp; */
  char x[1], y[1], tmp;

  board[(BOARD_HEIGHT * 3) + (BOARD_WIDTH / 2) - 1] = BLACK;
  board[(BOARD_HEIGHT * 3) + (BOARD_WIDTH / 2)] = WHITE;
  board[(BOARD_HEIGHT * 4) + (BOARD_WIDTH / 2) - 1] = WHITE;
  board[(BOARD_HEIGHT * 4) + (BOARD_WIDTH / 2)] = BLACK;

  dispboard(board);

  /* main loop */
  while((scanempty(board, (sizeof(board) / sizeof(board[0])))) > 0)
    {
      /* x[0] = y[0] = '\0'; */

      printf("x: ");
      /* scanf("%[1-8]", x); */
      tmp = getchar();
      sscanf(&tmp, "%[1-8]", x);

      printf("y: ");
      /* scanf("%[1-8]", y); */
      tmp = getchar();
      sscanf(&tmp, "%[1-8]", y);

      /* printf("%d %d", x, y); */
      /* board[getpos((x - 1), (y - 1))] = stone; */
      stone = reverse(stone);

      dispboard(board);
    }

  return 0;
}
