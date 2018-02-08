EXE_TARGETS		:=$(patsubst %.c,%.exe,$(wildcard *.c))
UTILS_OBJS	:=$(patsubst %.c,%.o,$(wildcard utils/*.c))
INCS		:=-I./utils
CC			?=gcc
CFLAGS		:=$(INCS) -g -Os  \
				-Wno-unused-variable \
				-Wno-comment \
				-Wno-unused-result \
				-Wall \
				-Werror
LD			:=$(CC)
LDFLAGS		:=
LIBS		:=-lpthread -llzl -lrt

all:$(EXE_TARGETS)	
	
%.exe:%.o $(UTILS_OBJS)
	$(LD)  $(LDFLAGS) -o $@ $^ $(LIBS) \
	&& mv $@ $(basename $@)
	
%.o:%.c
#	$(CC) $(CFLAGS) -E -o $@.c $< 
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	rm -rf $(UTILS_OBJS) $(EXE_TARGETS) *.o

install:
	mkdir -p $(INSTALL_DIR)/bin
	cp -rf $(EXE_TARGETS) $(INSTALL_DIR)/bin	
	
uninstall:
	cp -rf  $(INSTALL_DIR)/bin/$(EXE_TARGETS)
	