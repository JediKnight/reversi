#ifndef _HAGE_H_
#define _HAGE_H_

#include "data.h"

#define getpos(x,y) ((y * BOARD_HEIGHT) + x)
#define reverse(c) (c * -1)

int scanempty(int *b, int size);

#endif	/* _HAGE_H_ */
