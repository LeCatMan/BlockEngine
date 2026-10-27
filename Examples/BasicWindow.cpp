#include "../src/BlockEngine.hpp"

int main()
{
    // here we initialize the (Logger, Rendering, Input, Audio ...).
    InitializeBlockEngine(1.0f);


    // You will have to put it in in {} because the AudioObject and (MyTriangle,MySquare) will have to destroy there resources before shutdown
    {
        BlockWindow Window;
        Window.CreateWindow(800, 600, "Block Engine", BLOCK_KEY_ESCAPE, true, 0, NULL);
        Color BGColor = {255.0f,255.0f,160.0f,255.0f};

        info("Entering Game Loop");
        while (!Window.WindowShouldClose())
        {   
            Window.BackGroundColor(BGColor);
            Window.UpdateWindow();
        }
        info("Exited Game Loop");
    }

    BlockEngineShutdown();
    return 0;
}

