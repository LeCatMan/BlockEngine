#include "../../BlockEngine/src/BlockEngine.hpp"

int main()
{
    // here we initialize the (Logger, Rendering, Input, Audio ...).
    InitializeBlockEngine(1.0f);


    // You will have to put it in in {} because the AudioObject and (MyTriangle,MySquare) will have to destroy there resources before shutdown
    {
        BlockWindow Windows[2];
        Windows[0].CreateWindow(800, 600, "1", BLOCK_KEY_1, true, 0, NULL);
        Windows[1].CreateWindow(800, 600, "2", BLOCK_KEY_2, true, 0, NULL);
        Color BGColor = {255.0f,255.0f,160.0f,255.0f};

        Blockwindow *WindowPointers[2] = { Windows[0].Window, Windows[1].Window };

        Triangle MyTriangle;
        MyTriangle.Create(Color(0.0f, 0.0f, 0.0f, 255.0f), WindowPointers, 2, false);
        Square MySquare;
        MySquare.Create(Color(134.0f, 17.0f, 63.0f, 255.0f), WindowPointers, 2, true);
        

        info("Entering Game Loop");
        while (!Windows[0].WindowShouldClose() || !Windows[1].WindowShouldClose())
        {
            if (!Windows[0].WindowShouldClose())
            {
                Windows[0].SetBackgroundColor(BGColor);
                MyTriangle.Draw(1, true, Color{0.0f, 255.0f, 0.0f, 255.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{1.0f, 1.0f, 1.0f});
                MySquare.Draw(1, false, Color{0.0f, 255.0f, 0.0f, 255.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{1.0f, 1.0f, 1.0f});
                Windows[0].UpdateWindow();
            }
            if (!Windows[1].WindowShouldClose())
            {
                Windows[1].SetBackgroundColor(BGColor);
                MyTriangle.Draw(2, false, Color{0.0f, 255.0f, 0.0f, 255.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{1.0f, 1.0f, 1.0f});
                MySquare.Draw(2, true, Color{0.0f, 255.0f, 0.0f, 255.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{0.0f, 0.0f, 0.0f}, FloatVector3{1.0f, 1.0f, 1.0f});
                Windows[1].UpdateWindow();
            }
            if (KeyEvent(BLOCK_KEY_R, BLOCK_PRESS))
            {
                Windows[0].RestoreWindow();
            }
            
        }
        info("Exited Game Loop");
    }

    ShutDownBlockEngine();
    return 0;
}
