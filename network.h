#ifndef _NETWORK_H_
#define _NETWORK_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 19860

int server(int *x, int *y);
int client(int x, int y, char *ipaddr);

#endif /* _NETWORK_H_ */
