# Block Engine Cheat Sheet

## Typical Lifecycle

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
            Window.SetBackgroundColor(BGColor);
            Window.UpdateWindow();
        }
        info("Exited Game Loop");
    }

    ShutDownBlockEngine();
    return 0;
}
```

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

Failure is any negative value, so check with `Result < 0`.

Boolean style queries (`WindowShouldClose`, `IsSoundPlaying`, ...) also return a `BlockResult`: TRUE (1), FALSE (0), or a negative value on failure. That is why `while (!Window.WindowShouldClose())` also leaves the loop on an error.

`const char* BlockGetErrorString(BlockResult Result);` converts a result to text (used by the logger).

---

## Engine

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult InitializeBlockEngine(float Volume);` | Initializes the logger, rendering engine and audio engine, and sets the master volume. | `InitializeBlockEngine(1.0f);` | Doesn't create a window. Doesn't call `InitializeInput`, which is separate. |
| ShutDown | `BlockResult ShutDownBlockEngine();` | Shuts down the rendering engine, audio engine and logger, in that order. | `ShutDownBlockEngine();` | Doesn't close windows. Objects like `BlockWindow` and `Audio` must be destroyed first (a `{}` scope does this). |

---

## Rendering

`BlockWindow`, `Shape2D`, `Shader2D`, `Texture2D` and `Audio` can't be copied or moved, and they clean up after themselves in their destructors. Their functions below are methods, so call them on an object (`Window.CreateWindow(...)`).

### Rendering Engine

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult InitializeRenderingEngine();` | Initializes the rendering engine. | `InitializeRenderingEngine();` | Called by `InitializeBlockEngine`, so you normally don't call it yourself. Doesn't set up input. |
| ShutDown | `BlockResult ShutdownRenderingEngine();` | Shuts down the rendering engine. | `ShutdownRenderingEngine();` | Called by `ShutDownBlockEngine`. Spelled `Shutdown` in the header, rename to `ShutDown` to match the rest. |

### Color

`Color(float r, float g, float b, float a)` takes values from **0 to 255** and stores them as 0 to 1 internally. There is no default constructor, so always give all four values.

```cpp
Color BGColor = {255.0f, 255.0f, 160.0f, 255.0f};
```

### Window

Methods of `BlockWindow`.

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult CreateWindow(int WindowWidth, int WindowHeight, const char *WindowTitle, int Exitkey, bool VSync, int ImageCount, GLFWimage *Image);` | Creates the window. `Exitkey` closes it when pressed, `VSync` toggles vertical sync, `ImageCount` is the number of icon images, and `Image` is an array of them at different resolutions. | `Window.CreateWindow(800, 600, "Block Engine", BLOCK_KEY_ESCAPE, true, 0, NULL);` | Pass `0, NULL` for no custom icon. Doesn't call `InitializeInput`. |
| ShutDown | `BlockResult CloseWindow();` | Closes the window. | `Window.CloseWindow();` | Also happens automatically when `UpdateWindow` sees the window should close, and when the `BlockWindow` is destroyed. |
| Get | `BlockResult WindowShouldClose();` | Checks whether the window should close (for example, the exit key was pressed). | `while (!Window.WindowShouldClose()) { }` | TRUE means close, FALSE means keep going, negative means failure. See BlockResult. |
| Process | `void UpdateWindow();` | Per-frame update, called once at the end of every frame. Makes the window's context current, calls `UpdateAudio` and `UpdateInput`, swaps the buffers, and closes the window when the exit key is pressed. | `Window.UpdateWindow();` | You don't need to call `UpdateAudio` or `UpdateInput` yourself. |
| Set | `void MakeCurrentWindowContext();` | Makes this window's OpenGL context the current one. | `Window.MakeCurrentWindowContext();` | `UpdateWindow` and `SetBackgroundColor` already do this. Only needed for your own OpenGL calls or with more than one window. |
| Set | `BlockResult SetBackgroundColor(Color color);` | Clears the window with this color. | `Window.SetBackgroundColor(Color(255.0f, 255.0f, 255.0f, 255.0f));` | Call it every frame before drawing, because it clears the screen. Channels are 0 to 255. Returns `BLOCK_FAILURE` if the window is closed or the rendering engine isn't initialized. |

