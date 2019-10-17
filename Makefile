OBJ=snake.o \
    terminal.o \
	food.o \
	drawable.o \
	snake_main.o

CXXFLAGS=-std=c++11 -I include
LDLIBS=-lncurses -lstdc++

snake: $(OBJ)
all: snake
clean:
	$(RM) *.o snake