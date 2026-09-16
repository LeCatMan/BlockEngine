#include "BlockEngine.hpp"


int main() {
    // here we initialize the (Logger, Window, Input, Audio) and set the exit key.
    InitializeBlockEngine(800, 600, "Block Engine", BLOCK_KEY_ESCAPE, 1.0f, true);

    // You will have to put it in in {} because the AudioObject and (MyTriangle,MySquare) will have to destroy there resources before shutdown
    {
        // This is an audio object it make
        Audio AudioObject[2];
        AudioObject[0].LoadSound("src/Assets/BlockEngine/Audio/StartUp/start.mp3", BLOCK_SOUND_FLAG_NO_SPATIAL | BLOCK_SOUND_FLAG_NO_PITCH);
        AudioObject[1].LoadSound("src/Assets/BlockEngine/Audio/Sounds/Correct.mp3", BLOCK_SOUND_FLAG_NO_SPATIAL | BLOCK_SOUND_FLAG_NO_PITCH);
        Triangle MyTriangle(Color(180.0f, 180.0f, 180.0f, 255.0f));
        Square MySquare(Color(155.0f, 155.0f, 180.0f, 255.0f));
        Texture Brick;
        Brick.LoadTexture("src/Assets/BlockEngine/Images/Block-Engine/Block.png", GL_NEAREST, GL_NEAREST);
        Brick.LoadTextureMesh(Color(0.0f, 0.0f, 0.0f, 255.0f), "src/Assets/BlockEngine/Shaders/BasicVertexTextureShader.vert", "src/Assets/BlockEngine/Shaders/BasicFragmentTextureShader.frag", SquarePosColorUV, sizeof(SquarePosColorUV), SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]), true);
        

        info("Entering Game Loop");
        while (!WindowShouldClose())
        {            
            if(KeyEvent(BLOCK_KEY_F,BLOCK_PRESS))
            {
                AudioObject[0].PlayOverlappingSound();
            }
            if(KeyEvent(BLOCK_KEY_G,BLOCK_RELEASE))
            {
                AudioObject[1].PlaySound();
            }
            if(KeyEvent(BLOCK_KEY_H,BLOCK_REPEAT))
            {
                AudioObject[1].PlaySound();
            }
            if(KeyEvent(BLOCK_KEY_Y,BLOCK_REPEAT))
            {
                AudioObject[0].PlayOverlappingSound();
            }
            BackGroundColor(Color(255.0f,255.0f,160.0f,255.0f));
            MySquare.DrawSquare();
            MyTriangle.DrawTriangle();
            Brick.DrawTexture2D();
            UpdateWindow();
        }
        info("Closed Window");
        info("Exited Game Loop");
    }

    BlockEngineShutdown();
    return 0;
}

