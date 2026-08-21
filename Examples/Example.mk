CXX = g++

CXXFLAGS = -I../BlockEngine/src \
           -I../BlockEngine/external/glad/include

LDFLAGS =

ASAN = 1

ifeq ($(ASAN),1)
	CXXFLAGS += -fsanitize=address -g
	LDFLAGS += -fsanitize=address
endif

TARGET = example

ENGINE_SRC = $(shell find ../BlockEngine/src -name "*.cpp" ! -name "BlockEngine.cpp")
ENGINE_OBJ = $(ENGINE_SRC:.cpp=.o)

GLAD_OBJ = ../BlockEngine/external/glad/src/glad.o
EXAMPLE_OBJ = example.o

all: $(TARGET)

$(TARGET): $(EXAMPLE_OBJ) $(ENGINE_OBJ) $(GLAD_OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS) -lGL -lglfw -ldl -lm -lcrypto

example.o: example.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

off:
	$(MAKE) clean
	$(MAKE) ASAN=0

clean:
	rm -f $(TARGET) $(EXAMPLE_OBJ)
