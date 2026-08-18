#include "BlockEngine.hpp"


int main() {  
    InitializeBlockEngine(800, 600, "Block Engine", BLOCK_KEY_ESCAPE);
    AudioPlay("src/Assets/Audio/StartUp/start.mp3");

    {
        Triangle MyTriangle(Color(180,180,180));
        Square MySquare(Color(155,155,180));
        
        info("Entering Game Loop");
        while (!WindowShouldClose())
        {
            UpdateWindow();
            if(KeyEvent(BLOCK_KEY_F,BLOCK_PRESS))
            {
                AudioPlay("src/Assets/Audio/Sounds/Correct.mp3");
            }
            if(KeyEvent(BLOCK_KEY_G,BLOCK_RELEASE))
            {
                AudioPlay("src/Assets/Audio/Sounds/Correct.mp3");
            }
            if(KeyEvent(BLOCK_KEY_H,BLOCK_REPEAT))
            {
                AudioPlay("src/Assets/Audio/Sounds/Correct.mp3");
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
