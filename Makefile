CXX = g++
CXXFLAGS = -Wall -std=c++17 -g

SRC_DIR = src
TARGET_DIR = target
OBJ_DIR = $(TARGET_DIR)/obj

TARGET = $(TARGET_DIR)/main

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

$(TARGET): $(OBJS) | $(TARGET_DIR)
	$(CXX) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

DEP = $(OBJS:.o=.d)
-include $(DEP)

clean:
	rm -rf $(TARGET_DIR)
