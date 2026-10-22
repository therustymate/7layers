
CC := x86_64-w64-mingw32-gcc
WINDRES := x86_64-w64-mingw32-windres
STRIP := x86_64-w64-mingw32-strip

NAME := 7layers
VERSION := 3.0.0

SRC_DIR := src
INC_DIR := include
RSRC_DIR := rsrc
BUILD_DIR := build
BIN_DIR := bin

TARGET := $(BIN_DIR)/$(NAME)_$(VERSION)_x64.exe

SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

RCS := $(shell find $(RSRC_DIR) -type f -name '*.rc' 2>/dev/null)
RC_OBJS := $(patsubst $(RSRC_DIR)/%.rc,$(BUILD_DIR)/rsrc/%.o,$(RCS))

ICON_FILES := $(shell find $(RSRC_DIR) -type f -name '*.ico' 2>/dev/null)

INC_DIRS := $(shell find $(INC_DIR) -type d)
INCLUDES := $(addprefix -I,$(INC_DIRS))

CFLAGS := \
	-Wall \
	-Wextra \
	-O2 \
	$(INCLUDES)

RCFLAGS := \
	$(INCLUDES) \
	-I$(RSRC_DIR)

LDFLAGS := \
	-Wl,--disable-runtime-pseudo-reloc \
	-Wl,-Map=$(BUILD_DIR)/$(NAME).map

LDLIBS :=

.PHONY: all strip clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS) $(RC_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@
	@echo "Build Success: $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/rsrc/%.o: $(RSRC_DIR)/%.rc $(ICON_FILES)
	@mkdir -p $(dir $@)
	$(WINDRES) $(RCFLAGS) -O coff -i $< -o $@

strip: $(TARGET)
	$(STRIP) --strip-all $(TARGET)
	@echo "Strip Success: $(TARGET)"

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)

rebuild: clean all
