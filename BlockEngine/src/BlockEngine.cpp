#include "BlockEngine.hpp"


int main() {  
    InitializeBlockEngine(800, 600, "Block Engine", BLOCK_KEY_ESCAPE);
    //AudioPlay("src/Assets/BlockEngine/Audio/StartUp/start.mp3");

    {
        Audio UI[2];
        UI[0].LoadSound("src/Assets/BlockEngine/Audio/StartUp/start.mp3");
        UI[1].LoadSound("src/Assets/BlockEngine/Audio/Sounds/Correct.mp3");
        Triangle MyTriangle(Color(180,180,180));
        Square MySquare(Color(155,155,180));

        info("Entering Game Loop");
        while (!WindowShouldClose())
        {
            UpdateWindow();
            if(KeyEvent(BLOCK_KEY_F,BLOCK_PRESS))
            {
                UI[0].PlaySound();
            }
            if(KeyEvent(BLOCK_KEY_G,BLOCK_RELEASE))
            {
                UI[1].PlaySound();
            }
            if(KeyEvent(BLOCK_KEY_H,BLOCK_REPEAT))
            {
                UI[1].PlaySound();
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
