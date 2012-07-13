#include "network.h"

int getsocket()
{
  int soc;

  if((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      perror("socket");
      return -1;
    }

  return soc;
}

int closesocket(int soc)
{
  close(soc);
  return 0;
}

int recvdata(int soc, int accept_soc, char *data)
{
  socklen_t sin_size = sizeof(struct sockaddr_in);
  struct sockaddr_in addr;
  struct sockaddr_in from_addr;

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  if(accept_soc < 0) goto listen;

  if(bind(soc, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
    { 
      perror("bind"); 
      return -1; 
    }

 listen:
  if(listen(soc, 10) < 0) 
    { 
      perror("listen"); 
      return -1; 
    }

  if((accept_soc = accept(soc, (struct sockaddr *)&from_addr, &sin_size)) < 0) 
    { 
      perror("accept"); 
      return -1; 
    }

  memset(data, 0, sizeof(data));

  if(recv(accept_soc, data, sizeof(data), 0) < 0) 
    { 
      perror("recv"); 
      return -1; 
    }

  return accept_soc;
}

int senddata(int soc, int x, int y, char *ipaddr)
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
