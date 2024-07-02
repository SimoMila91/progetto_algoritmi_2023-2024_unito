CC = gcc
CFLAGS = -g -Wall -Wextra -Wpedantic -Wconversion -pedantic

all: bin/main_ex2 bin/main_ex2_test

COMMON_DEPS = $(INCLUDES) Makefile

build/%.o: src/%.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/main_ex2: build/main_ex2.o build/library.o src/*.h
	mkdir -p $(@D)
	$(CC) -o bin/main_ex2 build/main_ex2.o build/library.o 

bin/main_ex2_test: build/main_ex2_test.o build/library.o build/unity.o $(COMMON_DEPS)
	$(CC) -o bin/main_ex2_test build/main_ex2_test.o build/library.o build/unity.o

clean: 
	rm -f build/* bin/*