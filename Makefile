CC=g++
LFLAGS=-lSDL2
CFLAGS=-c -std=c++11 -Wall

ODIR=obj
SDIR=src
EXECUTABLE=main

CPPS = $(wildcard $(SDIR)/*.cpp) #lists all .cpp files
_OBJ = $(CPPS:.cpp=.o)
OBJ = $(_OBJ:$(SDIR)%=$(ODIR)%) #lists all object files

.PHONY: all clean

all: $(EXECUTABLE)

$(ODIR)/%.o: $(SDIR)/%.cpp
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) $< -o $@

$(EXECUTABLE): $(OBJ)
	 $(CC) $^ -o $@ -Wall $(LFLAGS)

clean:
	rm main
	rm -f $(OBJ)
	rm -df $(ODIR)
