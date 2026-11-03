#include "../../BlockEngine/src/BlockEngine.hpp"

int main()
{
    // here we initialize the (Logger, Rendering, Input, Audio ...).
    InitializeBlockEngine(1.0f);


    // You will have to put it in in {} because the AudioObject and (MyTriangle,MySquare) will have to destroy there resources before shutdown
    {
        BlockWindow Window1;
        Window1.CreateWindow(800, 600, "1", BLOCK_KEY_1, true, 0, NULL);
        BlockWindow Window2;
        Window2.CreateWindow(800, 600, "2", BLOCK_KEY_2, true, 0, NULL);
        Color BGColor = {255.0f,255.0f,160.0f,255.0f};

        info("Entering Game Loop");
        while (!Window1.WindowShouldClose() || !Window2.WindowShouldClose())
        {
            if (!Window1.WindowShouldClose())
            {
                Window1.SetBackgroundColor(BGColor);
                Window1.UpdateWindow();
            }
            if (!Window2.WindowShouldClose())
            {
                Window2.SetBackgroundColor(BGColor);
                Window2.UpdateWindow();
            }
        }
        info("Exited Game Loop");
    }

    ShutDownBlockEngine();
    return 0;
}
