CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++17

# Source, object, and include directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

# Automatically detect all source files
SRCS = $(shell find $(SRC_DIR) -name "*.cpp") main.cpp
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

# Target executable
TARGET = fastfantasy

all: directories $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ -lcpr -lfmt

# Rule to build object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/domain/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/utils/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: directories
directories: $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@/domain $@/utils

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

# For debugging the makefile
print-%  : ; @echo $* = $($*)
