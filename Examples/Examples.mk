CXX = g++
CC = gcc
WINCXX = x86_64-w64-mingw32-g++
WINCC = x86_64-w64-mingw32-gcc
WINE = wine

SHELL := /bin/bash

EXAMPLES_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
ROOT_DIR := $(abspath $(EXAMPLES_DIR)/..)
ENGINE_DIR := $(ROOT_DIR)/BlockEngine
BUILD_DIR := $(EXAMPLES_DIR)/.build

CPPFLAGS = -I"$(ENGINE_DIR)/src" \
           -I"$(ENGINE_DIR)/external/glad/include" \
           -I"$(ENGINE_DIR)/external/glfw-3.5.1/include"

CXXFLAGS = -O2
CFLAGS = -O2
WIN_CXXFLAGS = -O2
WIN_CFLAGS = -O2
WIN_DEBUG_CXXFLAGS = -O0 -g
WIN_DEBUG_CFLAGS = -O0 -g

LDFLAGS =
LDLIBS =
LINUX_LIBS = -lGL -lglfw -ldl -lm -lcrypto

GLFW_WIN_DIR = $(ENGINE_DIR)/external/glfw-3.5.1/build-win/src
GLFW_WIN_LIB = $(GLFW_WIN_DIR)/libglfw3.a
WIN_LDFLAGS = -L"$(GLFW_WIN_DIR)"
WIN_LIBS = -lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32 -lwinmm \
           -static-libgcc -static-libstdc++

# Compile the engine, excluding BlockEngine.cpp.
SRC = $(shell if [ -d "$(ENGINE_DIR)/src" ]; then find "$(ENGINE_DIR)/src" -type f -name '*.cpp' ! -name 'BlockEngine.cpp' -print; fi)

LINUX_OBJ_DIR = $(BUILD_DIR)/linux/engine
LINUX_OBJ = $(patsubst $(ENGINE_DIR)/src/%.cpp,$(LINUX_OBJ_DIR)/%.o,$(SRC))
LINUX_GLAD_OBJ = $(BUILD_DIR)/linux/glad.o

WIN_OBJ_DIR = $(BUILD_DIR)/windows/engine
WIN_OBJ = $(patsubst $(ENGINE_DIR)/src/%.cpp,$(WIN_OBJ_DIR)/%.o,$(SRC))
WIN_GLAD_OBJ = $(BUILD_DIR)/windows/glad.o

WIN_DEBUG_OBJ_DIR = $(BUILD_DIR)/windows-debug/engine
WIN_DEBUG_OBJ = $(patsubst $(ENGINE_DIR)/src/%.cpp,$(WIN_DEBUG_OBJ_DIR)/%.o,$(SRC))
WIN_DEBUG_GLAD_OBJ = $(BUILD_DIR)/windows-debug/glad.o

.DEFAULT_GOAL := all

.PHONY: all linux run run-multi windows run-windows windows-debug run-windows-debug clean

# Linux engine objects.
$(LINUX_OBJ_DIR)/%.o: $(ENGINE_DIR)/src/%.cpp
	@mkdir -p "$(@D)"
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c "$<" -o "$@"

$(LINUX_GLAD_OBJ): $(ENGINE_DIR)/external/glad/src/glad.c
	@mkdir -p "$(@D)"
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c "$<" -o "$@"

# Windows release engine objects.
$(WIN_OBJ_DIR)/%.o: $(ENGINE_DIR)/src/%.cpp
	@mkdir -p "$(@D)"
	$(WINCXX) $(CPPFLAGS) $(WIN_CXXFLAGS) -MMD -MP -c "$<" -o "$@"

$(WIN_GLAD_OBJ): $(ENGINE_DIR)/external/glad/src/glad.c
	@mkdir -p "$(@D)"
	$(WINCC) $(CPPFLAGS) $(WIN_CFLAGS) -MMD -MP -c "$<" -o "$@"

# Windows debug engine objects.
$(WIN_DEBUG_OBJ_DIR)/%.o: $(ENGINE_DIR)/src/%.cpp
	@mkdir -p "$(@D)"
	$(WINCXX) $(CPPFLAGS) $(WIN_DEBUG_CXXFLAGS) -MMD -MP -c "$<" -o "$@"

$(WIN_DEBUG_GLAD_OBJ): $(ENGINE_DIR)/external/glad/src/glad.c
	@mkdir -p "$(@D)"
	$(WINCC) $(CPPFLAGS) $(WIN_DEBUG_CFLAGS) -MMD -MP -c "$<" -o "$@"

# Header dependencies.
-include $(LINUX_OBJ:.o=.d) $(LINUX_GLAD_OBJ:.o=.d)
-include $(WIN_OBJ:.o=.d) $(WIN_GLAD_OBJ:.o=.d)
-include $(WIN_DEBUG_OBJ:.o=.d) $(WIN_DEBUG_GLAD_OBJ:.o=.d)


