#############
# Variables #
#############
SRCDIR = src
BINDIR = bin
OBJDIR = $(BINDIR)\obj
CFLAGS = -Wall -O2
OBJS = $(OBJDIR)\test.o \
	   $(OBJDIR)\main.o \
	   $(OBJDIR)\matrix.o \
	   $(OBJDIR)\csv.o


########
# Misc #
########
.PHONY: clean


###########
# Targets #
###########
all: $(OBJS)
all: $(BINDIR)\\matrix.exe

debug: CFLAGS += -g
debug: $(OBJS)
debug: $(BINDIR)\\matrix.exe

$(BINDIR)\\matrix.exe: $(OBJS)
	gcc $^ -o $@

$(OBJDIR)\\%.o: $(SRCDIR)\%.c
	gcc -c $(CFLAGS) $< -o $@

clean:
	del $(OBJS)
	del $(BINDIR)\matrix.exe
