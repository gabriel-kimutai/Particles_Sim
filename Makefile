CC=g++
CFLAGS = -std=c++17 -O2
LDFLAGS = -lraylib

App: ./src/*.cpp
	$(CC) $(CFLAGS) -o  ./build/App  -g ./src/*.c* $(LDFLAGS)

.PHONY: test clean

test: App
	./build/App
clean:
	rm -f ./build/App
