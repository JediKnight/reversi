#include "network.h"

int server(int *x, int *y)
{
  int soc;
  int accsoc;
  socklen_t sin_size = sizeof(struct sockaddr_in);
  struct sockaddr_in addr;
  struct sockaddr_in from_addr;
  char buf[2048];
  char *tmp;

  memset(buf, 0, sizeof(buf));

  if((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "socket");
    return -1;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;

  if(bind(soc, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    fprintf(stderr, "bind");
    return -1;
  }

  if(listen(soc, 10) < 0) {
    fprintf(stderr, "listen");
    return -1;
  }

  if((accsoc = accept(soc, (struct sockaddr *)&from_addr, &sin_size)) < 0) {
    fprintf(stderr, "accept");
    return -1;
  }
 
  if(recv(accsoc, buf, sizeof(buf), 0) < 0) {
    fprintf(stderr, "recv");
    return -1;
  }

  tmp = strtok(buf, ":");
  *x = atoi(tmp);
  tmp = strtok(NULL, ":");
  *y = atoi(tmp);

  close(accsoc);
  close(soc);

  return 0;
}

int client(int x, int y, char *ipaddr)
{
  int soc;
  struct sockaddr_in addr;
  char msg[3 + 1] = { 0 };

  sprintf(msg, "%d:%d", x, y);

  if((soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    fprintf(stderr, "socket");
    return -1;
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = inet_addr(ipaddr);

  connect(soc, (struct sockaddr *)&addr, sizeof(struct sockaddr_in));

  if(send(soc, msg, strlen(msg), 0) < 0) {
    fprintf(stderr, "send");
    return -1;
  }

  close(soc);

  return 0;
}
