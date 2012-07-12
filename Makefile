CC=gcc

PROGRAM=game
OBJS=$(PROGRAM).o hage.o search.o network.o
SRCS=$(OBJS:%.o=%.c)
CFLAGS=-Wall -g -D_NETWORK_
LDFLAGS=

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)

clean:
	rm -f $(PROGRAM)
	rm -f $(OBJS)
