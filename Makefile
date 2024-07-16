SRC_DIR=./src
LIB_DIR=./h
BUILD_DIR=build
BINARY=Scratcher

CXX=g++
GDB=gdb
MKDIR=mkdir -p
RM=rm -rf

LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS=-Wall -I $(LIB_DIR) -O3

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
OBJECTS=$(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

.PHONY: all run clean
all: compile

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp #$(LIB_DIR)/%.h Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

compile:
	$(MKDIR) $(BUILD_DIR)
	$(MAKE) $(BINARY)

run: compile
	./$(BINARY)

clean:
	$(RM) $(BINARY) $(BUILD_DIR)
