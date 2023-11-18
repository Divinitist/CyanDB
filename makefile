INC_DIR = ./inc
BIN_DIR = ./bin
SRC_DIR = ./src/cli
OBJ_DIR = ./obj

TARGET = cyandb
BIN_TARGET = $(BIN_DIR)/$(TARGET)
SOURCE = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(INC_DIR)/*.hpp)
OBJECTS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SOURCE)))
# notdir is used for cutting off the path and only leaving the filename

COMPILER = g++
VERSION = -std=c++23
TOOL = -fsanitize=address -g
WARNING = -Wall -Wextra -Werror -Wpedantic

$(BIN_TARGET) : $(OBJECTS)
	$(COMPILER) $(VERSION) $(OBJECTS) -o $(BIN_TARGET) \
				$(TOOL) $(WARNING) -I$(INC_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp $(HEADERS)
# if not adding headers into dependences, the alternation of headers would not be monitored
	$(COMPILER) $(VERSION) -c $< -o $@ \
				$(TOOL) $(WARNING) -I$(INC_DIR)

clean :
	find $(OBJ_DIR) -name *.o -exec rm -rf {} \;
	rm $(BIN_TARGET)

