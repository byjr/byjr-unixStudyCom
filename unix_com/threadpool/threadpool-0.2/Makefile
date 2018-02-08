
#OBJECTS 	:=$(patsubst %.c,%.o,$(wildcard *.c))
OBJECTS 	:=$(EXE_TARGET:=.o)
CC			:=gcc
INCS		:=
CFLAGS		:=$(INCS) -g -Werror 
LDFLAGS		:=
LIBS		:=-lpthread -llzl -lrt

all:$(EXE_TARGET)
	
$(EXE_TARGET):$(OBJECTS)
	$(CC)  -o $@ $^ $(LIBS)
	
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
	
	