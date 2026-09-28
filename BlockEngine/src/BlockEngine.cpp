#include "BlockEngine.hpp"
#include "Assets/BlockEngine/GeneratedAssets/Images/asset_Brick_icon_png.h"

int main() {
    // here we initialize the (Logger, Window, Input, Audio) and set the exit key.
    InitializeBlockEngine(800, 600, "Block Engine", BLOCK_KEY_ESCAPE, 1.0f, true);

    // You will have to put it in in {} because the AudioObject and (MyTriangle,MySquare) will have to destroy there resources before shutdown
    {
        // This is an audio object it make
        Audio AudioObject[2];
        
        AudioObject[0].LoadSound("src/Assets/BlockEngine/Audio/StartUp/start.mp3", BLOCK_SOUND_FLAG_NO_SPATIAL | BLOCK_SOUND_FLAG_NO_PITCH);
        AudioObject[1].LoadSound("src/Assets/BlockEngine/Audio/Sounds/Correct.mp3", BLOCK_SOUND_FLAG_NO_SPATIAL | BLOCK_SOUND_FLAG_NO_PITCH);

        Triangle MyTriangle(Color(0.0f, 0.0f, 0.0f, 255.0f));
        Square MySquare(Color(134.0f, 17.0f, 63.0f, 255.0f));
        
        Texture2D Brick;
        Brick.LoadTexture2D("src/Assets/BlockEngine/Images/Block-Engine/Brick-icon.png", BLOCK_NEAREST, BLOCK_NEAREST, BLOCK_TEXTURE_REPEAT, true);
        Brick.LoadTextureMesh("src/Assets/BlockEngine/Shaders/BasicVertexTextureShader.vert", "src/Assets/BlockEngine/Shaders/BasicFragmentTextureShader.frag", SquareVerticesUV, sizeof(SquareVerticesUV), SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]), false);
        
        Texture2D EmbeddedBrick;
        EmbeddedBrick.LoadEmbeddedTexture2D((const char*)BlockEngine_src_Assets_BlockEngine_Images_Block_Engine_Brick_icon_png, sizeof(BlockEngine_src_Assets_BlockEngine_Images_Block_Engine_Brick_icon_png), BLOCK_LINEAR, BLOCK_LINEAR, BLOCK_TEXTURE_REPEAT, true);
        EmbeddedBrick.LoadTextureMesh("src/Assets/BlockEngine/Shaders/BasicVertexTextureShader.vert", "src/Assets/BlockEngine/Shaders/BasicFragmentTextureShader.frag", SquareVerticesUV, sizeof(SquareVerticesUV), SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]), false);

        Color BGColor = {255.0f,255.0f,160.0f,255.0f};
    
        bool ChangeBackGroundColor = true;
        bool DrawBrick = true;
        bool DrawEmbeddedBrick = true;

        info("Entering Game Loop");
        while (!WindowShouldClose())
        {   
            // Change Audio         
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
            
            // Change Rendering 
            if(KeyEvent(BLOCK_KEY_TAB,BLOCK_PRESS))
            {
                BGColor = {(float)(rand() % 256), (float)(rand() % 256), (float)(rand() % 256), (float)(rand() % 256)};
            }
            if(KeyEvent(BLOCK_KEY_Q,BLOCK_PRESS))
            {
                if (DrawBrick)
                {
                    DrawBrick = false;
                }
                else
                {
                    DrawBrick = true;
                }
            }
            if(KeyEvent(BLOCK_KEY_W,BLOCK_PRESS))
            {
                if (DrawEmbeddedBrick)
                {
                    DrawEmbeddedBrick = false;
                }
                else
                {
                    DrawEmbeddedBrick = true;
                }
            }
            
            BackGroundColor(BGColor);
            MySquare.DrawSquare();
            MyTriangle.DrawTriangle();

            
            if (DrawBrick) {Brick.DrawTexture2D();}
            if (DrawEmbeddedBrick) {EmbeddedBrick.DrawTexture2D();}

            UpdateWindow();
        }
        info("Closed Window");
        info("Exited Game Loop");
    }

    BlockEngineShutdown();
    return 0;
}

