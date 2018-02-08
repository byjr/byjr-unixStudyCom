
#OBJECTS 	:=$(patsubst %.c,%.o,$(wildcard *.c))
OBJECTS 	:=$(EXE_TARGET:=.o)
CC			:=gcc
CFLAGS		:=-w -g -I. 
LDFLAGS		:=-llzl -lrt -lpthread

all:$(EXE_TARGET)
	
$(EXE_TARGET):$(OBJECTS)
	$(CC)  -o $@ $^ $(LDFLAGS)
	
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
	
	