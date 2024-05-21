TARGET_EXEC := my_mouse
BUILD_DIR := ./build
SRC_DIRS := ./src
INCLUDE_DIR := -I ./include
TEST_DIR := ./tests

# Determine the platform
UNAME_S := $(shell uname -s)

# CC
ifeq ($(UNAME_S), Darwin)
	CC := clang
else
	CC := gcc
endif

CFLAGS += $(INCLUDE_DIR)
LDFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

# Find all C files to compile
SRCS := $(wildcard $(SRC_DIRS)/*.c)

# Prepends BUILD_DIR and appends .o to every src file
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# The final build step
$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source 
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

fclean: clean
	$(RM) my_mouse