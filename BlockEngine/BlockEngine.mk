CXX = g++
CXXFLAGS = -Isrc -Iexternal/glad/include
LDFLAGS =

# ASAN is now 0 (OFF) by default
ASAN ?= 0

ifeq ($(ASAN),1)
    CXXFLAGS += -g -fsanitize=address
    LDFLAGS += -fsanitize=address
    TARGET = BlockEngineDEBUG
else
    TARGET = BlockEngine
endif

SRC = $(shell find src -name "*.cpp")
OBJ = $(SRC:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJ) external/glad/src/glad.o
	$(CXX) $^ -o $@ $(LDFLAGS) -lGL -lglfw -ldl -lm -lcrypto

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

external/glad/src/glad.o: external/glad/src/glad.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

# Type 'make san' to wipe, build with AddressSanitizer, and run
san:
	$(MAKE) -f BlockEngine.mk clean
	$(MAKE) -f BlockEngine.mk ASAN=1
	./BlockEngineDEBUG

clean:
	rm -f BlockEngine BlockEngineDEBUG $(OBJ) external/glad/src/glad.o
