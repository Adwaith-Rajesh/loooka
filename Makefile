BUILD_DIR=./build
BINARY=$(BUILD_DIR)/loooka
SRCDIR=./src
INCDIR=./src

SRC_FILES=$(shell find $(SRCDIR) -type f -name "*.c")
OBJ_FILES=$(patsubst %.c,%.o,$(SRC_FILES))
DEP_FILES=$(patsubst %.c,%.d,$(SRC_FILES))

CC=gcc
OPT=-O3
CFLAGS=-Wall -Wextra -g $(OPT) $(foreach D,$(INCDIR),-I$(D)) -MP -MD


.PHONY: all make_build_dir clean run

all: make_build_dir $(BINARY)

make_build_dir:
	@mkdir -p $(BUILD_DIR)

$(BINARY): $(OBJ_FILES)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	@rm -rf $(BUILD_DIR) $(OBJ_FILES) $(DEP_FILES)

run:
	./$(BINARY)


-include $(DEP_FILES)
