#ifndef _HAGE_H_
#define _HAGE_H_

#include <stdio.h>

#include "data.h"

#define getpos(x,y) ((y * BOARD_HEIGHT) + x)
#define reverse(c) (c * -1)
#define getinputpos() (getchar() - 48);
#define bufclear() while(getchar() != '\n')

void dispboard(int *b, int s);

#endif	/* _HAGE_H_ */
