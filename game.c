#include "game.h"

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
  stn = getinputpos();
  bufclear();

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
  return 0;
}

int main(int argc, char **argv)
{
  int board[BOARD_HEIGHT * BOARD_WIDTH] = { EMPTY };
  int stone = BLACK;
  int turn = stone;

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
	  // ai
	  enemytrun(board, stone);
	}
      
      turn = reverse(stone);
      printf("stone:%d, turn:%d\n", stone, turn);
      sleep(3);
    }
  
  return 0;
}
