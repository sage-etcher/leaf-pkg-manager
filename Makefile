SOURCE_DIR := ./source
BUILD_DIR := ./build

DESTDIR := /
PREFIX := /usr/local
BIN_DIR := $(DESTDIR)/$(PREFIX)/bin

PKG_EXEC := pkg
PKG_FILENAMES := pkg_globals.c pkg_fileio.c pkg_config.c pkg.c
PKG_SOURCE_FILES := $(foreach filename,$(PKG_FILENAMES),$(SOURCE_DIR)/$(filename))
PKG_OBJECT_FILES := $(foreach filename,$(PKG_FILENAMES),$(BUILD_DIR)/$(filename).o)

LD := clang
CC := clang

TOML_L_FLAGS := -L/usr/local/lib -ltoml
TOML_C_FLAGS :=

L_FLAGS :=$(TOML_L_FLAGS)
C_FLAGS :=$(TOML_C_FLAGS) -std=c99 -pedantic -Wall -Werror

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
