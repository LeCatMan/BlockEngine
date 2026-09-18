CXX = g++
WINCXX = x86_64-w64-mingw32-g++

CXXFLAGS = -Isrc -Iexternal/glad/include
LDFLAGS =

SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

all: BlockEngine

BlockEngine: $(OBJ) external/glad/src/glad.o
	$(CXX) $^ -o $@ $(LDFLAGS) -lGL -lglfw -ldl -lm -lcrypto

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

external/glad/src/glad.o: external/glad/src/glad.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: BlockEngine
	./BlockEngine

windows: BlockEngine.exe

BlockEngine.exe: $(SRC) external/glad/src/glad.c external/glfw-3.5.1/build-win/src/libglfw3.a
	$(WINCXX) $(CXXFLAGS) $(SRC) external/glad/src/glad.c \
	-Iexternal/glfw-3.5.1/include \
	-Lexternal/glfw-3.5.1/build-win/src \
	-lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32 -lwinmm \
	-static-libgcc -static-libstdc++ \
	-o $@

run-windows: BlockEngine.exe
	wine ./BlockEngine.exe

windows-debug: BlockEngineDEBUG.exe

BlockEngineDEBUG.exe: $(SRC) external/glad/src/glad.c external/glfw-3.5.1/build-win/src/libglfw3.a
	$(WINCXX) -g $(CXXFLAGS) $(SRC) external/glad/src/glad.c \
	-Iexternal/glfw-3.5.1/include \
	-Lexternal/glfw-3.5.1/build-win/src \
	-lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32 -lwinmm \
	-static-libgcc -static-libstdc++ \
	-o $@

clean:
	rm -f BlockEngine BlockEngine.exe BlockEngineDEBUG.exe $(OBJ) external/glad/src/glad.o
