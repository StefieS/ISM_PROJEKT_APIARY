CXX = g++
CXXFLAGS = -std=c++20 -O2 -pedantic -Wall -Wextra -Iinc
LDFLAGS = -lsimlib -lm

SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Find all .cpp files recursively
SRCS = $(shell find $(SRC_DIR) -name "*.cpp")

# Exclude main.cpp from object list
MAIN = $(SRC_DIR)/main.cpp
SRCS_NO_MAIN = $(filter-out $(MAIN), $(SRCS))

# Turn e.g. src/a/b/c.cpp → build/obj/a/b/c.o
OBJS = $(SRCS_NO_MAIN:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

TARGET = simulation

.PHONY: all clean purge zip

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN)
	$(CXX) $(CXXFLAGS) $(OBJS) $(MAIN) -o $@ $(LDFLAGS)

# Compile object files, create subdirs automatically
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

purge: clean
	rm -f $(TARGET)

zip:
	zip -r 02_xlesigm00_xnovakf00.zip src inc figs Makefile LICENSE README.md
