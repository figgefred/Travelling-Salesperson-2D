#!/bin/bash
# Makefile make me fast and accurate

CC = g++
FLAGS = -g -static -O2 -std=gnu++0x  -Wall -Wextra -Wformat=2

EXE = tsp
EXE_ARGS = input/test_1.in

SRC_DIR = src/
INCL = $(SRC_DIR)
SRC_FILES = tsp.cpp map.cpp tabusearch.cpp christofides.cpp 2opt.cpp types.cpp naivegreedy.cpp neighbourhood.cpp
SOURCES = $(SRC_FILES:%.cpp=$(SRC_DIR)%.cpp)
CCFLAGS = -I. -I$(INCL)

BIN = bin/
OBJ = $(SOURCES:$(SRC_DIR)%.cpp=obj/%.o)



all: $(EXE)

cleanall: clean
	rm -rf $(BIN)

clean: 
	rm -rf $(BIN)*
	rm -f $(OBJ)

$(EXE): $(OBJ) | $(BIN)
	$(CC) $(OBJ) $(CCFLAGS) $(FLAGS) -o $(BIN)$(EXE)

$(OBJ): $(SOURCES) | $(BIN)
	$(CC) -c $(SOURCES) $(CCFLAGS) $(FLAGS)
	mv *.o obj/

$(BIN): 
	mkdir -p $(BIN)

run_$(EXE):
	$(BIN)$(EXE) $(EXE_ARGS)
