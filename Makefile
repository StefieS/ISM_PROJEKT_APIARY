CXX = g++
CXXFLAGS = -std=c++20 -O2 -pedantic -Wall -Wextra
LDFLAGS = -lsimlib -lm

SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SRCS := $(filter-out $(SRC_DIR)/main.cpp, $(SRCS))

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN = $(SRC_DIR)/main.cpp
TARGET = simulation

.PHONY: all clean purge zip

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN)
	$(CXX) $(CXXFLAGS) $(OBJS) $(MAIN) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(BUILD_DIR)

purge: clean
	rm -f $(TARGET)

zip:
	zip -r xlesigm00.zip src inc Makefile LICENSE README.md