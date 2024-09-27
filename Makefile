# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build

# Compiler and flags
CXX := g++
# CXXFLAGS := -g -std=c++17 -Wall -I include/controller -I include/model -I include/view
CXXFLAGS := -g -std=c++17 -Wall $(addprefix -I , $(INCLUDE_DIR) $(wildcard $(INCLUDE_DIR)/*))

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)   \
        $(wildcard $(SRC_DIR)/*/*.cpp)

# Object files stored in build directory, maintaining source structure
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable
TARGET := media_player_cli_app

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile .cpp files to .o files, creating necessary subdirectories
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)  # Ensure the directory for the object file is created
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the target executable
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
