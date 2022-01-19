CC=g++ -std=c++17

OPTIMIZATION=-O0

INCLUDE_DIR=./include
SRC_DIR=./src
SRC_SHARED_DIR=./src/shared
OBJ_DIR=./obj
BIN_DIR=./bin

OBJ_FILES=$(OBJ_DIR)/trie.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/stringutils.o 

MAIN_BIN=main

INCLUDE_DIR_FLAGS=-I$(INCLUDE_DIR)
LINKER_FLAGS=-pthread -lboost_date_time

CFLAGS=-Wno-return-type -g $(OPTIMIZATION) $(LINKER_FLAGS) $(INCLUDE_DIR_FLAGS)

.PRECIOUS: $(OBJ_DIR)/%.o

all: $(MAIN_BIN)

objs: $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_SHARED_DIR)/%.cpp 
	$(CC) -o $@ $(CFLAGS) -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(CC) -o $@ $(CFLAGS) -c $<

%: $(SRC_DIR)/%.cpp $(OBJ_DIR)/%.o objs 
	$(CC) -o $(BIN_DIR)/$@ $(CFLAGS) $(OBJ_DIR)/$@.o $(OBJ_FILES)


test: test
preprocessor: preprocessor

run: $(MAIN_BIN)
	$(BIN_DIR)/$(MAIN_BIN)

clean: 
	rm $(BIN_DIR)/* $(OBJ_DIR)/*.o 
