#include "search.h"

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
