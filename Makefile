CXX = g++
CXXFLAGS = -std=c++20 -Wall
SRC = src/*.cpp
OUT = impactdoc

all: build

build: clean
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)