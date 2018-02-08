TAGERTS	= cap-dis
#SRCS	= $(TAGERTS:=.c)
INC		= -I.
CC		= /usr/bin/gcc
CFLAGS	= -Wall
#OBJS	= $(TAGERTS:=.o)

all:$(TAGERTS)
	
%:%.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -rf $(TAGERTS) *.o