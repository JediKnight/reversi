#include "network.h"

int getsoc()
{
  int soc;

  if((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
      perror("socket");
      return -1;
    }

  return soc;
}

int closesoc(int soc)
{
  close(soc);

  return 0;
}

int initnetwork()
{
  int accsoc;
  socklen_t sin_size = sizeof(struct sockaddr_in);
  struct sockaddr_in addr;
  struct sockaddr_in from_addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  if(bind(soc, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    {
      perror("bind");
      return -1;
    }

  if(listen(soc, 10) < 0) 
    {
      perror("listen");
      return -1;
    }

  if((accsoc = accept(soc, (struct sockaddr *)&from_addr, &sin_size)) < 0) 
    {
      perror("accept");
      return -1;
    }

  return 0;
}

int getdata(int soc, int *x, int *y)
{
  char buf[2 + 1];

  memset(buf, 0, sizeof(buf));
 
  if(recv(accsoc, buf, sizeof(buf), 0) < 0) 
    {
      perror("recv");
      return -1;
    }

  *x = buf[0];
  *y = buf[1];

  return 0;
}

int client(int soc, int x, int y, char *ipaddr)
{
  struct sockaddr_in addr;
  char msg[3 + 1];

  memset(msg, 0, sizeof(msg) / sizeof(msg[0]));
  sprintf(msg, "%d%d", x, y);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr(ipaddr);

  if(connect(soc, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0)
    {
      perror("connect");
      return -1;
    }

  if(send(soc, msg, sizeof(msg) / sizeof(msg[0]), 0) < 0) 
    {
      perror("send");
      return -1;
    }

  return 0;
}
