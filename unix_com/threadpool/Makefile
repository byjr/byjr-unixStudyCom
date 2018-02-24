CURRENT_DIR	:=`pwd`
COMPILE_DIR	:=/tmp
INSTALL_DIR	:=/usr/local
TARGET		:=$(notdir $(shell pwd))
VERSION		:=1.0
SRC_DIR		:=$(TARGET)-$(VERSION)
Q			:=@			
EXE_TARGET	:=$(TARGET)_$(p0)

export INSTALL_DIR Q EXE_TARGET

all:compile excute

prepare:
	rm -rf $(COMPILE_DIR)/$(SRC_DIR)
	mkdir -p $(COMPILE_DIR) && cp -af $(SRC_DIR) $(COMPILE_DIR)	

compile:prepare
	make -C $(COMPILE_DIR)/$(SRC_DIR)
	
clean:
	make -C $(COMPILE_DIR)/$(SRC_DIR) clean
	
install:
	make -C $(COMPILE_DIR)/$(SRC_DIR) install
	
uninstall:
	make -C $(COMPILE_DIR)/$(SRC_DIR) uninstall	
	
excute:
	$(COMPILE_DIR)/$(SRC_DIR)/$(EXE_TARGET) $(p1) $(p2) $(p3) $(p4) $(p5) $(p6)