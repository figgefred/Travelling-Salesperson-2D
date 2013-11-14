
CC = g++
FLAGS = -Wall -g

EXE = tsp
EXE_ARGS = input/test_1.in
SRC = src/
BIN = bin/

all: $(EXE)

clean: 
	rm -rf $(BIN)/*

$(EXE): $(SRC)/tsp.cpp
	$(CC) $(FLAGS) $(SRC)/tsp.cpp -o $(BIN)/$(EXE)

run_$(EXE):
	$(BIN)/$(EXE) $(EXE_ARGS)