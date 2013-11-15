#!/bin/bash

# Makefile make me fast and accurate

CC = g++
FLAGS = -Wall -g

EXE = tsp
EXE_ARGS = input/test_1.in

SRC_DIR = src
INCL = $(SRC_DIR)
SRC_FILES = tsp.cpp map.cpp
SOURCES = $(SRC_FILES:%.cpp=$(SRC_DIR)/%.cpp)
CCFLAGS = -I. -I$(INCL)

BIN = bin
OBJ = $(SRC_FILES:%.cpp=%.o)

all: $(EXE)

cleanall: clean
	rm -rf bin/

clean: 
	rm -rf $(BIN)/
	rm $(OBJ)

$(EXE): $(OBJ) | $(BIN)
	$(CC) $(OBJ) $(FLAGS) -o $(BIN)/$(EXE)

$(OBJ): $(SOURCES) | $(BIN)
	$(CC) -c $(SOURCES) $(CCFLAGS) $(FLAGS)

$(BIN): 
	mkdir -p $(BIN)

run_$(EXE):
	$(BIN)/$(EXE) $(EXE_ARGS)
