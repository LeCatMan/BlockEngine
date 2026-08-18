# Block Engine

Block Engine is a free-to-use game engine.

You can use it, modify it, study it, and share it for free. You can also use it to make commercial games, applications, and other products.

## Preview

### Preview Image:

<img width="800" height="632" alt="BlockEngineAlpha0 5Preview" src="https://github.com/user-attachments/assets/01dbb55c-abf5-49b8-8d0a-f74fe671de95" />

### Console Output:


<pre><font color="#C061CB"><b>lecatman@daniel7</b></font>:<font color="#2A7BDE"><b>~/Projects/C/Block-Engine</b></font>$ run
make: Nothing to be done for &apos;all&apos;.
./Block-Engine
[<b>INFO</b>] -&gt; Info in &lt;<b>src/Debugger/Logger/Logger.cpp</b>&gt; at line &lt;<b>173</b>&gt;: &lt;<b>Logger initialized: Logs/Log-001.txt</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.hpp</b>&gt; at line &lt;<b>11</b>&gt;: &lt;<b>Launching BlockEngine</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/Rendering/RenderingUtilities/RenderingUtilities.hpp</b>&gt; at line &lt;<b>81</b>&gt;: &lt;<b>Creating Triangle Resources</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.cpp</b>&gt; at line &lt;<b>12</b>&gt;: &lt;<b>Entering Game Loop</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.cpp</b>&gt; at line &lt;<b>32</b>&gt;: &lt;<b>Closed Window</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.cpp</b>&gt; at line &lt;<b>33</b>&gt;: &lt;<b>Exited Game Loop</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/Rendering/RenderingUtilities/RenderingUtilities.cpp</b>&gt; at line &lt;<b>326</b>&gt;: &lt;<b>Destroyed the Shapes resources</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/Rendering/RenderingUtilities/RenderingUtilities.cpp</b>&gt; at line &lt;<b>326</b>&gt;: &lt;<b>Destroyed the Shapes resources</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.hpp</b>&gt; at line &lt;<b>20</b>&gt;: &lt;<b>Closing Program</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.hpp</b>&gt; at line &lt;<b>23</b>&gt;: &lt;<b>Closed Program</b>&gt;
<font color="#C061CB"><b>lecatman@daniel</b></font>:<font color="#2A7BDE"><b>~/Projects/C/Block-Engine</b></font>$ 
</pre>


### Main Example:

```code
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
            if(KeyEvent(BLOCK_KEY_H,BLOCK_PRESS))
            {
                AudioPlay("src/Assets/Audio/Sounds/Correct.mp3");
            }
            BackGroundColor(Color(255,255,160), 255);
            MySquare.DrawSquare();
            MyTriangle.DrawTriangle();
            UpdateWindow();
        }
        info("Closed Window");
        info("Exited Game Loop");
    }

    ShutdownBlockEngine();
    return 0;
}

```


## Development Status

Block Engine is currently in **Alpha 0.51** and is still actively being developed.

The engine is an early version, so features may change, break, or be replaced as development continues.

Block Engine is currently **Linux-exclusive**. Support for **Windows** will be considered after both **2D and 3D** support have been implemented.

The long-term goal is to support both **2D and 3D** game development.

Current development is focused on building the core engine and gradually expanding its capabilities.

The main restriction is simple:

**You can make money using Block Engine, but you cannot make money by selling Block Engine itself as development technology.**

## What You Can Do

| Action | Allowed? |
|---|:---:|
| Use Block Engine freely                                      | **YES** |
| Modify Block Engine                                          | **YES** |
| Share Block Engine for free                                  | **YES** |
| Build and sell a commercial game/product                     | **YES** |
| Make money providing your own work or services               | **YES** |
| Use Block Engine internally within a company                 | **YES** |
| Sell Block Engine itself                                     | **NO** |
| Sell a Modified Engine                                       | **NO** |
| Sell Block Engine as developer technology                    | **NO** |
| Commercially host/provide the engine remotely                | **NO** |
| Hide the engine behind a wrapper or similar arrangement      | **NO** |
| Use a fake/minimal "game" to commercially provide the engine | **NO** |

> This License does not restrict anyone from independently creating software that competes with Block Engine, provided that Block Engine or a Modified Engine is not used as the basis for that software.
