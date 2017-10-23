CC=bear clang++
CFLAGS=-std=c++1z -Wall
IDIR=-I./include -I/usr/local/include/
SRC=./src/main.cpp
LDIR=-L/usr/local/lib -L/usr/lib -L/usr/lib/x86_64-linux-gnu/
LIBS=-lpistache -lpthread

all: $(SRC) $()
	$(CC) $(IDIR) $(CFLAGS) $(SRC) $(LDIR) $(LIBS) -o blog
