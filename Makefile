# Compiler and flags
CXX := g++
CXXFLAGS := -g -std=c++17 -Wall -I include/controller -I include/model -I include/view

# Directories
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)   \
		$(wildcard $(SRC_DIR)/*/*.cpp)

# Object files stored in build directory mirroring src structure
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Executable
TARGET := media_player_app

# Default target
all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/controller $(BUILD_DIR)/model $(BUILD_DIR)/view
# Create the build directory and necessary subdirectories


# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

# Compile .cpp files to .o files, placing them in the build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	mkdir -p $(dir $@)  # Ensure subdirectories are created
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Phony targets
.PHONY: all clean
