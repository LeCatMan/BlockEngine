## Block Engine Vision

Block Engine is made for people who want things to be simple without taking control away from them.

The **Block Engine API** is the core of the project and grows alongside the engine. The engine itself acts as an interface for the API, providing the systems and tools developers use to make their games.

The engine is mainly there to make common tasks easier, not to create a separate, slower way of doing things.

You don't have to bash your head against the wall just to make a square. But if you *want* to bash your head against the wall and work with the lower-level systems, you're welcome to join me.

Block Engine tries to give you both: simplicity when you want it, and control when you need it.

## Preview

### Preview

<img width="800" height="632" alt="BlockEngineAlpha0 5Preview" src="https://github.com/user-attachments/assets/01dbb55c-abf5-49b8-8d0a-f74fe671de95" />

### Console Output

<pre><font color="#C061CB"><b>lecatman@daniel7</b></font>:<font color="#2A7BDE"><b>~/Projects/C/Block-Engine</b></font>$ ./run
make: Nothing to be done for &apos;all&apos;.
./Block-Engine
[<b>INFO</b>] -&gt; Info in &lt;<b>src/Debugger/Logger/Logger.cpp</b>&gt; at line &lt;<b>173</b>&gt;: &lt;<b>Logger initialized: Logs/Log-001.txt</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.hpp</b>&gt; at line &lt;<b>11</b>&gt;: &lt;<b>Launching BlockEngine</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/Rendering/RenderingUtilities/RenderingUtilities.hpp</b>&gt; at line &lt;<b>92</b>&gt;: &lt;<b>Creating Triangle Resources</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.cpp</b>&gt; at line &lt;<b>12</b>&gt;: &lt;<b>Entering Game Loop</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.cpp</b>&gt; at line &lt;<b>32</b>&gt;: &lt;<b>Closed Window</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.cpp</b>&gt; at line &lt;<b>33</b>&gt;: &lt;<b>Exited Game Loop</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/Rendering/RenderingUtilities/RenderingUtilities.cpp</b>&gt; at line &lt;<b>591</b>&gt;: &lt;<b>Destroyed the Shapes resources</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/Rendering/RenderingUtilities/RenderingUtilities.cpp</b>&gt; at line &lt;<b>591</b>&gt;: &lt;<b>Destroyed the Shapes resources</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.hpp</b>&gt; at line &lt;<b>20</b>&gt;: &lt;<b>Closing Program</b>&gt;
[<b>INFO</b>] -&gt; Info in &lt;<b>src/BlockEngine.hpp</b>&gt; at line &lt;<b>23</b>&gt;: &lt;<b>Closed Program</b>&gt;
<font color="#C061CB"><b>lecatman@daniel</b></font>:<font color="#2A7BDE"><b>~/Projects/C/Block-Engine</b></font>$ 
</pre>

### Main Example

```cpp
#include "BlockEngine.hpp"


int main() {  
    InitializeBlockEngine(800, 600, "Block Engine", BLOCK_KEY_ESCAPE);
    AudioPlay("src/Assets/BlockEngine/Audio/StartUp/start.mp3");

    {
        Triangle MyTriangle(Color(180,180,180));
        Square MySquare(Color(155,155,180));

        info("Entering Game Loop");
        while (!WindowShouldClose())
        {
            UpdateWindow();
            if(KeyEvent(BLOCK_KEY_F,BLOCK_PRESS))
            {
                AudioPlay("src/Assets/BlockEngine/Audio/Sounds/Correct.mp3");
            }
            if(KeyEvent(BLOCK_KEY_G,BLOCK_RELEASE))
            {
                AudioPlay("src/Assets/BlockEngine/Audio/Sounds/Correct.mp3");
            }
            if(KeyEvent(BLOCK_KEY_H,BLOCK_REPEAT))
            {
                AudioPlay("src/Assets/BlockEngine/Audio/Sounds/Correct.mp3");
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
```

## Development Status

Block Engine is currently in **Alpha 0.57** and is still actively being developed.

The engine is an early version, so features may change, break, or be replaced as development continues.

Block Engine is currently **Linux-exclusive**. Support for **Windows** will be considered after both **2D and 3D** support have been implemented.

The long-term goal is to support both **2D and 3D** game development.

Current development is focused on building the core engine and gradually expanding its capabilities.

## License Summary

You can make money using Block Engine, including by creating and selling Products, providing your own services, creating and selling Mods, plugins, add-ons, extensions, tools, assets, and other independently created software for use with Block Engine.

You may freely use, study, modify, fork, and share Block Engine and create Modified Engines. **Modified Engines may be shared for free, but may not themselves be commercially provided as Development Technology.**

You may also create and commercially distribute independently created software that works with, extends, integrates with, or competes with Block Engine. Such software does not become Block Engine Development Technology merely because it is designed for Block Engine or provides additional functionality for Developers.

You may include Engine Materials and Modified Engine code in a genuine Product, including substantial portions where incorporated into the Product as part of its operation. You may commercially distribute and sell that Product.

You may not commercially provide Block Engine, a Modified Engine, or Block Engine Development Technology to Developers as Development Technology. This includes selling, licensing, renting, leasing, hosting, remotely providing, or otherwise commercially offering the engine or its development functionality.

The following is a plain-language summary of the permissions and restrictions in the Block Engine License. It is provided **for informational convenience only** and does not replace, supplement, override, expand, restrict, or otherwise modify the Block Engine License. **The Block Engine License is the controlling legal document and takes precedence over this summary in all circumstances.**

| Action | Allowed? |
| --- | :---: |
| Use Block Engine | **YES** |
| Study Block Engine | **YES** |
| Modify Block Engine | **YES** |
| Fork Block Engine | **YES** |
| Create a Modified Engine | **YES** |
| Share Block Engine for free | **YES** |
| Share a Modified Engine for free | **YES** |
| Create and sell a Product made with Block Engine | **YES** |
| Include Engine Materials in a commercial Product | **YES** |
| Include Modified Engine code in a commercial Product | **YES** |
| Create and distribute Mods | **YES** |
| Sell independently created Mods | **YES** |
| Create plugins, add-ons, and extensions | **YES** |
| Sell independently created plugins, add-ons, and extensions | **YES** |
| Create independent tools for Block Engine | **YES** |
| Sell independently created tools | **YES** |
| Create independent software that works with Block Engine | **YES** |
| Sell independently created software that works with Block Engine | **YES** |
| Create independently developed competing software | **YES** |
| Sell independently developed competing software | **YES** |
| Provide paid services using Block Engine | **YES** |
| Use Block Engine internally within a company | **YES** |
| Sell Block Engine itself | **NO** |
| Sell a Modified Engine as Development Technology | **NO** |
| Commercially provide Block Engine as Development Technology | **NO** |
| Commercially provide Block Engine Development Technology | **NO** |
| Commercially host or provide the engine remotely for development | **NO** |
| Charge for access to Block Engine or its development functionality | **NO** |
| Use a wrapper, shell, or fake Product to commercially provide the engine | **NO** |
| Rename or disguise the engine to commercially provide it | **NO** |
| Split the engine across components or services to circumvent the License | **NO** |

> **Important:** This summary is provided for convenience only. It does not grant, remove, expand, restrict, replace, supplement, or modify any rights or restrictions. **The Block Engine License is the controlling document and takes precedence over this summary in all circumstances.**