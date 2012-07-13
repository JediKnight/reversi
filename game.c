#include "game.h"

int client_soc;
int server_soc;
char ipaddr[15 + 1] = { EMPTY };

int networkinit(int cnt, char **val, int size, char *addr)
{
  if(cnt < 2)
    {
      fprintf(stderr, "%s [Server IP]\n", val[0]);
      exit(EXIT_FAILURE);
    }

  strncpy(addr, val[1], size);

  return 0;
}

int gameinit(int *b)
{
  b[(BOARD_HEIGHT * 3) + (BOARD_WIDTH / 2) - 1] = BLACK;
  b[(BOARD_HEIGHT * 3) + (BOARD_WIDTH / 2)] = WHITE;
  b[(BOARD_HEIGHT * 4) + (BOARD_WIDTH / 2) - 1] = WHITE;
  b[(BOARD_HEIGHT * 4) + (BOARD_WIDTH / 2)] = BLACK;

  return 0;
}

int selectcolor(int *stn)
{
  int x, y;

  x = y = 0;

#ifdef _NETWORK_
  if(client(client_soc, x, y, ipaddr) == -1)
    {
      puts("wait...");
      server(server_soc, &x, &y);
      *stn = reverse(*stn);
    }
#endif	/* _NETWORK_ */

  return 0;
}


int mytrun(int *b, int stn)
{
  int x, y;

  x = y = 0;

  printf("x: ");
  x = getinputpos();
  bufclear();
  if(x < 1 || x > 8) return -1;
  
  printf("y: ");
  y = getinputpos();
  bufclear();
  if(y < 1 || y > 8) return -1;
  
  if(b[getpos((x - 1), (y - 1))] == EMPTY &&
     flip(b, stn, (x -1), (y -1)) != 0)
    {
      b[getpos((x - 1), (y - 1))] = stn;
      
#ifdef _NETWORK_
      client(client_soc, x, y, ipaddr);
#endif	/* _NETWORK_ */
    }

  else
    {
      printf("置けねーから\n");
      sleep(1);
      return -1;
    }

  return 0;
}

int enemytrun(int *b, int stn)
{
  int x, y;

  x = y = 0;

#ifdef _NETWORK_
  server(server_soc, &x, &y);
  fprintf(stdout, "%d:%d", x, y);
  sleep(10);
  flip(b, reverse(stn), (x - 1), (y - 1));
  b[getpos((x - 1), (y - 1))] = reverse(stn);
#else
  stone = reverse(stone);
#endif	/* _NETWORK_ */
  
  return 0;
}

int main(int argc, char **argv)
{
  int board[BOARD_HEIGHT * BOARD_WIDTH] = { EMPTY };
  int stone = BLACK;
  int turn = stone;
  int x = 0, y = 0;

#ifdef _NETWORK_
  int clntsoc = getsoc();
  int servsoc = getsoc();
  char ipaddr[15 + 1] = { 0 };

  networkinit(argc, argv, sizeof(argv[1]), ipaddr);
#endif	/* _NETWORK_ */

  gameinit(board);
  selectcolor(&stone);

  /* game start */
  while((scanempty(board, (sizeof(board) / sizeof(board[0])))) >= 0)
    {
    start:
      dispboard(board, stone);

      if(turn == stone)
	{
  if(mytrun(board, stone) == -1) goto start;
	}

      else
	{
  enemytrun(board, stone);
	}

      turn = reverse(stone);
    }

  closesoc(clntsoc);
  closesoc(servsoc);

  return 0;
}
