CC=g++
LFLAGS=-lSDL2 -lSDL2_image -pthread
CFLAGS=-g -c -std=c++11 -Wall

MAKEDIR=mkdir -p $(ODIR)
ODIR=obj
SDIR=src
EXECUTABLE=main

# Modify some variables if on windows
ifeq ($(OS), Windows_NT)
	ODIR=obj-win
	EXECUTABLE=main.exe
	MAKEDIR=mkdir $(ODIR) 2> nul
	LFLAGS += -L.github/lib -static-libgcc -static-libstdc++
	CFLAGS += -I.github/include
endif

CPPS = $(wildcard $(SDIR)/*.cpp) #lists all .cpp files
_OBJ = $(CPPS:.cpp=.o)
OBJ = $(_OBJ:$(SDIR)%=$(ODIR)%) #lists all object files

.PHONY: all clean

all: $(EXECUTABLE)

$(ODIR)/%.o: $(SDIR)/%.cpp
	-$(MAKEDIR)
	$(CC) $(CFLAGS) $< -o $@

$(EXECUTABLE): $(OBJ)
	 $(CC) $^ -o $@ -Wall $(LFLAGS)

clean:
	rm -f $(OBJ)
	rm -df $(ODIR)
	rm main
