CXX = g++

CXXFLAGS = -Isrc -Iexternal/glad/include
LDFLAGS =

ASAN = 1

ifeq ($(ASAN),1)
	CXXFLAGS += -g -fsanitize=address
	LDFLAGS += -fsanitize=address
endif

SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

TARGET = BlockEngine

all: $(TARGET)

$(TARGET): $(OBJ) external/glad/src/glad.o
	$(CXX) $^ -o $@ $(LDFLAGS) -lGL -lglfw -ldl -lm -lcrypto

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

external/glad/src/glad.o: external/glad/src/glad.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

off:
	$(MAKE) clean
	$(MAKE) ASAN=0

clean:
	rm -f $(TARGET) $(OBJ) external/glad/src/glad.o
