TAGERTS	=$(in)
#SRCS	= $(TAGERTS:=.c)
INC		= -I.
#CC		= /usr/local/arm/arm-2009q3/bin/arm-none-linux-gnueabi-gcc
CC		= /usr/bin/gcc
CFLAGS	= -Wall -lpthread
#OBJS	= $(TAGERTS:=.o)

all:$(TAGERTS)
%:%.c
	$(CC) -o $@ $< $(CFLAGS)

#%.o:%.c
#	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(TAGERTS) 