# Build all Linux examples.
all: $(LINUX_OBJ) $(LINUX_GLAD_OBJ)
	@set -e; \
	shopt -s nullglob; \
	dirs=("$(EXAMPLES_DIR)"/*/); \
	if (( $${#dirs[@]} == 0 )); then \
	    echo "No example folders found in $(EXAMPLES_DIR)." >&2; exit 1; \
	fi; \
	built=0; \
	for dir in "$${dirs[@]}"; do \
	    folder="$${dir%/}"; \
	    base="$${folder##*/}"; \
	    name="$$(printf '%s' "$$base" | tr -d '[:space:]')"; \
	    source="$$dir$$name.cpp"; \
	    if [ ! -f "$$source" ]; then \
	        mapfile -d '' candidates < <(find "$$dir" -maxdepth 1 -type f -name '*.cpp' -print0 | sort -z); \
	        if (( $${#candidates[@]} == 1 )); then source="$${candidates[0]}"; \
	        elif (( $${#candidates[@]} == 0 )); then echo "Skipping $$base: no .cpp file." >&2; continue; \
	        else echo "Cannot choose a source in $$base. Add $$name.cpp or leave one .cpp file." >&2; exit 1; fi; \
	    fi; \
	    output="$$dir$$name"; \
	    echo "==> Building Linux: $$base"; \
	    $(CXX) $(CPPFLAGS) $(CXXFLAGS) "$$source" $(LINUX_OBJ) $(LINUX_GLAD_OBJ) $(LDFLAGS) $(LDLIBS) $(LINUX_LIBS) -o "$$output"; \
	    built=$$((built + 1)); \
	done; \
	if (( built == 0 )); then echo "No buildable examples found." >&2; exit 1; fi

linux: all


# Build all Windows release examples.
windows: $(WIN_OBJ) $(WIN_GLAD_OBJ) $(GLFW_WIN_LIB)
	@set -e; \
	shopt -s nullglob; \
	dirs=("$(EXAMPLES_DIR)"/*/); \
	if (( $${#dirs[@]} == 0 )); then echo "No example folders found." >&2; exit 1; fi; \
	built=0; \
	for dir in "$${dirs[@]}"; do \
	    folder="$${dir%/}"; base="$${folder##*/}"; \
	    name="$$(printf '%s' "$$base" | tr -d '[:space:]')"; \
	    source="$$dir$$name.cpp"; \
	    if [ ! -f "$$source" ]; then \
	        mapfile -d '' candidates < <(find "$$dir" -maxdepth 1 -type f -name '*.cpp' -print0 | sort -z); \
	        if (( $${#candidates[@]} == 1 )); then source="$${candidates[0]}"; \
	        elif (( $${#candidates[@]} == 0 )); then echo "Skipping $$base: no .cpp file." >&2; continue; \
	        else echo "Cannot choose a source in $$base. Add $$name.cpp or leave one .cpp file." >&2; exit 1; fi; \
	    fi; \
	    output="$$dir$$name.exe"; \
	    echo "==> Building Windows release: $$base"; \
	    $(WINCXX) $(CPPFLAGS) $(WIN_CXXFLAGS) "$$source" $(WIN_OBJ) $(WIN_GLAD_OBJ) $(WIN_LDFLAGS) $(WIN_LIBS) -o "$$output"; \
	    built=$$((built + 1)); \
	done; \
	if (( built == 0 )); then echo "No buildable examples found." >&2; exit 1; fi


# Build all Windows debug examples.
windows-debug: $(WIN_DEBUG_OBJ) $(WIN_DEBUG_GLAD_OBJ) $(GLFW_WIN_LIB)
	@set -e; \
	shopt -s nullglob; \
	dirs=("$(EXAMPLES_DIR)"/*/); \
	if (( $${#dirs[@]} == 0 )); then echo "No example folders found." >&2; exit 1; fi; \
	built=0; \
	for dir in "$${dirs[@]}"; do \
	    folder="$${dir%/}"; base="$${folder##*/}"; \
	    name="$$(printf '%s' "$$base" | tr -d '[:space:]')"; \
	    source="$$dir$$name.cpp"; \
	    if [ ! -f "$$source" ]; then \
	        mapfile -d '' candidates < <(find "$$dir" -maxdepth 1 -type f -name '*.cpp' -print0 | sort -z); \
	        if (( $${#candidates[@]} == 1 )); then source="$${candidates[0]}"; \
	        elif (( $${#candidates[@]} == 0 )); then echo "Skipping $$base: no .cpp file." >&2; continue; \
	        else echo "Cannot choose a source in $$base. Add $$name.cpp or leave one .cpp file." >&2; exit 1; fi; \
	    fi; \
	    output="$$dir$${name}DEBUG.exe"; \
	    echo "==> Building Windows debug: $$base"; \
	    $(WINCXX) $(CPPFLAGS) $(WIN_DEBUG_CXXFLAGS) "$$source" $(WIN_DEBUG_OBJ) $(WIN_DEBUG_GLAD_OBJ) $(WIN_LDFLAGS) $(WIN_LIBS) -o "$$output"; \
	    built=$$((built + 1)); \
	done; \
	if (( built == 0 )); then echo "No buildable examples found." >&2; exit 1; fi


