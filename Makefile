SOURCE_DIR := ./source
BUILD_DIR := ./build

DESTDIR := /
PREFIX := /usr/local
BIN_DIR := $(DESTDIR)/$(PREFIX)/bin

PKG_EXEC := pkg
PKG_FILENAMES := debug.c globals.c fileio.c log.c conargs.c config.c pkg.c
PKG_SOURCE_FILES := $(foreach filename,$(PKG_FILENAMES),$(SOURCE_DIR)/$(filename))
PKG_OBJECT_FILES := $(foreach filename,$(PKG_FILENAMES),$(BUILD_DIR)/$(filename).o)

LD := clang
CC := clang

TOML_L_FLAGS := -L/usr/local/lib -ltoml
TOML_C_FLAGS :=

L_FLAGS :=$(TOML_L_FLAGS)

DEBUG_C_FLAGS := -O0 -g
RELEASE_C_FLAGS := -O3
C_FLAGS :=$(TOML_C_FLAGS) 
C_FLAGS += -std=c99 -pedantic -Wpedantic
C_FLAGS += -Wall 
#C_FLAGS += -Werror
C_FLAGS += -Wunused
C_FLAGS += -Wunused-result
C_FLAGS += -Wno-macro-redefined
C_FLAGS += -Wno-format-pedantic
#C_FLAGS += -Wno-unused-function
C_FLAGS += -Wno-unused-label
#C_FLAGS += -Wno-unused-variable
#C_FLAGS += $(RELEASE_C_FLAGS)
C_FLAGS += $(DEBUG_C_FLAGS)


.PHONY: build
build: $(BUILD_DIR)/$(PKG_EXEC)

$(BUILD_DIR)/$(PKG_EXEC): $(PKG_OBJECT_FILES)
	@echo "LD $(basename $@)"
	@mkdir -p $(dir $@)
	@$(LD) -o $@ $(L_FLAGS) $(PKG_OBJECT_FILES)

$(BUILD_DIR)/%.c.o: $(SOURCE_DIR)/%.c
	@echo "CC $(basename $@)"
	@mkdir -p $(dir $@)
	@$(CC) -c -o $@ $(C_FLAGS) $<
	
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: test
test:
	$(BUILD_DIR)/$(PKG_EXEC) "param1" "param2" "param3"





