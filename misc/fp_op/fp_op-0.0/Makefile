# OBJECTS 	:=$(patsubst %.c,%.o,$(wildcard *.c))
OBJECTS 	:=$(EXE_TARGET:=.o)
CC			?=gcc
CFLAGS		:=$(INCS) -g -O2  \
				-Wno-unused-variable \
				-Wno-comment \
				-Wall -Werror
LD			:=$(CC)
LDFLAGS		:=
LIBS		:=-lpthread -llzl -lrt

all:$(EXE_TARGET)
	
$(EXE_TARGET):$(OBJECTS)
	$(LD)  $(LDFLAGS) -o $@ $^ $(LIBS)
	
%.o:%.c
#	$(CC) $(CFLAGS) -E -o $@.c $< 
	$(CC) $(CFLAGS) -o $@ -c $< 

clean:
	rm -rf $(OBJECTS) $(EXE_TARGET)

install:
	mkdir -p $(INSTALL_DIR)/bin
	cp -rf $(EXE_TARGET) $(INSTALL_DIR)/bin	
	
uninstall:
	cp -rf  $(INSTALL_DIR)/bin/$(EXE_TARGET)
	
	