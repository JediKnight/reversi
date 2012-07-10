#include "hage.h"

int scanempty(int *b, int size)
{
  int i;

  for(i = 1; i <= size; i++) if(b[i] == EMPTY) return i;
  return 0;
}
