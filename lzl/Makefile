CURRENT_DIR	:=`pwd`
COMPILE_DIR	:=/tmp
INSTALL_DIR	:=/usr/local
TARGET		:=$(notdir $(shell pwd))
VERSION		:=1.0
SRC_DIR		:=$(TARGET)-$(VERSION)
Q			:=@
SO_TARGET	:=lib$(TARGET).so

export INSTALL_DIR Q TARGET SO_TARGET 

all:compile

prepare:
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
	