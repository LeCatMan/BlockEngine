#!/bin/bash

g++ -g $(find src -name '*.cpp') \
    external/glad/src/glad.c \
    -Iexternal/glfw-3.5.1/include \
    -Iexternal/glad/include \
    external/glfw-3.5.1/build/src/libglfw3.a \
    -o Block-Engine \
    -lGL -lm -ldl -lpthread -lX11 -lXrandr -lXi -lXxf86vm -lXcursor

./Block-Engine
