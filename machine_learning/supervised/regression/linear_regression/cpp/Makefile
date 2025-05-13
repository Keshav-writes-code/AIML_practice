CC = g++
CFLAGS = -Wall -std=c++11
TARGET = linear_regression
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
SRC_DIR = .
IMP_DIR = implementations
HEADERS_DIR = headers

# Automatically find all .cpp files in the source directory and implementations directory
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(IMP_DIR)/*.cpp)
# Generate object file names from source files
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(patsubst $(IMP_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES)))

# Create needed directories
$(shell mkdir -p $(BUILD_DIR) $(OBJ_DIR))

# Default target
all: $(BUILD_DIR)/$(TARGET)

# Link all object files to create the executable
$(BUILD_DIR)/$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^
	./${BUILD_DIR}/$(TARGET)

# Compile source files in the main directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -c $< -o $@

# Compile source files in the implementations directory
$(OBJ_DIR)/%.o: $(IMP_DIR)/%.cpp
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
