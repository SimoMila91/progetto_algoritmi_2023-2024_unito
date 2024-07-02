CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion -pedantic


all: bin/main_ex1 bin/main_ex1_test

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/main_ex1: build/main_ex1.o build/sort_lib.o src/*.h
	mkdir -p $(@D)
	$(CC) -o bin/main_ex1 build/main_ex1.o build/sort_lib.o

bin/main_ex1_test: build/main_ex1_test.o build/sort_lib.o build/unity.o $(COMMON_DEPS)
	$(CC) -o  bin/main_ex1_test build/main_ex1_test.o build/sort_lib.o build/unity.o
	
clean: 
	rm -f build/* bin/*