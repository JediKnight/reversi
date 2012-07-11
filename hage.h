#ifndef _HAGE_H_
#define _HAGE_H_

#include "data.h"

#define getpos(x,y) ((y * BOARD_HEIGHT) + x)
#define reverse(c) (c * -1)
#define getinputpos() (getchar() - 48);
#define bufclear() while(getchar() != '\n')

int scanempty(int *b, int size);

#endif	/* _HAGE_H_ */
