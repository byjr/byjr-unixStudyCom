OBJECTS 	:=$(patsubst %.c,%.o,$(wildcard *.c))
# OBJECTS 	:=$(EXE_TARGET:=.o)
CC			:=gcc
# INCS		+=-I/usr/src/linux-headers-4.10.0-33/include
# INCS		+=-I/usr/src/linux-headers-4.10.0-20/include
CFLAGS		:=$(INCS) -g -Werror 
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
	
	