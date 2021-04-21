.PHONY: all clean

APP = main

CXX = g++
OPTS = -std=c++11 -Wall -Wextra
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(APP)

run: $(APP)
	./$(APP)

$(APP): $(OBJ)
	$(CXX) $(OPTS) $^ -o $@ 
%.o: %.cpp
	$(CXX) $(OPTS) -c $< -o $@
clean:
	rm -rf $(APP) *.o
