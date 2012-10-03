#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "main.h"
#include "data.h"






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
  printf("Black:%d\nWhite:%d\ncolor> ", BLACK, WHITE + 1);
  *stn = getinputpos();
  bufclear();
  if(*stn != BLACK) *stn = WHITE;
  return 0;
}

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

int scanempty(int *b, int size)
{
  int i;

  for(i = 1; i <= size; i++) if(b[i] == EMPTY) return i;
  return 0;
}

int flip(int *b, int s, int x, int y)
{
  int xx, yy, xxx, yyy, flg = 0;

  /* x から右にサーチ */
  if(b[getpos((x + 1), y)] == reverse(s))
    {
      for(xx = x + 1; xx < BOARD_WIDTH; xx++)
	{
	  if(b[getpos(xx, y)] == s)
	    {
	      for(xxx = x + 1; xxx < xx; xxx++)
		b[getpos(xxx, y)] = s;
	      flg++;
	      break;
	    }
	}
    }

  /* x から左にサーチ */
  if(b[getpos((x - 1), y)] == reverse(s))
    {
      for(xx = x - 1; xx >= 0; xx--)
	{
	  if(b[getpos(xx, y)] == s)
	    {
	      for(xxx = x - 1; xxx >= xx; xxx--)
		b[getpos(xxx, y)] = s;
	      flg++;
	      break;
	    }
	}
    }

  /* y から下にサーチ */
  if(b[getpos(x, (y + 1))] == reverse(s))
    {
      for(yy = y + 1; yy < BOARD_HEIGHT; yy++)
	{
	  if(b[getpos(x, yy)] == s)
	    {
	      for(yyy = y + 1; yyy < yy; yyy++)
		b[getpos(x, yyy)] = s;
	      flg++;
	      break;
	    }
	}
    }

  /* y から上にサーチ */
  if(b[getpos(x, (y - 1))] == reverse(s))
    {
      for(yy = y - 1; yy >= 0; yy--)
	{
	  if(b[getpos(x, yy)] == s)
	    {
	      for(yyy = y - 1; yyy >= yy; yyy--)
		b[getpos(x, yyy)] = s;
	      flg++;
	      break;
	    }
	}
    }

  /* xy から右下にサーチ */
  if(b[getpos((x + 1), (y + 1))] == reverse(s))
    {
      for(xx = x + 1, yy = y + 1; xx < BOARD_WIDTH && yy < BOARD_HEIGHT; xx++, yy++)
	{
	  if(b[getpos(xx, yy)] == s)
	    {
	      for(xxx = x + 1, yyy = y + 1; xxx < xx && yyy < yy; xxx++, yyy++)
		b[getpos(xxx, yyy)] = s;
	      flg++;
	      break;
	    }
	}
    }

  /* xy から左下にサーチ */
  if(b[getpos((x - 1), (y + 1))] == reverse(s))
    {
      for(xx = x - 1, yy = y + 1; xx >= 0 && yy < BOARD_HEIGHT; xx--, yy++)
	{
	  if(b[getpos(xx, yy)] == s)
	    {
	      for(xxx = x - 1, yyy = y + 1; xxx >= xx && yyy < yy; xxx--, yyy++)
		b[getpos(xxx, yyy)] = s;
	      flg++;
	      break;
	    }
	}
    }

  /* xy から右上にサーチ */
  if(b[getpos((x + 1), (y - 1))] == reverse(s))
    {
      for(xx = x + 1, yy = y - 1; xx < BOARD_WIDTH && yy >= 0; xx++, yy--)
	{
	  if(b[getpos(xx, yy)] == s)
	    {
	      for(xxx = x + 1, yyy = y - 1; xxx < xx && yyy >= yy; xxx++, yyy--)
		b[getpos(xxx, yyy)] = s;
	      flg++;
	      break;
	    }
	}
    }

  /* xy から左上にサーチ */
  if(b[getpos((x - 1), (y - 1))] == reverse(s))
    {
      for(xx = x - 1, yy = y - 1; xx >= 0 && yy >= 0; xx--, yy--)
	{
	  if(b[getpos(xx, yy)] == s)
	    {
	      for(xxx = x - 1, yyy = y - 1; xxx >= xx && yyy >= yy; xxx--, yyy--)
		b[getpos(xxx, yyy)] = s;
	      flg++;
	      break;
	    }
	}
    }

  return flg;
}

int myturn(int *b, int stn)
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
     flip(b, stn, (x - 1), (y - 1)) != 0)
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


int eval(int *b)
{
  int x, y, val = 0;

  for(y = 0; y < BOARD_HEIGHT; y++)
    {
      for(x = 0; x < BOARD_WIDTH; x++)
	{
	  val += (val_table[getpos(x, y)] * b[getpos(x, y)]);
	}
    }

  return val;
}


/* int ab(int *b, int lv, int al, int be) */
/* { */
/*   int val; */

/*   if(lv == 0)return 評価値(盤面); */

/*   while(打てる手がある){ */
/*     手を差して次の盤面を作る; */
/*     val = -ab(b, lv - 1, -be, -al); */
/*     盤面を１手戻す; */
/*     //枝狩り */
/*     if(val >= be)return al; */
/*     //最高値 */
/*     if(al < val)al = val; */
/*   } */
/*   return al; */
/* } */

int enemyturn(int *b, int stn)
{
  int pos = eval(b) * stn;
  int y = pos / BOARD_HEIGHT;
  int x = pos % BOARD_WIDTH - 1;

  printf("pos = %d, y = %d, x = %d\n", pos, y, x);
  sleep(3);

  if(b[pos] == EMPTY && flip(b, stn, x, y) != 0)
    { b[pos] = stn; }

  return 0;
}

int main(int argc, char **argv)
{
  int board[BOARD_HEIGHT * BOARD_WIDTH] = { EMPTY };
  int stone = BLACK;
  int turn = stone;
  int i, ret = 0;

  gameinit(board);
  selectcolor(&stone);

  /* game start */
  while((scanempty(board, (sizeof(board) / sizeof(board[0])))) >= 0)
    {
    start:
      dispboard(board, turn);

      if(turn == stone)
	{
	  if(myturn(board, stone) == -1) goto start;
	}

      else
	{
	  enemyturn(board, stone);
	  sleep(3);
	}
      
      turn = reverse(turn);
      printf("stone:%d, turn:%d\n", stone, turn);
    }

  for(i = 0; i < (sizeof(board) / sizeof(board[0])); ret += board[i++]);
  if(ret > 0)
    {
      puts("win Black!!");
    }

  else if(ret < 0)
    {
      puts("win White!!");
    }

  else
    {
      puts("draw...");
    }
  
  return 0;
}
