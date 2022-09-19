#include <utilities.h>

RenderState render_state;
GlobalVars global_vars;

//COLORS
#define red 0xff5500

#include "renderer.cpp"

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    switch (uMsg)
    {
    case WM_CLOSE:

    case WM_DESTROY:
    {
        global_vars.window_running = false;
    }
    break;

    case WM_SIZE:
    {
        RECT rect;
        GetClientRect(hwnd, &rect);
        render_state.width = rect.right - rect.left;
        render_state.height = rect.bottom - rect.top;

        int size = render_state.width * render_state.height * sizeof(unsigned int);

        if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
        render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
        render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
        render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
        render_state.bitmap_info.bmiHeader.biPlanes = 1; 
        render_state.bitmap_info.bmiHeader.biBitCount = 32;
        render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;

    }
    break;

    default:
    {
        result = DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    }
    return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    //create window class
        // a window class is a set of behaviours that windows might have in common
    // like for eg. with buttons clicking on the button gives the same result across different windows
    // data that is unique to each window is called instance data
    WNDCLASSW window_class = {}; //changed from WNDCLASS
    window_class.style = CS_HREDRAW | CS_VREDRAW;       //draw horizontally and vertically 
    
    // Window classes are registered with the system at run time
    // to register them we fill in a WNDCLASS structure as below
    window_class.lpszClassName = L"Game Window Class";
    window_class.lpfnWndProc = window_callback;

    // pointer to a callback function called window procedure,
    // used by the window to send messages to us

    //Register class
    RegisterClass(&window_class);

    //create 
    HWND window = CreateWindow(window_class.lpszClassName, L"Game Window Name..", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
    HDC hdc = GetDC(window);


    while (global_vars.window_running)
    {
        //input
        MSG message;
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        //simulate
        clear_screen(red);
        //render_background();
        draw_rect(-2, 0, 8, 3, 0xff22);
        //render
        StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);
    }
}
