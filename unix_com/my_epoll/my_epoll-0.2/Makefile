
#OBJECTS 	:=$(patsubst %.c,%.o,$(wildcard *.c))
OBJECTS 	:=$(EXE_TARGET:=.o)
CC			:=gcc
CFLAGS		:=-Wall -Werror -g -I. 
LDFLAGS		:=-llzl -lpthread -lrt

all:$(EXE_TARGET)	
	
$(EXE_TARGET):$(OBJECTS)
	$(CC)  -o $@ $^ $(LDFLAGS)
	
%.o:%.c
	$(CC) $(CFLAGS) -c -o $@ $< 
	
clean:
	rm -rf $(OBJECTS) $(EXE_TARGET)

install:
	mkdir -p $(INSTALL_DIR)/bin
	cp -rf $(EXE_TARGET) $(INSTALL_DIR)/bin	
	
uninstall:
	cp -rf  $(INSTALL_DIR)/bin/$(EXE_TARGET)	