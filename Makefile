CC=clang++
CFLAGS=-std=c++1z -Wall -g
IDIR=-I./include/ -I/usr/local/include/
SRC=./src/main.cpp ./src/index.cpp
LDIR=-L/usr/local/lib -L/usr/lib -L/usr/lib/x86_64-linux-gnu/
LIBS=-lpthread -lboost_system

all: $(SRC) $()
	$(CC) $(IDIR) $(CFLAGS) $(SRC) $(LDIR) $(LIBS) -o blog
