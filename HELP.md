# Block Engine Help

This file explains the basic tools and build commands included with Block Engine.

## 📁 Project Layout

    BlockEngine/       # Engine source and build files

    Examples/          # Example projects

    CompileCode        # Compile a project using the engine

    CompileEngine      # Build and run Block Engine itself

    CompileExamples    # Build and run the examples

    CleanEngine        # Clean the engine build

    RemoveLogs         # Remove generated log files

    HELP.md            # This help file

    README.md          # Project overview

    LICENSE.md         # Block Engine license

## 🛠️ CompileCode

`CompileCode` compiles your own `.cpp` program using the already-built Block Engine object files.

Before using `CompileCode`, you must build Block Engine first:

    ./CompileEngine

This creates the engine `.o` files that `CompileCode` uses.

`CompileCode` does **not** compile `BlockEngine.cpp`, because your program provides its own `main()` function.

### Basic usage

    ./CompileCode MyGame.cpp

The resulting executable is created from the name of your source file:

    MyGame.cpp → MyGame

### Optional compiler flags

You can manually enable additional options.

Enable debug information:

    ./CompileCode MyGame.cpp debug

Adds:

    -g

`-g` includes debugging information so tools such as GDB can show useful source-level information.

Enable AddressSanitizer:

    ./CompileCode MyGame.cpp asan

Adds:

    -fsanitize=address

AddressSanitizer helps detect memory errors such as buffer overflows and use-after-free.

You can also use both:

    ./CompileCode MyGame.cpp asan debug

## 🏗️ CompileEngine

Build and run the Block Engine itself:

    ./CompileEngine

This must be run before building or running examples because the examples use the compiled Block Engine `.o` files.

The engine uses its Make build file and keeps compiled `.o` files so unchanged source files do not need to be compiled again.

## 🧹 CleanEngine

Remove the engine executable and generated object files:

    ./CleanEngine

Use this when you want a clean rebuild.

After cleaning the engine, you must run:

    ./CompileEngine

before building examples or using `CompileCode`.

## 🎮 CompileExamples

Build and run the example project(s):

    ./CompileExamples

The examples use the already-compiled Block Engine `.o` files instead of recompiling the entire engine every time.

Because of this, you must build Block Engine first:

    ./CompileEngine

## 📦 Examples

The `Examples/` directory contains example source code and its build file:

    Examples/
    │
    ├── example.cpp
    ├── example
    ├── Example.mk
    └── Logs/

The example has its own `main()` function, so `BlockEngine.cpp` is not included when building it.

## 📝 Logs

Block Engine writes runtime logs into `Logs/` directories.

To remove generated logs, use:

    ./RemoveLogs

## ⚙️ Incremental Builds

The engine and examples reuse existing object files.

For example, if only this changes:

    BlockEngine/src/Audio/Audio.cpp

Make can rebuild only:

    BlockEngine/src/Audio/Audio.o

and then relink the executable.

Unchanged source files do not need to be compiled again.

## 💡 Quick Reference

    # Build and run the engine
    ./CompileEngine

    # Clean engine build files
    ./CleanEngine

    # Build and run examples
    ./CompileExamples

    # Compile your own program
    ./CompileCode MyGame.cpp

    # Compile with debug information
    ./CompileCode MyGame.cpp debug

    # Compile with AddressSanitizer
    ./CompileCode MyGame.cpp asan

    # Compile with both
    ./CompileCode MyGame.cpp asan debug

    # Remove logs
    ./RemoveLogs