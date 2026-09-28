
// This is a basic window.

#include "BlockEngine.hpp"

int main() {
    // here we initialize the (Logger, Window, Input, Audio) and set the exit key.
    InitializeBlockEngine(800, 600, "Block Engine", BLOCK_KEY_ESCAPE, 1.0f, true);

    // You will have to put it in in {} because the AudioObject and (MyTriangle,MySquare) will have to destroy there resources before shutdown
    {
        Color BGColor = {255.0f,255.0f,160.0f,255.0f};

        info("Entering Game Loop");
        while (!WindowShouldClose())
        {   
            BackGroundColor(BGColor);

            UpdateWindow();
        }
        info("Closed Window");
        info("Exited Game Loop");
    }

    BlockEngineShutdown();
    return 0;
}