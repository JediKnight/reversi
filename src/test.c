#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int numberOfDigit(int val)
{
  int ret = 0;
  for(; val > 0; val /= 10, ret++);
  return ret;			/* return sprintf(dummy, "%d", val); */
}

int separate(int val, int digit, int targ)
{
  char v[digit];
  sprintf(v, "%d", val);
  return v[digit - targ] - '0';
}

int btod(int decimal, int val)
{
  int i, ret = 0, digit = numberOfDigit(val);
  for(i = digit - 1; i >= 0; ret += (int)pow((double)decimal, (double)i) * separate(val, digit, i + 1), i--);
  return ret;
}

int dtob(int decimal, int val)
{
  int i, ret = 0, digit = numberOfDigit(val);
  for(i = digit - 1; i >=0; ret += (val % decimal) * (int)pow((double)10, (double)1));
  return ret;
}

int main(int argc, char **argv)
{
  int org, dec;

  if(argc < 3) return -1;

  dec = atoi(argv[1]);
  org = atoi(argv[2]);

  if(dec == 10)
    printf("%d\n", btod(dec, org));
  else
    printf("%d\n", btod(2, org));

  return 0;
}
