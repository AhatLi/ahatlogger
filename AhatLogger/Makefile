CC = g++
AR = ar rc
GCCVERSION = $(shell gcc --version | grep 4\\.4\\.)

INCLUDEDIR = -Iinc
SRCDIR = src
ETC = -g -lpthread
OBJDIR = obj
OBJS = ahatloggeritem.o ahatlogger.o
TARGET = libahatlogger.a
TARGETDIR = lib

ifeq "$(GCCVERSION)" ""
	ETC += -std=c++11
else
	ETC += -std=c++0x -D_GLIBCXX_USE_NANOSLEEP
endif


all : ${TARGET}

$(TARGET) : $(TARGETDIR) $(OBJS)
	$(AR) $(TARGETDIR)/$@ $(addprefix $(OBJDIR)/,$(OBJS))

$(OBJS) : $(OBJDIR)
	$(CC) -o $(OBJDIR)/$@ -c $(SRCDIR)/$(@:%.o=%.cpp) $(INCLUDEDIR) $(ETC)

$(TARGETDIR) :
	mkdir -p $(TARGETDIR)

$(OBJDIR) :
	mkdir -p $(OBJDIR)
	
clean :
	rm -rf $(OBJDIR) $(TARGETDIR)
