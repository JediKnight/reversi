#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int nofd(int val)
{
  int ret = 0;
  for(; val > 0; val /= 10, ret++);
  return ret;			/* return sprintf(dummy, "%d", val); */
}

int numsep(int val, int digit, int targ)
{
  char v[digit];
  sprintf(v, "%d", val);
  return v[digit - targ] - '0';
}

int btod(int dec, int val)
{
  int i, ret = 0, digit = nofd(val);
  for(i = digit - 1; i >= 0; ret += (int)pow((double)dec, (double)i) * numsep(val, digit, i + 1), i--);
  return ret;
}

int dtob(int dec, int val)
{
  int quo = val, rem = val, ret = 0;

  for(;(quo /= dec) > 0;)
    {
      ret *= 10;
      rem %= dec;
      printf("%d %d\n", quo, rem);
      ret += rem;
      rem = quo;
    }
  return ret;
}

int main(int argc, char **argv)
{
  int orig, decimal;

  if(argc < 3) return -1;

  decimal = atoi(argv[1]);
  orig = atoi(argv[2]);

  if(decimal == 10)
    printf("%d\n", btod(decimal, orig));
  else
    printf("%016d\n", dtob(decimal, orig));

  return 0;
}
