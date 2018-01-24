CC			:=gcc -fPIC
OBJECTS 	:=$(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS		:=-Werror -g -fno-builtin 
LDFLAGS		:=-shared
INSTALL_DIR	:=/usr/local

all:$(SO_TARGET) 

$(SO_TARGET):$(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^ 
	
%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $< 
	
clean:
	rm -rf $(OBJECTS) $(SO_TARGET)

install:
	mkdir -p $(INSTALL_DIR)/include/$(TARGET)
	cp -rf *.h $(INSTALL_DIR)/include/$(TARGET)
	mkdir -p $(INSTALL_DIR)/lib
	cp -rf $(SO_TARGET) $(INSTALL_DIR)/lib
	$(Q)echo "export LD_LIBRARY_PATH=$(INSTALL_DIR)/lib:$(LD_LIBRARY_PATH)"
	
uninstall:
	rm -rf 	$(INSTALL_DIR)/include/$(TARGET)
	rm -rf  $(INSTALL_DIR)/lib/$(SO_TARGET)		


		