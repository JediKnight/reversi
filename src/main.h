#ifndef _GAME_H_
#define _GAME_H_

#include "data.h"

#define getpos(x,y) ((y * BOARD_HEIGHT) + x)
#define reverse(c) (c * -1)
#define getinputpos() (getchar() - 48);
#define bufclear() while(getchar() != '\n')

#endif	/* _GAME_H_ */
