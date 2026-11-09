
CXX := x86_64-w64-mingw32-g++
WINDRES := x86_64-w64-mingw32-windres
STRIP := x86_64-w64-mingw32-strip

NAME := 7layers
VERSION := 4.0.0

SRC_DIR := src
INC_DIR := include
RSRC_DIR := rsrc
BUILD_DIR := build
BIN_DIR := bin

TARGET := $(BIN_DIR)/$(NAME)_$(VERSION)_x64.exe

# -------------------------------------------
# Source Files
# -------------------------------------------

SRCS := $(shell find $(SRC_DIR) -type f -name '*.cpp')
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# -------------------------------------------
# Resources
# -------------------------------------------

RCS := $(shell find $(RSRC_DIR) -type f -name '*.rc' 2>/dev/null)
RC_OBJS := $(patsubst $(RSRC_DIR)/%.rc,$(BUILD_DIR)/rsrc/%.o,$(RCS))

ICON_FILES := $(shell find $(RSRC_DIR) -type f -name '*.ico' 2>/dev/null)

# -------------------------------------------
# Includes
# -------------------------------------------

INC_DIRS := $(shell find $(INC_DIR) -type d)
INCLUDES := $(addprefix -I,$(INC_DIRS))

# -------------------------------------------
# Compiler Flags
# -------------------------------------------

CXXFLAGS := \
	-std=c++17 \
	-Wall \
	-Wextra \
	-O2 \
	-MMD \
	-MP \
	$(INCLUDES)

RCFLAGS := \
	$(INCLUDES) \
	-I$(RSRC_DIR)

LDFLAGS := \
	-static \
	-Wl,-Map=$(BUILD_DIR)/$(NAME).map

LDLIBS := -lversion -ladvapi32


# -------------------------------------------
# Build Metadata
# -------------------------------------------

BUILD_ID := $(shell python3 -c "import uuid; print(uuid.uuid4())")
BUILD_COMMIT := $(shell git rev-parse --short=12 HEAD 2>/dev/null || echo unknown)
BUILD_DATE := $(shell date -u +"%Y-%m-%dT%H:%M:%SZ")

BUILD_PROFILE ?= UNVERIFIED
AUTHORIZATION_ID ?= NONE
SIGNING_KEY_FINGERPRINT ?= UNSIGNED

CXXFLAGS += \
    -DBUILD_ID=\"$(BUILD_ID)\" \
    -DBUILD_GIT_COMMIT=\"$(BUILD_COMMIT)\" \
    -DBUILD_DATE=\"$(BUILD_DATE)\" \
    -DBUILD_PROFILE=\"$(BUILD_PROFILE)\" \
    -DBUILD_AUTHORIZATION_ID=\"$(AUTHORIZATION_ID)\" \
    -DBUILD_SIGNING_KEY_FINGERPRINT=\"$(SIGNING_KEY_FINGERPRINT)\"


# -------------------------------------------
# Build
# -------------------------------------------

.PHONY: all strip clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS) $(RC_OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $@
	@echo "Build Success: $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/rsrc/%.o: $(RSRC_DIR)/%.rc $(ICON_FILES)
	@mkdir -p $(dir $@)
	$(WINDRES) $(RCFLAGS) -O coff -i $< -o $@

# -------------------------------------------
# Utilities
# -------------------------------------------

strip: $(TARGET)
	$(STRIP) --strip-all $(TARGET)
	@echo "Strip Success: $(TARGET)"

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(TARGET)

rebuild: clean all

-include $(DEPS)