Public members: `ExitKey`, `Window` (a `Blockwindow *`, which is a GLFW window) and `Monitor` (a `BlockMonitor *`). Careful: `Blockwindow` (lowercase *w*) is an alias for `GLFWwindow`, while `BlockWindow` is the class.

### Shape

Methods of `Shape2D`. `Triangle` and `Square` are only test objects for it and are not fully implemented. `Shape3D` is an empty placeholder for now.

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult LoadShape2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, BlockWindow *Window, bool PerVertexColor, Color color);` | Loads a 2D shape using shader files on disk. | See [LoadShape2D](#loadshape2d). | Sizes are in bytes (`sizeof`). `PerVertexColor` true means the vertices carry their own colors, false means the single `color` is used. |
| Initialize | `BlockResult LoadEmbeddedShape2D(const char *VertexShaderSource, const char *FragmentShaderSource, const float *Vertices, size_t VerticesSize, const unsigned int *ShapeIndices, size_t ShapeIndicesSize, BlockWindow *Window, bool PerVertexColor, Color color);` | Same as `LoadShape2D`, but takes the vertex and fragment shader source text from memory instead of file paths. | See [LoadEmbeddedShape2D](#loadembeddedshape2d). | Sizes are in bytes (`sizeof`). No shaders are embedded in the project yet, so the example is only an illustration. |
| Process | `void DrawShape2D(size_t ShapeIndicesSize);` | Draws the shape. | `MyShape.DrawShape2D(sizeof(TriangleIndices) / sizeof(TriangleIndices[0]));` | Despite the name, the argument is an index **count**, unlike the Load functions, where it is bytes. |
| ShutDown | `BlockResult UnloadShape2D();` | Frees the shape's resources. | `MyShape.UnloadShape2D();` | Also happens automatically when the shape is destroyed. |
| Initialize | `Triangle(Color color, BlockWindow *Window);` | Test object: loads a triangle that uses per-vertex colors. | `Triangle MyTriangle(Color(255.0f, 0.0f, 0.0f, 255.0f), &Window);` | Derives from `Shape2D`. |
| Process | `void DrawTriangle();` | Draws the triangle. | `MyTriangle.DrawTriangle();` | - |
| Initialize | `Square(Color color, BlockWindow *Window);` | Test object: loads a square in a single color. | `Square MySquare(Color(0.0f, 255.0f, 0.0f, 255.0f), &Window);` | Derives from `Shape2D`. |
| Process | `void DrawSquare();` | Draws the square. | `MySquare.DrawSquare();` | - |

### Texture

Methods of `Texture2D`.

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult LoadTexture2D(const char *ImagePath, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, BlockTextureFlags Border, bool RGBA);` | Loads an image file as a texture. `RGBA` says whether the image uses RGBA or RGB. | `MyTexture.LoadTexture2D("src/Assets/BlockEngine/Images/Block-Engine/Brick-icon.png", BLOCK_NEAREST, BLOCK_NEAREST, BLOCK_TEXTURE_REPEAT, true);` | The filters are `BLOCK_NEAREST` or `BLOCK_LINEAR`. `Border` is the wrap mode. See Texture Flags. |
| Initialize | `BlockResult LoadEmbeddedTexture2D(const char *ImageData, size_t ImageSize, BlockTextureFlags MinifyFilter, BlockTextureFlags MagnifyingFilter, BlockTextureFlags Border, bool RGBA);` | Loads a texture from image data embedded in the executable. | See [LoadEmbeddedTexture2D](#loadembeddedtexture2d). | `ImageSize` is in bytes. |
| Initialize | `BlockResult LoadTextureMesh2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor);` | Loads the mesh the texture is drawn on, using shader files on disk. | See [LoadTextureMesh2D](#loadtexturemesh2d). | `MeshIndicesArraySize` is the size of one index (`sizeof(SquareIndices[0])`). |
| Initialize | `BlockResult LoadEmbeddedTextureMesh2D(const char *VertexShaderPath, const char *FragmentShaderPath, const float *Vertices, size_t VerticesSize, const unsigned int *MeshIndices, size_t MeshIndicesSize, size_t MeshIndicesArraySize, bool PerVertexColor);` | Same as `LoadTextureMesh2D`, but with shader source text from memory. | TODO | The header names the shader parameters `...Path` even though they are source text. |
| Process | `void DrawTexture2D();` | Draws the texture on its mesh. | `MyTexture.DrawTexture2D();` | Load both the texture and its mesh first (confirm). |
| ShutDown | `BlockResult UnloadTexture2D();` | Frees the texture. | `MyTexture.UnloadTexture2D();` | - |
| ShutDown | `BlockResult UnloadTextureMesh2D();` | Frees the mesh. | `MyTexture.UnloadTextureMesh2D();` | - |

#### Texture Flags

| Flag | Description |
| :--- | :--- |
| `BLOCK_TEXTURE_REPEAT` | The default. Repeats the texture image. |
| `BLOCK_TEXTURE_REPEAT_MIRRORED` | Like repeat, but mirrors the image with each repeat. |
| `BLOCK_TEXTURE_CLAMP_TO_EDGE` | Clamps coordinates to 0 to 1. Higher coordinates stretch the edge pixels. |
| `BLOCK_TEXTURE_CLAMP_TO_BORDER` | Coordinates outside 0 to 1 get a user-specified border color. |
| `BLOCK_NEAREST` | Nearest-neighbor filtering (pixelated). |
| `BLOCK_LINEAR` | Linear filtering (smooth). |
| `BLOCK_TEXTURE_MIN_FILTER`, `BLOCK_TEXTURE_MAG_FILTER` | OpenGL parameter names, not values. Use `BLOCK_NEAREST` or `BLOCK_LINEAR` for the filter arguments (confirm). |

### Shader

Methods of `Shader2D`. It is a friend of `Shape2D` and `Texture2D`, which use it to build their shaders, so you normally don't call it yourself (confirm).

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult CreateShader2D(const char *VertexShaderSourcePath, const char *FragmentShaderSourcePath);` | Reads the vertex and fragment shader files and compiles them. | `MyShader.CreateShader2D(VertexShaderPath, FragmentShaderPath);` | Returns `BLOCK_ERR_INVALID_PARAM` if a path can't be read. |
| Initialize | `BlockResult CreateEmbeddedShader2D(const char *VertexShaderSource, const char *FragmentShaderSource);` | Compiles vertex and fragment shader source text that is already in memory. | `MyShader.CreateEmbeddedShader2D(VertexShaderSource, FragmentShaderSource);` | - |

### Essential

Low-level OpenGL helpers (free functions). `Shape2D` and `Texture2D` use them internally.

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `void CreateVAO(unsigned int *VAO);` | Creates a vertex array object and writes its id to `*VAO`. | `CreateVAO(&VAO);` | - |
| ShutDown | `void DestroyVAO(unsigned int VAO);` | Deletes the vertex array object. | `DestroyVAO(VAO);` | - |
| Initialize | `void CreateVBO(const float *Vertices, size_t VerticesSize, unsigned int *VBO, bool PerVertexColor, bool texture, size_t Stride, Color BorderColor, bool RGBA);` | Creates a vertex buffer object from `Vertices` and writes its id to `*VBO`. `PerVertexColor` and `texture` describe the vertex layout. | `CreateVBO(Vertices, sizeof(Vertices), &VBO, true, false, 0, Color(0.0f, 0.0f, 0.0f, 255.0f), false);` | `Stride`: pass 0 to calculate it automatically. `BorderColor` is the color beyond the texture's area. `RGBA` says whether the image uses RGBA or RGB. |
| ShutDown | `void DestroyVBO(unsigned int VBO);` | Deletes the vertex buffer object. | `DestroyVBO(VBO);` | - |
| Initialize | `void CreateEBO(const unsigned int *Indices, size_t Size, unsigned int *EBO);` | Creates an element buffer object from `Indices` and writes its id to `*EBO`. | `CreateEBO(Indices, sizeof(Indices), &EBO);` | `Size` is in bytes (confirm). |
| ShutDown | `void DestroyEBO(unsigned int EBO);` | Deletes the element buffer object. | `DestroyEBO(EBO);` | - |
| Initialize | `void ShaderProgram(unsigned int *Shader, unsigned int VertexShader, unsigned int FragmentShader);` | Links a compiled vertex shader and fragment shader into a shader program and writes its id to `*Shader`. | `ShaderProgram(&Shader, VertexShader, FragmentShader);` | Takes compiled shader ids, not paths or source. |
| ShutDown | `void DestroyShader(unsigned int Shader);` | Deletes the shader program. | `DestroyShader(Shader);` | - |

---

## Audio

`BLOCK_DEFAULT_VOLUME` and `BLOCK_DEFAULT_PITCH` are both `1.0f`.

### Global Audio Functions

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult InitializeAudioEngine(float volume);` | Initializes the audio engine and sets the master volume. | `InitializeAudioEngine(1.0f);` | Called by `InitializeBlockEngine`. |
| Process | `void UpdateAudio();` | Frees the finished copies made by `PlayOverlappingSound`. | `UpdateAudio();` | Called every frame by `UpdateWindow`, so you normally don't call it yourself. |
| ShutDown | `BlockResult AudioShutdown();` | Shuts down the audio engine and frees any overlapping sound copies still alive. | `AudioShutdown();` | Called by `ShutDownBlockEngine`. Returns `BLOCK_FAILURE` if the engine isn't initialized. The name doesn't follow the `ShutDown...` pattern, consider `ShutDownAudioEngine`. |

### Audio Class

Methods of `Audio`. Each `Audio` object holds one sound at a time. Every method except the loaders returns `BLOCK_FAILURE` (and logs a warning) if no sound is loaded.

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult LoadSound(const char *Path, BlockSoundFlags Flag);` | Loads a sound from a file. | `MySound.LoadSound("Click.wav", BLOCK_SOUND_FLAG_DECODE);` | Use `DECODE` for short sound effects and `STREAM` for long music. Flags can be combined, see Sound Flags. Fails if this object already has a sound or the audio engine isn't initialized. |
| Initialize | `BlockResult LoadEmbeddedSound(const unsigned char *Data, size_t dataSize);` | Loads a sound from audio data embedded in the executable. | `MySound.LoadEmbeddedSound(SoundData, sizeof(SoundData));` | `dataSize` is in bytes. `Data` must stay valid while the sound is loaded, because it is read in place and not copied. No `Flag` parameter, so the sound flags don't apply. Returns `BLOCK_ERR_NULL_POINTER` for null or empty data. |
| ShutDown | `BlockResult UnloadSound();` | Unloads the sound and frees its resources. | `MySound.UnloadSound();` | Also happens when the `Audio` object is destroyed. The audio engine must still be initialized, so destroy `Audio` objects before `ShutDownBlockEngine`. |
| Process | `BlockResult PlaySound();` | Plays the sound from the beginning, restarting it if it is already playing. | `MySound.PlaySound();` | Use `StartSound` to continue instead of restarting. |
| Process | `BlockResult StopSound();` | Stops the sound where it is. | `MySound.StopSound();` | `StartSound` continues from this point. |
| Process | `BlockResult StartSound();` | Starts the sound from where it is, without rewinding. | `MySound.StartSound();` | Continues after `StopSound`. Use `PlaySound` to start from the beginning. |
| Process | `BlockResult PlayOverlappingSound();` | Plays a copy of the sound, so it can overlap with itself. | `MySound.PlayOverlappingSound();` | Finished copies are freed by `UpdateAudio`. Probably fails for embedded sounds and sounds loaded with `BLOCK_SOUND_FLAG_STREAM`, because miniaudio can only copy fully loaded file sounds (confirm). |
| Process | `BlockResult Fade(float volumeBeg, float volumeEnd, int fadeLengthInMilliseconds, int absoluteGlobalTimeInMilliseconds);` | Fades the volume from `volumeBeg` to `volumeEnd` over `fadeLengthInMilliseconds`, starting at `absoluteGlobalTimeInMilliseconds` (an `int`, in milliseconds). | `MySound.Fade(0.0f, 1.0f, 2000, 0);` | The start time is passed straight to miniaudio's `ma_sound_set_fade_start_in_milliseconds`, which treats it as a time on the audio engine's clock (confirm that 0 starts the fade right away). |
| Get | `BlockResult IsSoundFinished();` | Checks whether playback has reached the end of the sound. | `MySound.IsSoundFinished();` | TRUE / FALSE / negative on failure. See BlockResult. |
| Get | `BlockResult IsSoundPlaying();` | Checks whether the sound is currently playing. | `MySound.IsSoundPlaying();` | TRUE / FALSE / negative on failure. |
| Get | `BlockResult IsSoundLooping();` | Checks whether the sound is set to loop. | `MySound.IsSoundLooping();` | TRUE / FALSE / negative on failure. |
| Set | `BlockResult SetSoundPosition(FloatVector3 XYZ);` | Sets the sound's position. Works for 2D and 3D audio (2D uses only X and Y). | `MySound.SetSoundPosition({1.0f, 0.0f, 0.0f});` | No effect if the sound was loaded with `BLOCK_SOUND_FLAG_NO_SPATIAL`. |
| Get | `FloatVector3 GetSoundPosition();` | Returns the sound's position. Works for 2D and 3D audio (2D uses only X and Y). | `FloatVector3 Position = MySound.GetSoundPosition();` | Returns (0, 0, 0) if no sound is loaded. |
| Set | `BlockResult SetLooping(bool State);` | Turns looping on or off. | `MySound.SetLooping(true);` | Same effect as loading with `BLOCK_SOUND_FLAG_LOOPING`, but can change at runtime. |

### Sound Flags

Combine flags with `|`:

```cpp
MySound.LoadSound("Music.ogg", BLOCK_SOUND_FLAG_STREAM | BLOCK_SOUND_FLAG_LOOPING);
```

| Flag | Description |
| :--- | :--- |
| `BLOCK_SOUND_FLAG_STREAM` | Reads the file in small chunks during playback. Saves RAM, best for long music tracks. |
| `BLOCK_SOUND_FLAG_DECODE` | Decompresses the whole sound into RAM at load time. Instant playback with no CPU delay, best for sound effects. |
| `BLOCK_SOUND_FLAG_ASYNC` | Loads the sound in the background on another thread so the main loop doesn't stutter. |
| `BLOCK_SOUND_FLAG_WAIT_INIT` | Waits until background loading completes. Use with `ASYNC` to wait before playing. |
| `BLOCK_SOUND_FLAG_UNKNOWN_LENGTH` | For dynamic or generated audio where the total length isn't known ahead of time. |
| `BLOCK_SOUND_FLAG_LOOPING` | Restarts playback from the beginning when it reaches the end. |
| `BLOCK_SOUND_FLAG_NO_ATTACHMENT` | Loads the sound without connecting it to the speakers yet (for manual channel routing). |
| `BLOCK_SOUND_FLAG_NO_PITCH` | Disables pitch changes to save CPU. |
| `BLOCK_SOUND_FLAG_NO_SPATIAL` | Disables 3D positioning, distance fade and stereo panning. Best for UI clicks or background music. |

---

## Input

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `void InitializeInput(BlockWindow *Window);` | Sets up GLFW input polling for the window. | `InitializeInput(&Window);` | Separate from `CreateWindow`. TODO: is it required for the exit key? The lifecycle example doesn't call it. |
| Process | `void UpdateInput(BlockWindow *Window);` | Updates the input state for the window. | `UpdateInput(&Window);` | Called by `UpdateWindow`, so you normally don't call it yourself. |
| Get | `bool KeyEvent(int key, int event);` | Returns true if `key` has the given `event`. | `KeyEvent(BLOCK_KEY_F, BLOCK_PRESS);` | Key constants are GLFW's names with `BLOCK_` instead of `GLFW_` (`GLFW_KEY_F` is `BLOCK_KEY_F`). Events: `BLOCK_PRESS`, `BLOCK_RELEASE`, `BLOCK_REPEAT` (confirm). |

---

## Debugger

### Logger

These are macros, not functions: they can't be used as an expression and return nothing. `Message` is a `printf`-style format string, so extra arguments are allowed.

```cpp
info("Loaded %d sounds", Count);
```

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Initialize | `BlockResult InitializeLogger();` | Initializes the logging system. | `InitializeLogger();` | Must be called before using the logging macros. |
| ShutDown | `BlockResult ShutDownLogger();` | Shuts down the logging system. | `ShutDownLogger();` | Call when logging is no longer needed. |
| Process | `error(Message, ...)` | Logs an error message. | `error("Hello World!");` | Automatically captures the time, source file and line number. |
| Process | `trace(Message, ...)` | Logs tracing information. | `trace("Hello World!");` | Automatically captures the time, source file and line number. |
| Process | `info(Message, ...)` | Logs general information. | `info("Hello World!");` | Automatically captures the time, source file and line number. |
| Process | `warning(Message, ...)` | Logs a warning message. | `warning("Hello World!");` | Automatically captures the time, source file and line number. |
| Process | `debug(Message, ...)` | Logs debugging information. | `debug("Hello World!");` | Automatically captures the time, source file and line number. |
| Process | `audio(Message, ...)` | Logs an audio-related message. | `audio("Hello World!");` | Automatically captures the time, source file and line number. |
| Process | `rendering(Message, ...)` | Logs a rendering-related message. | `rendering("Hello World!");` | Automatically captures the time, source file and line number. |
| Process | `special(Message, ...)` | Logs a special message. | `special("Hello World!");` | Automatically captures the time, source file and line number. |

Gotchas:

- A literal `%` in the message must be written `%%`.
- Arguments are evaluated twice (once to measure, once to format), so don't pass expressions with side effects like `i++`.
- Don't pass a variable named `size` or `Buffer` as an argument. The macro declares locals with those names, so your argument would read the macro's variable instead.

### Utilities

| Category | Function | Description | Example | Note |
| :------: | :------- | :---------- | :------ | :--: |
| Get | `void GetCurrentRunningPath();` | Stores the current working directory in `RunningPath` (confirm). | `GetCurrentRunningPath();` | Called by `InitializeBlockEngine`. |
| Get | `char *GetFileText(const char *FileName);` | Reads a text file and returns its contents. | `char *Text = GetFileText("File.txt");` | The caller must free the returned text with `delete[]` (see `CreateShader2D`). |

---

## Examples

Long calls moved out of the tables.

### LoadShape2D

```cpp
Shape2D MyShape;
MyShape.LoadShape2D(
    "src/Assets/BlockEngine/Shaders/BasicPerVertexVertexShader.vert",
    "src/Assets/BlockEngine/Shaders/BasicPerVertexFragmentShader.frag",
    TriangleVerticesColor, sizeof(TriangleVerticesColor),
    TriangleIndices, sizeof(TriangleIndices),
    &Window, true, Color(255.0f, 255.0f, 255.0f, 255.0f));

// In the game loop:
MyShape.DrawShape2D(sizeof(TriangleIndices) / sizeof(TriangleIndices[0]));
```

### LoadEmbeddedShape2D

```cpp
// VertexShaderSource / FragmentShaderSource are variables holding the GLSL source text.
// No shaders are embedded in the project yet, so this is only an illustration.
MyShape.LoadEmbeddedShape2D(
    VertexShaderSource,
    FragmentShaderSource,
    TriangleVerticesColor, sizeof(TriangleVerticesColor),
    TriangleIndices, sizeof(TriangleIndices),
    &Window, true, Color(255.0f, 255.0f, 255.0f, 255.0f));
```

### LoadEmbeddedTexture2D

```cpp
Texture2D MyTexture;
MyTexture.LoadEmbeddedTexture2D(
    (const char *)BlockEngine_src_Assets_BlockEngine_Images_Block_Engine_Brick_icon_png,
    sizeof(BlockEngine_src_Assets_BlockEngine_Images_Block_Engine_Brick_icon_png),
    BLOCK_LINEAR, BLOCK_LINEAR, BLOCK_TEXTURE_REPEAT, true);
```

### LoadTextureMesh2D

```cpp
MyTexture.LoadTextureMesh2D(
    "src/Assets/BlockEngine/Shaders/BasicVertexTextureShader.vert",
    "src/Assets/BlockEngine/Shaders/BasicFragmentTextureShader.frag",
    SquareVerticesUV, sizeof(SquareVerticesUV),
    SquareIndices, sizeof(SquareIndices), sizeof(SquareIndices[0]),
    false);
```

### Playing a sound

```cpp
Audio Click;
Click.LoadSound("Click.wav", BLOCK_SOUND_FLAG_DECODE | BLOCK_SOUND_FLAG_NO_SPATIAL);
Click.PlaySound();
```

---

## Design Notes

- Boolean style queries (`WindowShouldClose`, `IsSound...`) intentionally return `BlockResult`. See the BlockResult section.
- `UpdateWindow` drives `UpdateAudio` and `UpdateInput`, so a normal game loop only calls `UpdateWindow`.