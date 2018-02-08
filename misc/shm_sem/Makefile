CURRENT_DIR	:=`pwd`
COMPILE_DIR	:=/tmp
INSTALL_DIR	:=/usr/local
TARGET		:=$(notdir $(shell pwd))
VERSION		:=0.0
SRC_DIR		:=$(TARGET)-$(VERSION)
Q			:=@			
TARGETS		:=$(patsubst %.c,%,$(wildcard $(SRC_DIR)/*.c))

export INSTALL_DIR Q TARGETS

all:compile excute

prepare:
	rm -rf $(COMPILE_DIR)/$(SRC_DIR)
	mkdir -p $(COMPILE_DIR)
	cp -af $(SRC_DIR) $(COMPILE_DIR)	

compile:prepare
	make -C $(COMPILE_DIR)/$(SRC_DIR)
	
clean:
	make -C $(COMPILE_DIR)/$(SRC_DIR) clean
	
install:
	make -C $(COMPILE_DIR)/$(SRC_DIR) install
	
uninstall:
	make -C $(COMPILE_DIR)/$(SRC_DIR) uninstall	
	
excute:
	killall mtdaemon iflytek > /dev/null
	rm /dev/shm/sys_shm > /dev/null
	$(COMPILE_DIR)/$(SRC_DIR)/mtdaemon&
	$(COMPILE_DIR)/$(SRC_DIR)/iflytek&
	$(COMPILE_DIR)/$(SRC_DIR)/uartd