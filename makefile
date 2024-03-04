#the compiler
CC = g++
 
#flags:
CFLAGS  = -g -Wall -Wextra -fsanitize=address -std=c++20
 
#sources of input
SOURCES = main.cpp

#sources of output
EXECUTABLE = solution

all:
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE) -lm