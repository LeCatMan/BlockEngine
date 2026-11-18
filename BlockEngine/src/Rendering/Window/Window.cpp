#include "Window.hpp"


/**
 *  returns Aspect ratio as a float like 1.78
 *  Examples:
 *  800 × 600 → 800 / 600 = 1.33
 *  1920 × 1080 → 1.78 (that’s 16:9)
 *  600 × 600 → 1.0 (a perfect square)
 */
float BlockWindow::Aspect()
{
    return Height > 0 ? (float)Width / (float)Height : 1.0f;
}


void BlockWindow::framebuffersizecallback(GLFWwindow *window, int WindowWidth, int WindowHeight)
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        if (Isloaded)
        {
            glfwMakeContextCurrent(window);
            //         x  y    width        height
            glViewport(0, 0, WindowWidth, WindowHeight);
        }
        else
        {
            warning("Cannot callback the frame buffer size because the window isn't initialized");
            return;
        }
    }
    else
    {
        warning("Cannot callback the frame buffer size because the engine isn't initialized");
        return;
    }
}


// Update the viewport to match the window size.
void FrameBufferSizeCallback(GLFWwindow *Window, int WindowWidth, int WindowHeight)
{
    BlockWindow *Self = (BlockWindow*)glfwGetWindowUserPointer(Window);
    if (Self)
    { 
        Self->framebuffersizecallback(Window, WindowWidth, WindowHeight);
    }
}


BlockResult BlockWindow::CreateWindow(int WindowWidth, int WindowHeight, const char *WindowTitle, int Exitkey, bool VSync, int ImageCount, GLFWimage *Image)
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        if (!Isloaded)
        {
            #pragma region load glad and glfw and make the window
            Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, Monitor, NULL);
            
            if (Window == NULL)
            {
                error("Failed to create GLFW window: %s", WindowTitle);
                return BLOCK_ERR_INIT_FAILED;
            }
            glfwMakeContextCurrent(Window);

            glfwSetWindowUserPointer(Window, this);

            Width = WindowWidth;
            Height = WindowHeight;

            if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                error("Failed to initialize GLAD");
                RenderingInitialized = BLOCK_SUCCESS_FALSE;
                CloseWindow();
                return BLOCK_ERR_INIT_FAILED;
            }
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            #pragma endregion

            #pragma region set the fps and vsync

            glfwSetFramebufferSizeCallback(Window, FrameBufferSizeCallback);
            
            Monitor = glfwGetPrimaryMonitor();

            if (Monitor == NULL)
            {
                error("Couldn't get the monitor");
                RenderingInitialized = BLOCK_SUCCESS_FALSE;
                return BLOCK_ERR_INIT_FAILED;
            }
            else
            {
                const GLFWvidmode *Mode = glfwGetVideoMode(Monitor);

                rendering("Monitor: %d Hz", Mode->refreshRate);
                rendering("Width Height : %i , %i",Mode->width, Mode->height);
                
                if (VSync)
                {
                    glfwSwapInterval(1);
                }
                else
                {
                    glfwSwapInterval(0);
                }
            }

            #pragma endregion
            
            glfwSetWindowIcon(Window, ImageCount, Image);
            
            InitializeInput(Window);
            ExitKey = Exitkey;

            rendering("Window initialized!");
            Isloaded = true;
            return BLOCK_SUCCESS_TRUE;
        }
        else
        {
            warning("Cannot create the window because the window is already create");
            return BLOCK_FAILURE;
        }
    }
    else
    {
        warning("Cannot create the window because the engine isn't initialized");
        return BLOCK_FAILURE;
    }
}


// Checks the close flag of the specified window.
BlockResult BlockWindow::WindowShouldClose()
{
    if (Isloaded)
    {
        return glfwWindowShouldClose(Window)
            ? BLOCK_SUCCESS_TRUE
            : BLOCK_SUCCESS_FALSE;
    }
    else
    {
        return BLOCK_FAILURE;
    }
}


// process rendering events.
void BlockWindow::UpdateWindow()
{
    glfwMakeContextCurrent(Window);
    glfwGetFramebufferSize(Window, &Width, &Height);
    UpdateAudio();
    UpdateInput(Window); 
    glfwSwapBuffers(Window); // Swaps the front and back buffers of the specified window.
    if (KeyEvent(ExitKey, BLOCK_PRESS))
    {
        glfwSetWindowShouldClose(Window, GLFW_TRUE);
    }
    if (WindowShouldClose())
    {
        CloseWindow();
    }
}


void BlockWindow::MakeCurrentWindowContext()
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        if (Isloaded)
        {
            glfwMakeContextCurrent(Window);
        }
        else
        {
            warning("Cannot change background color because the window is closed");
            return;
        }
    }
    else 
    {
        warning("Cannot close the window because the rendering engine is not Initialized");
        return ;
    }
}


BlockResult BlockWindow::SetBackgroundColor(Color color)
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        if (Isloaded)
        {
            glfwMakeContextCurrent(Window);
            glClearColor((color.r), (color.g), (color.b), (color.a));
            glClear(GL_COLOR_BUFFER_BIT);
            return BLOCK_SUCCESS_TRUE;
        }
        else
        {
            warning("Cannot change background color because the window is closed");
            return BLOCK_FAILURE;
        }
    }
    else
    {
        warning("Cannot change the background color because the rendering engine is not Initialized");
        return BLOCK_FAILURE;
    }
}


BlockResult BlockWindow::CloseWindow()
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        if (Isloaded)
        {
            Isloaded = false;
            glfwDestroyWindow(Window);
            Window = NULL;
            Monitor = NULL;
            Isloaded = false;
            rendering("Closed the window");
            return BLOCK_SUCCESS_TRUE;
        }
        else
        {
            warning("Cannot close the window because the window is already closed");
            return BLOCK_SUCCESS_FALSE;
        }
    }
    else 
    {
        warning("Cannot close the window because the rendering engine is not Initialized");
        return BLOCK_FAILURE;
    }
}


BlockWindow::~BlockWindow()
{
    if (RenderingInitialized == BLOCK_SUCCESS_TRUE)
    {
        if (Isloaded)
        {
            Isloaded = false;
            glfwDestroyWindow(Window);
            Window = NULL;
            Monitor = NULL;
            Isloaded = false;
            rendering("Closed the window");
            return;
        }
        else
        {
            return;
        }
    }
    else 
    {
        warning("Cannot close the window because the rendering engine is not Initialized");
        return;
    }
}


double GetTime()
{
    return glfwGetTime();
}




