CXX = g++
WINCXX = x86_64-w64-mingw32-g++

CXXFLAGS = -Isrc -Iexternal/glad/include
LDFLAGS =

DEBUGFLAGS = -g -O0 -Wall -Wextra -Wshadow -Wsign-compare -D_GLIBCXX_ASSERTIONS
SANFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer

SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

LINUXLIBS = -lGL -lglfw -ldl -lm -lcrypto

WINLIBS = -Iexternal/glfw-3.5.1/include \
	-Lexternal/glfw-3.5.1/build-win/src \
	-lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32 -lwinmm \
	-static-libgcc -static-libstdc++

all: BlockEngine

# ---------- Linux ----------

BlockEngine: $(OBJ) external/glad/src/glad.o
	$(CXX) $^ -o $@ $(LDFLAGS) $(LINUXLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

external/glad/src/glad.o: external/glad/src/glad.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: BlockEngine
	./BlockEngine

# ---------- Linux gdb (no sanitizers) ----------

gdb: BlockEngineGDB
	gdb ./BlockEngineGDB

BlockEngineGDB: $(SRC) external/glad/src/glad.c
	$(CXX) $(DEBUGFLAGS) $(CXXFLAGS) $(SRC) external/glad/src/glad.c -o $@ $(LINUXLIBS)

# ---------- Linux sanitizers (no gdb) ----------

san: BlockEngineSAN
	./BlockEngineSAN

BlockEngineSAN: $(SRC) external/glad/src/glad.c
	$(CXX) $(DEBUGFLAGS) $(SANFLAGS) $(CXXFLAGS) $(SRC) external/glad/src/glad.c -o $@ $(LINUXLIBS)

# ---------- Windows ----------

windows: BlockEngine.exe

BlockEngine.exe: $(SRC) external/glad/src/glad.c external/glfw-3.5.1/build-win/src/libglfw3.a
	$(WINCXX) $(CXXFLAGS) $(SRC) external/glad/src/glad.c $(WINLIBS) -o $@

run-windows: BlockEngine.exe
	wine ./BlockEngine.exe

# ---------- Windows gdb (no sanitizers on MinGW) ----------

windows-debug: BlockEngineDEBUG.exe

BlockEngineDEBUG.exe: $(SRC) external/glad/src/glad.c external/glfw-3.5.1/build-win/src/libglfw3.a
	$(WINCXX) $(DEBUGFLAGS) $(CXXFLAGS) $(SRC) external/glad/src/glad.c $(WINLIBS) -o $@

gdb-windows: BlockEngineDEBUG.exe
	winedbg --gdb ./BlockEngineDEBUG.exe

# ---------- Clean ----------

clean:
	rm -f BlockEngineGDB BlockEngineSAN BlockEngineDEBUG.exe $(OBJ) external/glad/src/glad.o
