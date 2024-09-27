TARGET = program
CC = g++
CXXFLAGS = -g -Wall -std=c++17
BUILD_DIR = build
SRC_DIR = src
INC_DIR = include

CXX_SRC = $(wildcard $(SRC_DIR)/**/*.cpp)
INCLUDES = $(wildcard -I$(INC_DIR)/**/)
OBJECTS = $(patsubst $(SRC_DIR)/**/%.cpp, $(BUILD_DIR)/%.o, $(CXX_SRC))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CXXFLAGS) $^ -o $@

# $(BUILD_DIR)/%.o: $(SRC_DIR)/**/%.cpp | $(BUILD_DIR)
$(BUILD_DIR)/%.o: $(BUILD_DIR)
	$(CC) $(CXXFLAGS) -c $< $(INCLUDES) -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

clean: 
	rm -r -f $(BUILD_DIR)

run: $(TARGET)
	./$(TARGET)