#include "BlockEngine.hpp"// we include this because we need it :D

int main() {
    // here we initialize the (Logger, Window, Input, Audio) and set the exit key
    InitializeBlockEngine(800, 600, "Block Engine", BLOCK_KEY_ESCAPE);

    {
        Audio AudioObject[2];
        AudioObject[0].LoadSound("src/Assets/BlockEngine/Audio/StartUp/start.mp3");
        AudioObject[1].LoadSound("src/Assets/BlockEngine/Audio/Sounds/Correct.mp3");
        Triangle MyTriangle(Color(180,180,180));
        Square MySquare(Color(155,155,180));

        info("Entering Game Loop");
        while (!WindowShouldClose())
        {
            UpdateWindow();
            if(KeyEvent(BLOCK_KEY_F,BLOCK_PRESS))
            {
                AudioObject[0].PlaySound();
            }
            if(KeyEvent(BLOCK_KEY_G,BLOCK_RELEASE))
            {
                AudioObject[1].PlaySound();
            }
            if(KeyEvent(BLOCK_KEY_H,BLOCK_REPEAT))
            {
                AudioObject[1].PlaySound();
            }
            BackGroundColor(Color(255,255,160), 255);
            MySquare.DrawSquare();
            MyTriangle.DrawTriangle();
        }
        info("Closed Window");
        info("Exited Game Loop");
    }

    ShutdownBlockEngine();
    return 0;
}
