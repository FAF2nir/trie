OPTIONS = -std=c++17 -O3 -DNDEBUG -I include

all:build/main

debug: OPTIONS= -std=c++17 -O0 -g -Wall -Wextra -I include
debug: all

build/main: build/main.o build/trie.o
	g++ $(OPTIONS) build/main.o build/trie.o -o build/main

build/main.o: src/main.cpp
	g++ $(OPTIONS) src/main.cpp -c -o build/main.o

build/trie.o: src/trie.cpp
	g++ $(OPTIONS) src/trie.cpp -c -o build/trie.o

build:
	mkdir -p build

clean:
	rm build/*
