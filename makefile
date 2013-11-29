#!/bin/bash
# Makefile make me fast and accurate

CC = g++
FLAGS = -Wall -g -std=c++11

EXE = tsp
EXE_ARGS = input/test_1.in

SRC_DIR = src/
INCL = $(SRC_DIR)
SRC_FILES = tsp.cpp map.cpp tabusearch.cpp christofides.cpp
SOURCES = $(SRC_FILES:%.cpp=$(SRC_DIR)%.cpp)
CCFLAGS = -I. -I$(INCL)

BIN = bin/
OBJ = $(SOURCES:$(SRC_DIR)%.cpp=%.o)



all: $(EXE)

cleanall: clean
	rm -rf $(BIN)

clean: 
	rm -rf $(BIN)*

$(EXE): $(OBJ) | $(BIN)
	$(CC) $(OBJ) $(CCFLAGS) $(FLAGS) -o $(BIN)$(EXE)

$(OBJ): $(SOURCES) | $(BIN)
	$(CC) -c $(SOURCES) $(CCFLAGS) $(FLAGS)

$(BIN): 
	mkdir -p $(BIN)

run_$(EXE):
	$(BIN)$(EXE) $(EXE_ARGS)