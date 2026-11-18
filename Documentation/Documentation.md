# Block Engine Cheat Sheet

A C++ engine for 2D graphics, audio, keyboard input and logging. It is built on GLFW (windows and input), glad (OpenGL 3.3 core), miniaudio (audio), stb_image (image loading) and glm (shape transforms).

## Contents

1. [Quick Start](#quick-start)
2. [Things to Know](#things-to-know)
3. [BlockResult](#blockresult)
4. [Engine](#engine)
5. [Rendering](#rendering): Color, Window, Shapes, Texture
6. [Audio](#audio)
7. [Input](#input)
8. [Logging](#logging)
9. [Math](#math)
10. [Examples](#examples)
11. [Advanced](#advanced)
12. [Known Issues](#known-issues)

---

## Quick Start

```cpp
#include <src/BlockEngine.hpp>

int main()
{
    InitializeBlockEngine(1.0f);

    {   // Everything is inside {} except ShutDownBlockEngine() so every object is destroyed automatically before shutdown.
        BlockWindow Window;
        Window.CreateWindow(800, 600, "Block Engine", BLOCK_KEY_ESCAPE, true, 0, NULL);
        Color BGColor = {255.0f, 255.0f, 160.0f, 255.0f};

        info("Entering Game Loop");
        while (!Window.WindowShouldClose())
        {
            Window.SetBackgroundColor(BGColor);   // clears the screen, so call it first every frame
            // draw things here
            Window.UpdateWindow();                // call it last every frame
        }
        info("Exited Game Loop");
    }

    ShutDownBlockEngine();
    return 0;
}
```

Include path: use `#include "../../BlockEngine/src/BlockEngine.hpp"` the way the Examples folder does, or `#include <src/BlockEngine.hpp>` if the `BlockEngine/` folder is on your include path.

---

## Things to Know

- Keep every engine object inside a `{}` scope, and call only `InitializeBlockEngine` and `ShutDownBlockEngine` outside it. Objects are destroyed in reverse order of declaration, so declare shapes, textures and sounds after the window.
- Window numbers in `Draw` start at 1. Window 1 is the first window you gave to `Create` or `Load...`.
- Colors take values from 0 to 255 and always need all four values (r, g, b, a). `Color()` with no arguments is magenta. A value outside 0 to 255 also gives magenta and logs an error.
- Rotation is in degrees, applied X, then Y, then Z.
- File paths (assets, shaders) are relative to the folder you run the program from. The `Logs/` folder is next to the executable (see [Logging](#logging)).
- Queries like `WindowShouldClose` return a `BlockResult`, not a bool. See [BlockResult](#blockresult).
- `KeyEvent` with `BLOCK_REPEAT` starts on the second frame of a hold. For "while held", check `BLOCK_PRESS` or `BLOCK_REPEAT`.
- For a texture, load the image first, then the mesh. The mesh load applies the wrap mode and border color to the texture that is bound at that moment.

---

## BlockResult

Most functions return a `BlockResult`.

| Value | Number | Meaning |
| :--- | :---: | :--- |
| `BLOCK_SUCCESS_TRUE` | 1 | Succeeded, result is TRUE |
| `BLOCK_SUCCESS_FALSE` | 0 | Succeeded, result is FALSE |
| `BLOCK_FAILURE` | -1 | General failure |
| `BLOCK_ERR_NULL_POINTER` | -2 | A null pointer was passed or found |
| `BLOCK_ERR_OUT_OF_MEMORY` | -3 | Out of memory |
| `BLOCK_ERR_FILE_IO` | -4 | File read or write failed |
| `BLOCK_ERR_INVALID_PARAM` | -5 | An invalid parameter was passed |
| `BLOCK_ERR_INIT_FAILED` | -6 | Initialization failed |

Failure is any negative value, so check with `Result < 0`:

```cpp
if (Window.CreateWindow(800, 600, "Game", BLOCK_KEY_ESCAPE, true, 0, NULL) < 0)
{
    error("Window failed");
}
```

Yes/no queries (`WindowShouldClose`, `IsSoundPlaying`, `IsSoundFinished`, `IsSoundLooping`) return TRUE (1), FALSE (0), or a negative value on failure. That is why `while (!Window.WindowShouldClose())` also stops the loop on an error, and why it stops once the window is closed.

Some calls return `BLOCK_SUCCESS_FALSE` when there was nothing to do, for example `CloseWindow` on a window that is already closed, or loading a texture that is already loaded.

`const char* BlockGetErrorString(BlockResult Result);` converts a result to text. See [Known Issues](#known-issues) for a bug in it.

---

## Engine

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult InitializeBlockEngine(float Volume);` | Starts the logger, rendering engine and audio engine, in that order, sets the master volume, and prints the current running path. | `InitializeBlockEngine(1.0f);` | Returns `BLOCK_ERR_INIT_FAILED` if any of them fails. Doesn't create a window. |
| ShutDown | `BlockResult ShutDownBlockEngine();` | Shuts down the rendering engine, audio engine and logger, in that order. | `ShutDownBlockEngine();` | Returns `BLOCK_FAILURE` at the first one that fails. Destroy windows, shapes, textures and sounds first (a `{}` scope does this). |

---

## Rendering

`BlockWindow`, `Shape2D`, `Triangle`, `Square`, `Texture2D` and `Audio` can't be copied or moved, and they clean up after themselves when destroyed. Their functions are methods, so call them on an object (`Window.CreateWindow(...)`). Alpha blending is on.

### Color

`Color(float r, float g, float b, float a)` takes values from 0 to 255 and stores them as 0 to 1 internally.

```cpp
Color BGColor = {255.0f, 255.0f, 160.0f, 255.0f};
Color Red(255.0f, 0.0f, 0.0f, 255.0f);
Color Default;   // magenta
```

A value outside the range gives magenta (255, 0, 255, 255) and logs an error. For a random channel use `rand() % 256`.

### Window

Methods of `BlockWindow`.

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult CreateWindow(int WindowWidth, int WindowHeight, const char *WindowTitle, int Exitkey, bool VSync, int ImageCount, GLFWimage *Image);` | Creates the window and sets up input for it. `Exitkey` closes the window when pressed, `VSync` turns vertical sync on or off, `ImageCount` and `Image` are the icon images. | `Window.CreateWindow(800, 600, "Block Engine", BLOCK_KEY_ESCAPE, true, 0, NULL);` | Pass `0, NULL` for no custom icon. Returns `BLOCK_FAILURE` if the window already exists or the engine isn't initialized, and `BLOCK_ERR_INIT_FAILED` if GLFW or GLAD fails. |
| ShutDown | `BlockResult CloseWindow();` | Closes the window. | `Window.CloseWindow();` | Also happens when the exit key is pressed and when the object is destroyed. |
| Get | `BlockResult WindowShouldClose();` | Checks whether the window should close. | `while (!Window.WindowShouldClose()) { }` | TRUE means close, FALSE means keep going, negative means failure (including a closed window). |
| Process | `void UpdateWindow();` | Ends the frame: updates the framebuffer size, audio and input, swaps the buffers, and closes the window if the exit key was pressed. | `Window.UpdateWindow();` | Call once per frame, last. Don't call it on a window that is already closed. |
| Set | `void MakeCurrentWindowContext();` | Makes this window the one OpenGL draws into. | `Window.MakeCurrentWindowContext();` | `SetBackgroundColor` and every `Draw` do this for you. |
| Set | `BlockResult SetBackgroundColor(Color color);` | Clears the window with this color. | `Window.SetBackgroundColor(Color(255.0f, 255.0f, 255.0f, 255.0f));` | Call every frame before drawing. Returns `BLOCK_FAILURE` if the window is closed. |
| Set | `void SetWindowPosition(int X, int Y);` | Moves the window on the screen. | `Window.SetWindowPosition(100, 100);` | |
| Set | `void SetWindowSize(int WindowWidth, int WindowHeight);` | Resizes the window. | `Window.SetWindowSize(1280, 720);` | |
| Set | `void SetWindowTitle(const char *Title);` | Changes the window title. | `Window.SetWindowTitle("New Title");` | |
| Set | `void SetWindowIcon(int ImageCount, GLFWimage *Image);` | Changes the window icon. | `Window.SetWindowIcon(1, &Icon);` | Same parameters as in `CreateWindow`. |
| Set | `void SetWindowOpacity(float Opacity);` | Sets how see-through the window is. | `Window.SetWindowOpacity(128.0f);` | 0 to 255, where 255 is fully opaque. Outside that range it logs an error and changes nothing. |
| Set | `void RestoreWindow();` | Restores a minimized or maximized window. | `Window.RestoreWindow();` | |
| Get | `void GetWindowSize(int *WindowWidth, int *WindowHeight);` | Writes the window size to the two pointers. | `Window.GetWindowSize(&W, &H);` | |
| Get | `void GetCursorPosition(double *X, double *Y);` | Writes the cursor position, relative to the window, to the two pointers. | `Window.GetCursorPosition(&X, &Y);` | Writes 0, 0 if the window isn't open. |
| Get | `const char *GetWindowTitle();` | Returns the window title. | `Window.GetWindowTitle();` | |
| Get | `float GetWindowOpacity();` | Returns the window opacity. | `Window.GetWindowOpacity();` | 0 to 255. |
| Get | `float Aspect();` | Returns the aspect ratio, width divided by height. | `float A = Window.Aspect();` | Returns 1.0 if the height is 0. Width and height are refreshed by `UpdateWindow`. |
| Show/Hide | `void ShowWindow();` | Shows a hidden window. | `Window.ShowWindow();` | |
| Show/Hide | `void HideWindow();` | Hides the window. | `Window.HideWindow();` | |

Public members: `ExitKey`, `Window` (the GLFW window, type `Blockwindow *`), `Monitor`, `Width` and `Height`.

`Blockwindow` (lowercase w) is an alias for `GLFWwindow`, and `BlockMonitor` is an alias for `GLFWmonitor`. `BlockWindow` (capital W) is the class.

The setters and getters above call GLFW directly, so call `CreateWindow` first and don't use them after `CloseWindow`.

`double GetTime()` returns the time in seconds, the same as `glfwGetTime()`.

### Shapes

`Triangle` and `Square` are ready-made shapes that use the built-in shaders, so they need no shader files. `Shape2D` is the base class for your own shapes.

A shape can be drawn in several windows. You give it an array of windows when you create it, and pick a window by number when you draw.

- `Blockwindow **Window` is an array of GLFW windows (the `Window` member of each `BlockWindow`) and `WindowCount` is how many there are. For one window, `&Window.Window` with a count of 1 works.
- Window numbers start at 1. A number outside 1 to `WindowCount` logs an error and draws nothing.
- `Position`, `Rotation` and `Scale` are `FloatVector3` (X, Y, Z). Rotation is in degrees.
- Sizes in the Load functions are in bytes (`sizeof`).

#### Triangle and Square

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult Create(Color color, Blockwindow **Window, int WindowCount, bool PerVertexColoring);` | Creates the shape for every window in the array. | See [Drawing a Triangle](#drawing-a-triangle). | `PerVertexColoring` true uses the colors stored in the vertices, false uses the single `color`. Returns `BLOCK_FAILURE` and logs an error if it fails. |
| Process | `void Draw(int WindowNumber, bool WireMode, Color color, FloatVector3 Position, FloatVector3 Rotation, FloatVector3 Scale);` | Draws the shape in one window. | See [Drawing a Triangle](#drawing-a-triangle). | `WindowNumber` starts at 1. `WireMode` true draws only the outline. `color` is used when `PerVertexColoring` is false. |
| ShutDown | `BlockResult Unload();` | Frees the shape's resources for every window. | `MyTriangle.Unload();` | Also happens when the shape is destroyed. |

#### Built-in vertex data

| Name | Layout per vertex | Floats | Use with |
| :--- | :---------------- | :----: | :------- |
| `TriangleVertices` | x y z | 9 | single color |
| `TriangleVerticesColor` | x y z r g b a (colors 0 to 1) | 21 | per-vertex color |
| `TriangleVerticesColorUV` | x y z r g b a u v | 27 | color and texture |
| `TriangleIndices` | 0, 1, 2 | 3 | triangle |
| `SquareVertices` | x y z | 12 | single color |
| `SquareVerticesUV` | x y z u v | 20 | textures |
| `SquareVerticesColor` | x y z r g b a | 28 | per-vertex color |
| `SquareVerticesColorUV` | x y z r g b a u v | 36 | color and texture |
| `SquareIndices` | 0, 1, 2 and 1, 3, 2 | 6 | square (two triangles) |
| `BasicTransform` | 4x4 identity matrix | 16 | identity transform |

The data array you pass must match `PerVertexColor`: false goes with 3 floats per vertex (x y z), true goes with 7 (x y z r g b a).

#### Shape2D

Use `Shape2D` directly when you want your own vertices or your own shaders. `Triangle` and `Square` hide these four functions.

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult LoadShape2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, size_t ShapeIndicesArraySize, bool PerVertexColor, Color color, Blockwindow **Window, int WindowCount);` | Loads a shape using shader files on disk. | See [LoadShape2D](#loadshape2d). | `ShapeIndicesArraySize` is the size of one index, `sizeof(TriangleIndices[0])`. The engine divides `ShapeIndicesSize` by it to get the index count. `PerVertexColor` true means 7 floats per vertex (x y z r g b a), false means 3 (x y z) and the single `color` is used. |
| Initialize | `BlockResult LoadEmbeddedShape2D(const char *VertexShaderSource, const char *FragmentShaderSource, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, size_t ShapeIndicesArraySize, bool PerVertexColor, Color color, Blockwindow **Window, int WindowCount);` | Same, but takes the shader source text from memory. | See [LoadEmbeddedShape2D](#loadembeddedshape2d). | |
| Process | `void DrawShape2D(int WindowNumber, bool WireMode, Color color, FloatVector3 Position, FloatVector3 Rotation, FloatVector3 Scale);` | Draws the shape in one window. | `MyShape.DrawShape2D(1, false, Color(255.0f, 255.0f, 255.0f, 255.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});` | Same arguments as `Triangle::Draw`. |
| ShutDown | `BlockResult UnloadShape2D();` | Frees the shape's resources for every window. | `MyShape.UnloadShape2D();` | Also happens when the shape is destroyed. |

Your own shaders should use these names:

| What | Name | Type |
| :--- | :--- | :--- |
| Vertex position | attribute location 0 | `vec3` |
| Vertex color | attribute location 1 | `vec4` (white when `PerVertexColor` is false) |
| Single color | uniform `color` | `vec4`, 0 to 1 |
| Transform | uniform `Transform` | `mat4` |

#### Embedded assets

Defined in `Assets/BlockEngine/GeneratedAssets/GeneratedAssets.hpp`, which `BlockEngine.hpp` already includes:

| Name | What it is |
| :--- | :--------- |
| `asset_BasicVertexShader_vert` | Vertex shader for a single color |
| `asset_BasicFragmentShader_frag` | Fragment shader for a single color |
| `asset_BasicPerVertexVertexShader_vert` | Vertex shader for per-vertex colors |
| `asset_BasicPerVertexFragmentShader_frag` | Fragment shader for per-vertex colors |
| `asset_BasicVertexTextureShader_vert` | Vertex shader for textures |
| `asset_BasicFragmentTextureShader_frag` | Fragment shader for textures |
| `asset_Brick_icon_png` | The brick icon image bytes |

Older code (`ExampleDump.cpp`) uses a longer name for the brick image, `BlockEngine_src_Assets_BlockEngine_Images_Block_Engine_Brick_icon_png`, with `#include "Assets/BlockEngine/GeneratedAssets/Images/asset_Brick_icon_png.h"`. `BlockEngine.cpp` uses `asset_Brick_icon_png` instead, so check which name your build generates.

### Texture

Methods of `Texture2D`. A texture has two parts, the image (`LoadTexture2D`) and the mesh it is drawn on (`LoadTextureMesh2D`). Load the image first, then the mesh, then call `Draw`.

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult LoadTexture2D(const char *ImagePath, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, bool RGBA);` | Loads an image file as a texture. `RGBA` true loads 4 channels, false loads 3 (RGB). | `MyTexture.LoadTexture2D("src/Assets/BlockEngine/Images/Block-Engine/Brick-icon.png", BLOCK_NEAREST, BLOCK_NEAREST, true);` | The two filters are `BLOCK_NEAREST` or `BLOCK_LINEAR`. The image is flipped vertically on load. Returns `BLOCK_SUCCESS_FALSE` if already loaded and `BLOCK_ERR_INIT_FAILED` if the file can't be read. |
| Initialize | `BlockResult LoadEmbeddedTexture2D(const char *ImageData, size_t ImageSize, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, bool RGBA);` | Loads a texture from image bytes embedded in the executable. | See [LoadEmbeddedTexture2D](#loadembeddedtexture2d). | `ImageSize` is in bytes. |
| Initialize | `BlockResult LoadTextureMesh2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor, BlockTextureFlags TextureBorder, Color TextureBorderColor, Color color, Blockwindow **Window, int WindowCount);` | Loads the mesh the texture is drawn on, using shader files on disk. | See [LoadTextureMesh2D](#loadtexturemesh2d). | `MeshIndicesArraySize` is the size of one index, `sizeof(SquareIndices[0])`. `TextureBorder` is the wrap mode (see Texture Flags). `TextureBorderColor` is only used with `BLOCK_TEXTURE_CLAMP_TO_BORDER`. `color` is the starting value of the shader's `color` uniform. Use `SquareVerticesUV` for the vertices. |
| Initialize | `BlockResult LoadEmbeddedTextureMesh2D(const char *VertexShaderSource, const char *FragmentShaderSource, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor, BlockTextureFlags TextureBorder, Color TextureBorderColor, Color color, Blockwindow **Window, int WindowCount);` | Same, but takes the shader source text from memory. | See [LoadTextureMesh2D](#loadtexturemesh2d). | Use `asset_BasicVertexTextureShader_vert` and `asset_BasicFragmentTextureShader_frag`. |
| Process | `void Draw(int WindowNumber, bool WireMode, Color color, FloatVector3 Position, FloatVector3 Rotation, FloatVector3 Scale);` | Draws the texture on its mesh in one window. | `MyTexture.Draw(1, false, Color(255.0f, 255.0f, 255.0f, 255.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});` | `WindowNumber` starts at 1. `color` goes to the shader's `color` uniform; `BlockEngine.cpp` cycles it to tint the brick. |
| ShutDown | `BlockResult UnloadTexture2D();` | Frees the image. | `MyTexture.UnloadTexture2D();` | Also happens when the object is destroyed. Returns `BLOCK_SUCCESS_FALSE` if already unloaded. |
| ShutDown | `BlockResult UnloadTextureMesh2D();` | Frees the mesh. | `MyTexture.UnloadTextureMesh2D();` | Also happens when the object is destroyed. |

Texture shaders use position at attribute 0 (`vec3`), color at attribute 1 (`vec4`, only if `PerVertexColor` is true) and UV at attribute 2 (`vec2`). Uniforms are `Transform` (`mat4`), `Texture` (`sampler2D`) and `color` (`vec4`). With `PerVertexColor` true, use `SquareVerticesColorUV` (9 floats per vertex).

The image is uploaded into whichever window's OpenGL context is current when you call `LoadTexture2D`. Windows don't share contexts, so with several windows, as far as the source shows, a texture only draws reliably in that one.

#### Texture Flags

| Flag | Description |
| :--- | :---------- |
| `BLOCK_TEXTURE_REPEAT` | The default. Repeats the image. |
| `BLOCK_TEXTURE_REPEAT_MIRRORED` | Repeats the image, mirrored each time. |
| `BLOCK_TEXTURE_CLAMP_TO_EDGE` | Coordinates above 1 stretch the edge pixels. |
| `BLOCK_TEXTURE_CLAMP_TO_BORDER` | Coordinates outside 0 to 1 show `TextureBorderColor`. |
| `BLOCK_NEAREST` | Pixelated filtering. |
| `BLOCK_LINEAR` | Smooth filtering. |

Use the four `REPEAT` and `CLAMP` flags for `TextureBorder`, and `BLOCK_NEAREST` or `BLOCK_LINEAR` for the two filters. (`BLOCK_TEXTURE_MIN_FILTER` and `BLOCK_TEXTURE_MAG_FILTER` also exist, but they are OpenGL parameter names, not values.)

---

## Audio

`BLOCK_DEFAULT_VOLUME` and `BLOCK_DEFAULT_PITCH` are both `1.0f`.

### Global audio functions

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult InitializeAudioEngine(float volume);` | Starts the audio engine and sets the master volume. | `InitializeAudioEngine(1.0f);` | Called by `InitializeBlockEngine`. |
| Process | `void UpdateAudio();` | Frees finished copies made by `PlayOverlappingSound`. | `UpdateAudio();` | Called by `UpdateWindow` every frame. |
| ShutDown | `BlockResult AudioShutDown();` | Shuts down the audio engine and frees any copies still playing. | `AudioShutDown();` | Called by `ShutDownBlockEngine`. |

### Audio class

Each `Audio` object holds one sound. Use an array for several sounds (`Audio Sounds[2];`). Every method except the loaders returns `BLOCK_FAILURE` if no sound is loaded.

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult LoadSound(const char *Path, BlockSoundFlags Flag);` | Loads a sound from a file. | `MySound.LoadSound("Click.wav", BLOCK_SOUND_FLAG_DECODE);` | Use `DECODE` for short effects and `STREAM` for long music. Combine flags with `\|`. Fails if the object already holds a sound. |
| Initialize | `BlockResult LoadEmbeddedSound(const unsigned char *Data, size_t dataSize);` | Loads a sound from data embedded in the executable. | `MySound.LoadEmbeddedSound(SoundData, sizeof(SoundData));` | `dataSize` is in bytes. `Data` must stay valid while the sound is loaded. Sound flags don't apply. Returns `BLOCK_ERR_NULL_POINTER` for null data or size 0. |
| ShutDown | `BlockResult UnloadSound();` | Unloads the sound. | `MySound.UnloadSound();` | Also happens when the object is destroyed. Destroy `Audio` objects before `ShutDownBlockEngine`. You can load a new sound afterwards. |
| Process | `BlockResult PlaySound();` | Plays the sound from the start, restarting it if it is playing. | `MySound.PlaySound();` | |
| Process | `BlockResult StopSound();` | Stops the sound where it is. | `MySound.StopSound();` | `StartSound` continues from here. |
| Process | `BlockResult StartSound();` | Starts the sound from where it is, without rewinding. | `MySound.StartSound();` | |
| Process | `BlockResult PlayOverlappingSound();` | Plays a new copy of the sound so it can overlap itself. | `MySound.PlayOverlappingSound();` | Use it with sounds loaded from a file. Finished copies are cleaned up for you by `UpdateAudio`. |
| Process | `BlockResult Fade(float volumeBeg, float volumeEnd, int fadeLengthInMilliseconds, int absoluteGlobalTimeInMilliseconds);` | Fades the volume from `volumeBeg` to `volumeEnd` over `fadeLengthInMilliseconds`. | `MySound.Fade(0.0f, 1.0f, 2000, 0);` | The last argument is when the fade starts, on the audio engine's clock. `0` starts it right away. |
| Get | `BlockResult IsSoundFinished();` | Checks whether the sound reached its end. | `MySound.IsSoundFinished();` | TRUE, FALSE, or negative on failure. |
| Get | `BlockResult IsSoundPlaying();` | Checks whether the sound is playing. | `MySound.IsSoundPlaying();` | TRUE, FALSE, or negative on failure. |
| Get | `BlockResult IsSoundLooping();` | Checks whether the sound is set to loop. | `MySound.IsSoundLooping();` | TRUE, FALSE, or negative on failure. |
| Set | `BlockResult SetSoundPosition(FloatVector3 XYZ);` | Sets the sound's position (2D audio uses only X and Y). | `MySound.SetSoundPosition({1.0f, 0.0f, 0.0f});` | No effect with `BLOCK_SOUND_FLAG_NO_SPATIAL`. |
| Get | `FloatVector3 GetSoundPosition();` | Returns the sound's position. | `FloatVector3 Position = MySound.GetSoundPosition();` | Returns (0, 0, 0) if no sound is loaded. |
| Set | `BlockResult SetLooping(bool State);` | Turns looping on or off. | `MySound.SetLooping(true);` | Same as loading with `BLOCK_SOUND_FLAG_LOOPING`, but you can change it any time. |

### Sound flags

Combine flags with `|`:

```cpp
MySound.LoadSound("Music.ogg", BLOCK_SOUND_FLAG_STREAM | BLOCK_SOUND_FLAG_LOOPING);
```

| Flag | Description |
| :--- | :---------- |
| `BLOCK_SOUND_FLAG_STREAM` | Reads the file in small chunks while playing. Saves RAM, best for long music. |
| `BLOCK_SOUND_FLAG_DECODE` | Loads the whole sound into RAM first. Plays instantly, best for sound effects. |
| `BLOCK_SOUND_FLAG_ASYNC` | Loads the sound on another thread so the game doesn't stutter. |
| `BLOCK_SOUND_FLAG_WAIT_INIT` | Waits for background loading to finish. Use with `ASYNC`. |
| `BLOCK_SOUND_FLAG_UNKNOWN_LENGTH` | For generated audio whose length isn't known. |
| `BLOCK_SOUND_FLAG_LOOPING` | Restarts the sound when it ends. |
| `BLOCK_SOUND_FLAG_NO_ATTACHMENT` | Loads the sound without connecting it to the speakers yet. |
| `BLOCK_SOUND_FLAG_NO_PITCH` | Disables pitch changes to save CPU. |
| `BLOCK_SOUND_FLAG_NO_SPATIAL` | Disables 3D positioning and panning. Best for UI sounds and music. |

---

## Input

Keyboard only for now. `CreateWindow` sets up input and `UpdateWindow` updates it every frame, so you only need `KeyEvent`.

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Get | `bool KeyEvent(int key, int event);` | Returns true if `key` has the given `event` this frame. | `KeyEvent(BLOCK_KEY_F, BLOCK_PRESS);` | Keys outside the valid range (including `BLOCK_KEY_UNKNOWN`) return false. |
| Initialize | `void InitializeInput(Blockwindow *Window);` | Sets up input for a GLFW window. | `InitializeInput(Window.Window);` | `CreateWindow` already calls it. |
| Process | `void UpdateInput(Blockwindow *Window);` | Polls events and reads the keyboard state for a GLFW window. | `UpdateInput(Window.Window);` | `UpdateWindow` already calls it. |

| Event | True when | Fires |
| :---- | :-------- | :---- |
| `BLOCK_PRESS` | key is down now and was up last frame | once, on the first frame |
| `BLOCK_RELEASE` | key is up now and was down last frame | once, on release |
| `BLOCK_REPEAT` | key is down now and was down last frame | every frame while held, from the second frame |

For "while held", use `KeyEvent(key, BLOCK_PRESS) || KeyEvent(key, BLOCK_REPEAT)`.

The key state is shared by all windows. With more than one window, `KeyEvent` reflects the window that was updated last.

### Input constants

Names are GLFW's with `BLOCK_` instead of `GLFW_` (`GLFW_KEY_F` becomes `BLOCK_KEY_F`).

| Group | Names |
| :---- | :---- |
| Events | `BLOCK_RELEASE` (0), `BLOCK_PRESS` (1), `BLOCK_REPEAT` (2) |
| Keys | `BLOCK_KEY_A` to `BLOCK_KEY_Z`, `BLOCK_KEY_0` to `BLOCK_KEY_9`, `BLOCK_KEY_F1` to `BLOCK_KEY_F25`, `BLOCK_KEY_KP_0` to `BLOCK_KEY_KP_9`, `BLOCK_KEY_KP_DECIMAL`, `_DIVIDE`, `_MULTIPLY`, `_SUBTRACT`, `_ADD`, `_ENTER`, `_EQUAL`, `BLOCK_KEY_COMMA`, `_PERIOD`, `_SLASH`, `_SEMICOLON`, `_EQUAL`, `_MINUS`, `_APOSTROPHE`, `_LEFT_BRACKET`, `_RIGHT_BRACKET`, `_BACKSLASH`, `_GRAVE_ACCENT`, `BLOCK_KEY_WORLD_1`, `_WORLD_2`, `BLOCK_KEY_SPACE`, `BLOCK_KEY_ENTER`, `BLOCK_KEY_ESCAPE`, `BLOCK_KEY_TAB`, `BLOCK_KEY_BACKSPACE`, `BLOCK_KEY_INSERT`, `BLOCK_KEY_DELETE`, `BLOCK_KEY_HOME`, `BLOCK_KEY_END`, `BLOCK_KEY_PAGE_UP`, `BLOCK_KEY_PAGE_DOWN`, `BLOCK_KEY_UP`, `BLOCK_KEY_DOWN`, `BLOCK_KEY_LEFT`, `BLOCK_KEY_RIGHT`, `BLOCK_KEY_CAPS_LOCK`, `BLOCK_KEY_SCROLL_LOCK`, `BLOCK_KEY_NUM_LOCK`, `BLOCK_KEY_PRINT_SCREEN`, `BLOCK_KEY_PAUSE`, `BLOCK_KEY_LEFT_SHIFT`, `BLOCK_KEY_LEFT_CONTROL`, `BLOCK_KEY_LEFT_ALT`, `BLOCK_KEY_LEFT_SUPER` (and the `RIGHT_` versions), `BLOCK_KEY_MENU`, `BLOCK_KEY_UNKNOWN` (-1), `BLOCK_KEY_LAST` (same as `BLOCK_KEY_MENU`) |
| Modifier flags | `BLOCK_MOD_SHIFT`, `BLOCK_MOD_CONTROL`, `BLOCK_MOD_ALT`, `BLOCK_MOD_SUPER`, `BLOCK_MOD_CAPS_LOCK`, `BLOCK_MOD_NUM_LOCK` |
| Mouse buttons | `BLOCK_MOUSE_BUTTON_1` to `BLOCK_MOUSE_BUTTON_8`, `BLOCK_MOUSE_BUTTON_LEFT`, `BLOCK_MOUSE_BUTTON_RIGHT`, `BLOCK_MOUSE_BUTTON_MIDDLE`, `BLOCK_MOUSE_BUTTON_LAST` |
| Joysticks | `BLOCK_JOYSTICK_1` to `BLOCK_JOYSTICK_16`, `BLOCK_JOYSTICK_LAST` |
| Gamepad buttons | `BLOCK_GAMEPAD_BUTTON_A`, `_B`, `_X`, `_Y`, `_LEFT_BUMPER`, `_RIGHT_BUMPER`, `_BACK`, `_START`, `_GUIDE`, `_LEFT_THUMB`, `_RIGHT_THUMB`, `_DPAD_UP`, `_DPAD_RIGHT`, `_DPAD_DOWN`, `_DPAD_LEFT`, `_LAST`, plus the aliases `_CROSS`, `_CIRCLE`, `_SQUARE`, `_TRIANGLE` |
| Gamepad axes | `BLOCK_GAMEPAD_AXIS_LEFT_X`, `_LEFT_Y`, `_RIGHT_X`, `_RIGHT_Y`, `_LEFT_TRIGGER`, `_RIGHT_TRIGGER`, `_LAST` |
| Joystick hats | `BLOCK_HAT_CENTERED`, `BLOCK_HAT_UP`, `BLOCK_HAT_RIGHT`, `BLOCK_HAT_DOWN`, `BLOCK_HAT_LEFT`, `BLOCK_HAT_RIGHT_UP`, `BLOCK_HAT_RIGHT_DOWN`, `BLOCK_HAT_LEFT_UP`, `BLOCK_HAT_LEFT_DOWN` |

Only `KeyEvent` uses these so far. The mouse, joystick and gamepad constants exist, but there are no functions for them yet. Use `Window.GetCursorPosition` for the cursor.

---

## Logging

The logger prints to the console and to a file in a `Logs/` folder next to the executable (`Log-001.txt`, then `Log-002.txt` on the next run). The executable's folder is found through `/proc/self/exe` on Linux and the module path on Windows; on other systems it falls back to the current folder. Each line has the time, type, file and line number.

These are macros, not functions. The message is a `printf`-style format string.

```cpp
info("Loaded %d sounds", Count);
```

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Process | `error(Message, ...)` | Logs an error. | `error("Something failed");` | |
| Process | `warning(Message, ...)` | Logs a warning. | `warning("Careful");` | |
| Process | `info(Message, ...)` | Logs general information. | `info("Started");` | |
| Process | `debug(Message, ...)` | Logs debugging information. | `debug("x = %d", x);` | |
| Process | `trace(Message, ...)` | Logs tracing information. | `trace("Entered function");` | |
| Process | `audio(Message, ...)` | Logs an audio message. | `audio("Loaded sound");` | |
| Process | `rendering(Message, ...)` | Logs a rendering message. | `rendering("Created window");` | |

`InitializeBlockEngine` starts the logger and `ShutDownBlockEngine` stops it. The logger must be running before you use the macros.

Things to watch for:

- Write a literal `%` as `%%`.
- Arguments are evaluated twice, so don't pass expressions with side effects like `i++`.
- Don't pass a variable named `size` or `Buffer`, because the macro uses those names.
- The macro names are common words, so you can't name your own variables `info`, `error`, `debug` and so on.

---

## Math

Included with the engine. These are plain structs; build them with braces: `FloatVector3{0.0f, 0.0f, 0.0f}`.

| Type | Members |
| :--- | :------ |
| `FloatVector2`, `IntVector2` | `x`, `y` |
| `FloatVector3`, `IntVector3` | `x`, `y`, `z` |
| `FloatVector4`, `IntVector4` | `x`, `y`, `z`, `w` |
| `FloatRectangle`, `IntRectangle` | `x`, `y`, `width`, `height` |

| Function | What it does |
| :------- | :----------- |
| `IntVector2 CenterOfScreen(IntVector2 screen)` | The center of a screen size (half of each value). |
| `HalfIntVector2/3/4(v)`, `HalfFloatVector2/3/4(v)` | Divides every component by 2. |
| `int HalfInt(int)`, `float HalfFloat(float)` | Half of a number. |
| `double Sum(int count, ...)` | Adds `count` numbers. The numbers must be `double`s: `Sum(3, 1.0, 2.0, 3.0)`. |

---

## Examples

### Drawing a Triangle

```cpp
BlockWindow Window;
Window.CreateWindow(800, 600, "Block Engine", BLOCK_KEY_ESCAPE, true, 0, NULL);

// An array of GLFW windows. Add more entries to draw in several windows.
Blockwindow *Windows[] = { Window.Window };

Triangle MyTriangle;
MyTriangle.Create(Color(255.0f, 255.0f, 255.0f, 255.0f), Windows, 1, true);

// In the game loop, after SetBackgroundColor:
MyTriangle.Draw(
    1,                                      // window number (1 is Windows[0])
    false,                                  // WireMode
    Color(255.0f, 255.0f, 255.0f, 255.0f),  // used when per-vertex coloring is off
    {0.0f, 0.0f, 0.0f},                     // Position
    {0.0f, 0.0f, 0.0f},                     // Rotation (degrees)
    {1.0f, 1.0f, 1.0f});                    // Scale
```

### Spinning a shape

```cpp
MySquare.Draw(1, false, Color(0.0f, 100.0f, 0.0f, 255.0f),
    {0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, (float)glfwGetTime() * 100.0f},   // degrees around Z
    {1.0f, 1.0f, 1.0f});
```

### Toggling something with a key

```cpp
bool DrawBrick = true;
// in the loop:
if (KeyEvent(BLOCK_KEY_Q, BLOCK_PRESS)) { DrawBrick = !DrawBrick; }
if (DrawBrick)
{
    Brick.Draw(1, false, Color(255.0f, 255.0f, 255.0f, 255.0f),
        {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
}
```

### Moving a shape while a key is held

```cpp
float X = 0.0f;
// in the loop:
if (KeyEvent(BLOCK_KEY_RIGHT, BLOCK_PRESS) || KeyEvent(BLOCK_KEY_RIGHT, BLOCK_REPEAT)) { X += 0.01f; }
MyTriangle.Draw(1, false, Color(255.0f, 255.0f, 255.0f, 255.0f), {X, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
```

The step is per frame, so with VSync off it moves faster on a faster machine.

### Drawing in two windows

```cpp
BlockWindow Windows[2];
Windows[0].CreateWindow(800, 600, "1", BLOCK_KEY_1, true, 0, NULL);
Windows[1].CreateWindow(800, 600, "2", BLOCK_KEY_2, true, 0, NULL);

Blockwindow *WindowPointers[2] = { Windows[0].Window, Windows[1].Window };

Triangle MyTriangle;
MyTriangle.Create(Color(0.0f, 0.0f, 0.0f, 255.0f), WindowPointers, 2, false);

while (!Windows[0].WindowShouldClose() || !Windows[1].WindowShouldClose())
{
    if (!Windows[0].WindowShouldClose())
    {
        Windows[0].SetBackgroundColor(BGColor);
        MyTriangle.Draw(1, false, Color(0.0f, 255.0f, 0.0f, 255.0f), {0, 0, 0}, {0, 0, 0}, {1, 1, 1});
        Windows[0].UpdateWindow();
    }
    if (!Windows[1].WindowShouldClose())
    {
        Windows[1].SetBackgroundColor(BGColor);
        MyTriangle.Draw(2, false, Color(0.0f, 255.0f, 0.0f, 255.0f), {0, 0, 0}, {0, 0, 0}, {1, 1, 1});
        Windows[1].UpdateWindow();
    }
}
```

Each window needs its own exit key (here 1 and 2), and each `UpdateWindow` is guarded so it only runs on windows that are still open.

### LoadShape2D

```cpp
Shape2D MyShape;
MyShape.LoadShape2D(
    "src/Assets/BlockEngine/Shaders/BasicPerVertexVertexShader.vert",
    "src/Assets/BlockEngine/Shaders/BasicPerVertexFragmentShader.frag",
    TriangleVerticesColor, sizeof(TriangleVerticesColor),
    TriangleIndices, sizeof(TriangleIndices), sizeof(TriangleIndices[0]),
    true, Color(255.0f, 255.0f, 255.0f, 255.0f),
    Windows, 1);

// In the game loop:
MyShape.DrawShape2D(
    1, false, Color(255.0f, 255.0f, 255.0f, 255.0f),
    {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
```

### LoadEmbeddedShape2D

```cpp
// The embedded shaders are the asset_* variables listed under Embedded assets.
MyShape.LoadEmbeddedShape2D(
    asset_BasicPerVertexVertexShader_vert,
    asset_BasicPerVertexFragmentShader_frag,
    TriangleVerticesColor, sizeof(TriangleVerticesColor),
    TriangleIndices, sizeof(TriangleIndices), sizeof(TriangleIndices[0]),
    true, Color(255.0f, 255.0f, 255.0f, 255.0f),
    Windows, 1);
```

### LoadEmbeddedTexture2D

```cpp
Texture2D MyTexture;
MyTexture.LoadEmbeddedTexture2D(
    (const char *)asset_Brick_icon_png, sizeof(asset_Brick_icon_png),
    BLOCK_LINEAR, BLOCK_LINEAR, true);

// Then the mesh, using the embedded texture shaders:
MyTexture.LoadEmbeddedTextureMesh2D(
    asset_BasicVertexTextureShader_vert,
    asset_BasicFragmentTextureShader_frag,
    SquareVerticesUV, sizeof(SquareVerticesUV),
    SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]),
    false,
    BLOCK_TEXTURE_REPEAT, Color(255.0f, 0.0f, 255.0f, 255.0f),
    Color(255.0f, 255.0f, 255.0f, 255.0f),
    &Window.Window, 1);
```

### LoadTextureMesh2D

```cpp
// Image first, then the mesh.
Texture2D Brick;
Brick.LoadTexture2D("src/Assets/BlockEngine/Images/Block-Engine/Brick-icon.png", BLOCK_NEAREST, BLOCK_NEAREST, true);

Brick.LoadTextureMesh2D(
    "src/Assets/BlockEngine/Shaders/BasicVertexTextureShader.vert",
    "src/Assets/BlockEngine/Shaders/BasicFragmentTextureShader.frag",
    SquareVerticesUV, sizeof(SquareVerticesUV),
    SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]),
    false,                                      // PerVertexColor
    BLOCK_TEXTURE_REPEAT,                       // wrap mode
    Color(255.0f, 0.0f, 255.0f, 255.0f),        // border color (only for CLAMP_TO_BORDER)
    Color(255.0f, 255.0f, 255.0f, 255.0f),      // starting value of the color uniform
    &Window.Window, 1);

// In the game loop:
Brick.Draw(1, false, Color(255.0f, 255.0f, 255.0f, 255.0f),
    {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f});
```

### Playing a sound

```cpp
Audio Click;
Click.LoadSound("Click.wav", BLOCK_SOUND_FLAG_DECODE | BLOCK_SOUND_FLAG_NO_SPATIAL);
Click.PlaySound();                 // restarts if already playing

// Overlapping hits, like gunshots:
if (KeyEvent(BLOCK_KEY_F, BLOCK_PRESS)) { Click.PlayOverlappingSound(); }
```

### Music that loops

```cpp
Audio Music;
Music.LoadSound("Music.ogg", BLOCK_SOUND_FLAG_STREAM | BLOCK_SOUND_FLAG_LOOPING | BLOCK_SOUND_FLAG_NO_SPATIAL);
Music.PlaySound();
```

---

## Advanced

These are used inside the engine. You normally don't call them, but they are available.

### Essential (OpenGL helpers)

Free functions that wrap the OpenGL calls used by shapes and textures. Each one checks for OpenGL errors and returns a `BlockResult`.

| Function | What it does |
| :------- | :----------- |
| `CreateVAO(unsigned int *VAO)` / `DestroyVAO(unsigned int VAO)` | Creates (and binds) or deletes a vertex array object. |
| `CreateVBO(const float *Vertices, size_t VerticesSize, unsigned int *VBO, bool PerVertexColor, bool texture, bool RGBA, BlockTextureFlags TextureBorder = BLOCK_TEXTURE_REPEAT, Color TextureBorderColor = Color(255, 0, 255, 255))` / `DestroyVBO(unsigned int VBO)` | Creates or deletes a vertex buffer and sets up the vertex attributes. A VAO must be bound first. The vertex layout is position (3 floats), then color (4 floats if `RGBA`, otherwise 3, only if `PerVertexColor`), then UV (2 floats, if `texture`). Keep `RGBA` true, because the built-in vertex data has 4 color floats. When `texture` is true, `TextureBorder` and `TextureBorderColor` are applied to the currently bound texture. |
| `CreateEBO(const unsigned int *Indices, size_t Size, unsigned int *EBO)` / `DestroyEBO(unsigned int EBO)` | Creates or deletes an index buffer. `Size` is in bytes. |
| `ShaderProgram(unsigned int *Shader, unsigned int VertexShader, unsigned int FragmentShader)` / `DestroyShader(unsigned int Shader)` | Links two compiled shaders into a program (and deletes the two shaders), or deletes a program. |

### Shader2D

Compiles shaders for `Shape2D` and `Texture2D`. Create it empty, then call one of these. The compiled shader IDs are private, and only `Shape2D` and `Texture2D` can read them, so you normally don't use `Shader2D` yourself.

| Function | What it does |
| :------- | :----------- |
| `BlockResult CreateShader2D(const char *VertexShaderSourcePath, const char *FragmentShaderSourcePath)` | Reads two shader files and compiles them. Returns `BLOCK_ERR_INVALID_PARAM` if a file can't be read and `BLOCK_FAILURE` if a shader doesn't compile. |
| `BlockResult CreateEmbeddedShader2D(const char *VertexShaderSource, const char *FragmentShaderSource)` | Compiles shader source text already in memory. Returns `BLOCK_ERR_INVALID_PARAM` for a null source. |

### Utilities

| Function | What it does |
| :------- | :----------- |
| `void GetCurrentRunningPath()` | Stores the current working directory in `CurrentRunningPath` and prints it. Called by `InitializeBlockEngine`. |
| `char *GetFileText(const char *FileName)` | Reads a text file and returns it as a string, or `NULL` if it can't be read. Free the result with `free()`. |
| `const char *BlockGetErrorString(BlockResult Result)` | Converts a `BlockResult` to text. |
| `void DetectOS()` | Prints the operating system (Windows, macOS, Linux or Unknown). Include `DetectOS.hpp` to use it. |

### Logger functions

The logging macros call these functions, which take an already formatted message plus a file name and line: `Error`, `Trace`, `Info`, `Warning`, `Debug`, `AudioLog`, `Rendering`. `InitializeLogger()` and `ShutDownLogger()` start and stop the logger.
