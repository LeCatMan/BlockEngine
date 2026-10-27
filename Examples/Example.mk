
CXX = g++
CC = gcc
WINCXX = x86_64-w64-mingw32-g++

CXXFLAGS = -I../BlockEngine/src -I../BlockEngine/external/glad/include
CFLAGS = -I../BlockEngine/external/glad/include
LDFLAGS =

TARGET = BasicWindow
WIN_TARGET = BasicWindow.exe
WIN_DEBUG_TARGET = BasicWindowDEBUG.exe

ENGINE_SRC = $(shell find ../BlockEngine/src -name "*.cpp" ! -name "BlockEngine.cpp")
SRC = BasicWindow.cpp

OBJ = $(SRC:.cpp=.o)
ENGINE_OBJ = $(ENGINE_SRC:.cpp=.o)
GLAD_OBJ = ../BlockEngine/external/glad/src/glad.o

WIN_GLFW = ../BlockEngine/external/glfw-3.5.1/build-win/src/libglfw3.a
WIN_GLFW_INCLUDE = ../BlockEngine/external/glfw-3.5.1/include

WIN_LIBS = -L../BlockEngine/external/glfw-3.5.1/build-win/src \
           -lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32 -lwinmm \
           -static-libgcc -static-libstdc++

# Linux build
all: $(TARGET)

$(TARGET): $(OBJ) $(ENGINE_OBJ) $(GLAD_OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS) -lGL -lglfw -ldl -lm -lcrypto

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(GLAD_OBJ): ../BlockEngine/external/glad/src/glad.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

# Windows release build
windows: $(WIN_TARGET)

$(WIN_TARGET): $(SRC) $(ENGINE_SRC) ../BlockEngine/external/glad/src/glad.c $(WIN_GLFW)
	$(WINCXX) $(CXXFLAGS) $(SRC) $(ENGINE_SRC) \
		../BlockEngine/external/glad/src/glad.c \
		-I$(WIN_GLFW_INCLUDE) \
		$(WIN_LIBS) -o $@

run-windows: $(WIN_TARGET)
	wine ./$(WIN_TARGET)

# Windows debug build
windows-debug: $(WIN_DEBUG_TARGET)

$(WIN_DEBUG_TARGET): $(SRC) $(ENGINE_SRC) ../BlockEngine/external/glad/src/glad.c $(WIN_GLFW)
	$(WINCXX) -g $(CXXFLAGS) $(SRC) $(ENGINE_SRC) \
		../BlockEngine/external/glad/src/glad.c \
		-I$(WIN_GLFW_INCLUDE) \
		$(WIN_LIBS) -o $@

# Clean build outputs
clean:
	rm -f $(WIN_DEBUG_TARGET) \
		$(OBJ) $(ENGINE_OBJ) $(GLAD_OBJ)

.PHONY: all run windows run-windows windows-debug clean
