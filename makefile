#Obsolete makefile
#TODO : Update Objects & Library
#This file is used for PSP compilation

TARGET = Solarus
OBJS = main.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Solarus Quest Launcher

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

PSP_LARGE_MEMORY = 1 