# Run Basic Window by default.
# Set EXAMPLE="Folder Name" to choose another example.
run: all
	@set -e; \
	if [ -n "$(EXAMPLE)" ]; then dir="$(EXAMPLES_DIR)/$(EXAMPLE)/"; \
	else \
	    dir="$(EXAMPLES_DIR)/Basic Window/"; \
	    if [ ! -d "$$dir" ]; then \
	        for candidate in "$(EXAMPLES_DIR)"/*Basic*Window*/; do \
	            if [ -d "$$candidate" ]; then dir="$$candidate"; break; fi; \
	        done; \
	    fi; \
	fi; \
	if [ ! -d "$$dir" ]; then echo "Basic Window example folder not found." >&2; exit 1; fi; \
	base="$${dir%/}"; base="$${base##*/}"; \
	name="$$(printf '%s' "$$base" | tr -d '[:space:]')"; \
	binary="$$dir$$name"; \
	if [ ! -x "$$binary" ]; then echo "Executable not found: $$binary" >&2; exit 1; fi; \
	echo "==> Running $$binary"; \
	"$$binary"


# Run Multi-Window by default.
run-multi: all
	@set -e; \
	if [ -n "$(EXAMPLE)" ]; then dir="$(EXAMPLES_DIR)/$(EXAMPLE)/"; \
	else \
	    dir=''; \
	    for candidate in "$(EXAMPLES_DIR)"/*Multi*/; do \
	        if [ -d "$$candidate" ]; then dir="$$candidate"; break; fi; \
	    done; \
	fi; \
	if [ -z "$$dir" ] || [ ! -d "$$dir" ]; then echo 'Multi example folder not found.' >&2; exit 1; fi; \
	base="$${dir%/}"; base="$${base##*/}"; \
	name="$$(printf '%s' "$$base" | tr -d '[:space:]')"; \
	binary="$$dir$$name"; \
	if [ ! -x "$$binary" ]; then echo "Executable not found: $$binary" >&2; exit 1; fi; \
	echo "==> Running $$binary"; \
	"$$binary"


# Build Windows release examples, then run the selected example through Wine.
run-windows: windows
	@set -e; \
	if [ -n "$(EXAMPLE)" ]; then dir="$(EXAMPLES_DIR)/$(EXAMPLE)/"; else dir="$(EXAMPLES_DIR)/Basic Window/"; fi; \
	if [ ! -d "$$dir" ]; then echo "Windows example folder not found: $$dir" >&2; exit 1; fi; \
	base="$${dir%/}"; base="$${base##*/}"; \
	name="$$(printf '%s' "$$base" | tr -d '[:space:]')"; \
	binary="$$dir$$name.exe"; \
	if [ ! -f "$$binary" ]; then echo "Windows executable not found: $$binary" >&2; exit 1; fi; \
	echo "==> Running $$binary with Wine"; \
	$(WINE) "$$binary"


# Build and run Windows debug.
run-windows-debug: windows-debug
	@set -e; \
	if [ -n "$(EXAMPLE)" ]; then dir="$(EXAMPLES_DIR)/$(EXAMPLE)/"; else dir="$(EXAMPLES_DIR)/Basic Window/"; fi; \
	if [ ! -d "$$dir" ]; then echo "Windows example folder not found: $$dir" >&2; exit 1; fi; \
	base="$${dir%/}"; base="$${base##*/}"; \
	name="$$(printf '%s' "$$base" | tr -d '[:space:]')"; \
	binary="$$dir$${name}DEBUG.exe"; \
	if [ ! -f "$$binary" ]; then echo "Windows debug executable not found: $$binary" >&2; exit 1; fi; \
	$(WINE) "$$binary"


# Remove generated files.
clean:
	rm -rf "$(BUILD_DIR)"
	@shopt -s nullglob; \
	for dir in "$(EXAMPLES_DIR)"/*/; do \
	    base="$${dir%/}"; base="$${base##*/}"; \
	    name="$$(printf '%s' "$$base" | tr -d '[:space:]')"; \
	    rm -f "$$dir$$name" "$$dir$$name.exe" "$$dir$${name}DEBUG.exe"; \
	done