CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -Iinclude

SRC := src/main.cpp src/funcs.cpp src/models.cpp src/views.cpp
OUT := bank

.PHONY: all build run clean

all: build

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: build
	./$(OUT)

clean:
	rm -f $(OUT) *.o
