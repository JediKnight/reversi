CC=gcc

PROGRAM=game
OBJS=$(PROGRAM).o hage.o search.o
SRCS=$(OBJS:%.o=%.c)
CFLAGS=-Wall -g
LDFLAGS=

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(PROGRAM) $(OBJS) $(LDLIBS)

clean:
	rm -f $(PROGRAM)
	rm -f $(OBJS)
