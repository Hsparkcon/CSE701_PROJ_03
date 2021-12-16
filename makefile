INC_DIR = include/
SRC_DIR = src/
OBJ_DIR = obj/

CC = g++
CFLAGS = -Wall -Wextra -Wconversion -Wpedantic -Wno-unused-result -Wno-unused-parameter -std=c++20 -O2

main:
	$(CC) main.cpp $(CFLAGS) -o proj_r.out