CC := gcc

SRC_DIR := src
BUILD_DIR := build
DEST_DIR := dest
INCLUDE_DIR := include

TARGET := $(DEST_DIR)/program

LIBS := -L./dest/bin -lSDL3 -Wl,-rpath,'$$ORIGIN/bin' -lm

SRCS := $(shell find $(SRC_DIR) -name "*.c")
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

CFLAGS := -Wall -Wextra -O0

ifeq ($(DEBUG),1)
    CFLAGS += -DDEBUG -g -O0
else ifeq ($(RELEASE),1)
    CFLAGS := -Wall -Wextra -O2
endif


INCLUDES := $(shell find $(INCLUDE_DIR) -type d -exec printf -- "-I%s " {} \;) \
            -I./libs/SDL/include -I./libs

all: $(TARGET)

$(TARGET): $(OBJS) | $(DEST_DIR)
	$(CC) $(OBJS) $(LIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DEST_DIR):
	mkdir -p $(DEST_DIR)

clean:
	rm -rf $(BUILD_DIR)/*

fclean: clean
	rm -f $(TARGET)

.PHONY: all clean fclean
