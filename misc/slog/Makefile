CURRENT_DIR	:=`pwd`
COMPILE_DIR	:=/tmp
INSTALL_DIR	:=/usr/local
TARGET		:=$(notdir $(shell pwd))
VERSION		:=0.2
SRC_DIR		:=$(TARGET)-$(VERSION)
Q			:=@

export INSTALL_DIR Q TARGET

all:compile

prepare:
	rm -rf $(COMPILE_DIR)/$(SRC_DIR)
	mkdir -p $(COMPILE_DIR)
	cp -af $(SRC_DIR) $(COMPILE_DIR)	

compile:prepare
	make -C $(COMPILE_DIR)/$(SRC_DIR) compile
	
clean:
	make -C $(COMPILE_DIR)/$(SRC_DIR) clean
	
install:
	make -C $(COMPILE_DIR)/$(SRC_DIR) install
	
uninstall:
	make -C $(COMPILE_DIR)/$(SRC_DIR) uninstall
	
ttt:
	$(Q)echo $(CURRENT_DIR)
	$(Q)echo $(notdir $(shell pwd))