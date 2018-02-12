LUA5_1=-llua5.1 -D_LUA_5_1_
LUA5_2=-llua5.2 -D_LUA_5_2_
LUA5_3=-llua5.3 -D_LUA_5_3_

LUA_VERSION=$(LUA5_3)

INC=-I ../include
CPP=g++
CFLAGS=-g -Wall -W -std=c++11
LIBDIR=-L ../build

all: test

test: test.c
	$(CPP) $(CFLAGS) $@.c -o $@ $(LUA_VERSION) $(INC) ../build/systems.o -lpthread
