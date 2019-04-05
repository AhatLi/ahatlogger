CC = g++
GCCVERSION = $(shell gcc --version | grep 4\\.4\\.)

INCLUDEDIR = -I../inc
ETC = -g
LIBDIR = -L../lib
LIB = -lahatlogger -lpthread
SRC = main.cpp
TARGET = sample

ifeq "$(GCCVERSION)" ""
        ETC += -std=c++11
else
        ETC += -std=c++0x -D_GLIBCXX_USE_NANOSLEEP
endif


all : ${TARGET}

$(TARGET) : main.cpp
	$(CC) -o $@ $(SRC) $(INCLUDEDIR) $(LIBDIR) $(LIB) $(ETC)

clean :
	rm -f $(TARGET)
