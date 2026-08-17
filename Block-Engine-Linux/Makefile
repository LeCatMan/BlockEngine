CXX = g++

CXXFLAGS = -Isrc -Iexternal/glad/include -fsanitize=address -g
LDFLAGS = -fsanitize=address

SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

TARGET = Block-Engine

all: $(TARGET)

$(TARGET): $(OBJ) external/glad/src/glad.o
	$(CXX) $^ -o $@ $(LDFLAGS) -lGL -lglfw -ldl -lm -lcrypto

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

external/glad/src/glad.o: external/glad/src/glad.c
	$(CXX) -Iexternal/glad/include -fsanitize=address -g -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJ) external/glad/src/glad.o