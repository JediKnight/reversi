#include "game.h"

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

int main(int argc, char **argv)
{
  int board[BOARD_HEIGHT * BOARD_WIDTH] = { EMPTY };
  int stone = BLACK;
  int x = 0, y = 0;
  char ipaddr[15 + 1] = { 0 };

  if(argc < 2)
    {
      fprintf(stderr, "%s [Server IP]\n", argv[0]);
      exit(EXIT_FAILURE);
    }

#ifndef _DEBUG_
  strncpy(ipaddr, argv[1], sizeof(argv[1]));
#else
  strncpy(ipaddr, "127.0.0.1", sizeof("127.0.0.1"));
#endif

  board[(BOARD_HEIGHT * 3) + (BOARD_WIDTH / 2) - 1] = BLACK;
  board[(BOARD_HEIGHT * 3) + (BOARD_WIDTH / 2)] = WHITE;
  board[(BOARD_HEIGHT * 4) + (BOARD_WIDTH / 2) - 1] = WHITE;
  board[(BOARD_HEIGHT * 4) + (BOARD_WIDTH / 2)] = BLACK;

#ifdef _NETWORK_
  puts("clisrv start");
  if(client(x, y, ipaddr) == -1)
    {
      puts("aite ga inai kara srv to shite kido");
      server(&x, &y);
      stone = reverse(stone);
    }
#endif

  printf("%d %d", x, y);

  /* main loop */
  while((scanempty(board, (sizeof(board) / sizeof(board[0])))) >= 0)
    {
    inputpos:
      dispboard(board, stone);

      printf("x: ");
      x = getinputpos();
      bufclear();
      if(x < 1 || x > 8) goto inputpos;

      printf("y: ");
      y = getinputpos();
      bufclear();
      if(y < 1 || y > 8) goto inputpos;

      if(board[getpos((x - 1), (y - 1))] == EMPTY &&
	 flip(board, stone, (x -1), (y -1)) != 0)
	{
	  board[getpos((x - 1), (y - 1))] = stone;
	}

      else
	{
	  printf("置けねーから\n");
	  sleep(1);
	  goto inputpos;
	}

#ifndef _NETWORK_
      stone = reverse(stone);
#else
      client(x, y, ipaddr);
      server(&x, &y);
      flip(board, reverse(stone), (x - 1), (y - 1));
      board[getpos((x - 1), (y - 1))] = reverse(stone);
#endif
    }

  return 0;
}
