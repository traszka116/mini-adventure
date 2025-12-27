CC := gcc

SRC_DIR := src
BUILD_DIR := build
DEST_DIR := dest
INCLUDE_DIR := include

TARGET := $(DEST_DIR)/program

LIBS := -L./dest/bin -lSDL3 -Wl,-rpath,'$$ORIGIN/bin' -lm

SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

CFLAGS := -Wall -Wextra
INCLUDES := $(shell find $(INCLUDE_DIR) -type d -exec printf -- "-I%s " {} \;) \
            -I./libs/SDL/include -I./libs

.PHONY: all debug release clean run help

# Default build (equivalent to DEBUG=0)
all: release

# Release build (optimized)
release: CFLAGS += -O2
release: $(TARGET)
	@echo "Build complete: $(TARGET)"

# Debug build (with debug symbols)
debug: CFLAGS += -DDEBUG -g -O0
debug: $(TARGET)
	@echo "Debug build complete: $(TARGET)"

# Build target
$(TARGET): $(OBJS) | $(DEST_DIR)
	$(CC) $(OBJS) $(LIBS) -o $@

# Compile objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create directories
$(DEST_DIR):
	mkdir -p $(DEST_DIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean build files
clean:
	rm -rf $(BUILD_DIR)/*

# Full clean
fclean: clean
	rm -f $(TARGET)

# Rebuild
re: fclean all

# Help
help:
	@echo "Usage:"
	@echo "  make           Build release version"
	@echo "  make release   Build release version"
	@echo "  make debug     Build debug version"
	@echo "  make run       Build and run release version"
	@echo "  make clean     Remove object files"
	@echo "  make fclean    Remove object files and executable"
	@echo "  make re        Rebuild everything"