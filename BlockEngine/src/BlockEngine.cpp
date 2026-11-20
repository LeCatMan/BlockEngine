#include "BlockEngine.hpp"
#include "Assets/BlockEngine/GeneratedAssets/GeneratedAssets.hpp"



int main() {
    // here we initialize the (Logger, Rendering, Input, Audio ...).
    InitializeBlockEngine(1.0f);


    // You will have to put it in in {} because the AudioObject and (MyTriangle,MySquare) will have to destroy there resources before shutdown
    {
        BlockWindow Window;
        Window.CreateWindow(800, 600, "Block Engine", BLOCK_KEY_ESCAPE, true, 0, NULL);

        // This is an audio object it make
        Audio AudioObject[2];
        
        AudioObject[0].LoadSound("src/Assets/BlockEngine/Audio/StartUp/start.mp3", BLOCK_SOUND_FLAG_NO_SPATIAL | BLOCK_SOUND_FLAG_NO_PITCH);
        AudioObject[1].LoadSound("src/Assets/BlockEngine/Audio/Sounds/Correct.mp3", BLOCK_SOUND_FLAG_NO_SPATIAL | BLOCK_SOUND_FLAG_NO_PITCH);

        Triangle MyTriangle;
        MyTriangle.Create(Color(0.0f, 0.0f, 0.0f, 255.0f), &Window.Window, 1, true);
        Square MySquare;
        MySquare.Create(Color(134.0f, 17.0f, 63.0f, 255.0f), &Window.Window, 1, true);
        
        Texture2D Brick;
        Brick.LoadTexture2D("src/Assets/BlockEngine/Images/Block-Engine/Brick-icon.png", BLOCK_NEAREST, BLOCK_NEAREST, true);
        Brick.LoadTextureMesh2D("src/Assets/BlockEngine/Shaders/BasicVertexTextureShader.vert", "src/Assets/BlockEngine/Shaders/BasicFragmentTextureShader.frag", SquareVerticesUV, sizeof(SquareVerticesUV), SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]), false, BLOCK_TEXTURE_REPEAT, Color{255.0f, 0.0f, 255.0f, 255.0f}, Color{255.0f, 255.0f, 255.0f, 255.0f}, &Window.Window, 1);
        
        Texture2D EmbeddedBrick;
        EmbeddedBrick.LoadEmbeddedTexture2D((const char*)asset_Brick_icon_png, sizeof(asset_Brick_icon_png), BLOCK_LINEAR, BLOCK_LINEAR, true);
        EmbeddedBrick.LoadEmbeddedTextureMesh2D(asset_BasicVertexTextureShader_vert, asset_BasicFragmentTextureShader_frag, SquareVerticesUV, sizeof(SquareVerticesUV), SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]), false, BLOCK_TEXTURE_REPEAT, Color{255.0f, 0.0f, 255.0f, 255.0f}, Color{255.0f, 255.0f, 255.0f, 255.0f}, &Window.Window, 1);

        Color BGColor = {255.0f,255.0f,160.0f,255.0f};
    
        bool DrawBrick = true;
        bool DrawEmbeddedBrick = true;

        Color color = {255.0f,255.0f,255.0f,255.0f};
        int FPS = 0;
        float dirR = 1.0f, dirG = 1.0f, dirB = 1.0f;
        float speed = 0.005f;

        info("Entering Game Loop");
        while (!Window.WindowShouldClose())
        {
            if (FPS >= 60)
            {
                FPS = 0;
            }
            else
            {
                FPS++;
                
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
                if(KeyEvent(BLOCK_KEY_P,BLOCK_PRESS))
                {
                    Window.RestoreWindow();
                }

                Window.SetBackgroundColor(BGColor);
                MySquare.Draw(1, false, Color{255.0f, 255.0f, 255.0f, 255.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{0.0f, 0.0f, GetTime()*100}, FloatVector3{1.0f, 1.0f, 1.0f});
                MyTriangle.Draw(1, false, Color{255.0f, 255.0f, 255.0f, 255.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{1.0f, 1.0f, 1.0f});

                if (color.r >= 1.0f) { color.r = 1.0f; dirR = -1.0f; }
                if (color.r <= 0.0f) { color.r = 0.0f; dirR =  1.0f; }

                if (color.g >= 1.0f) { color.g = 1.0f; dirG = -1.0f; }
                if (color.g <= 0.0f) { color.g = 0.0f; dirG =  1.0f; }

                if (color.b >= 1.0f) { color.b = 1.0f; dirB = -1.0f; }
                if (color.b <= 0.0f) { color.b = 0.0f; dirB =  1.0f; }

                color.r += dirR * speed;
                color.g += dirG * speed;
                color.b += dirB * speed;
                
                if (DrawBrick) {Brick.Draw(1, false, color, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{1.0f, 1.0f, 1.0f});}
                if (DrawEmbeddedBrick) {EmbeddedBrick.Draw(1, false, color, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{1.0f, 1.0f, 1.0f});}

                Window.UpdateWindow();
            }
        }
        info("Exited Game Loop");
    }

    ShutDownBlockEngine();
    return 0;
}

