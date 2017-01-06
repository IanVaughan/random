#pragma hdrstop
#include <condefs.h>

const bool FULLSCREEN = false;
//zero for the first, primary display, 1+ for others
const unsigned int MONITOR = 0;

//---------------------------------------------------------------------------
#pragma argsused

USELIB("..\..\..\..\mssdk\lib\Borland\dxguid.lib");
USELIB("..\..\..\..\mssdk\lib\Borland\ddraw.lib");
USELIB("..\..\..\..\mssdk\lib\Borland\d3dim.lib");
USEUNIT("X.cpp");
USEUNIT("..\DXError.cpp");
USEUNIT("XUtil.cpp");

#include "X.h"

//---------------------------------------------------------------------------

bool Init(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, bool fullScreen);
LRESULT CALLBACK WindowProc(HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam);

X* x = NULL;
//---------------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR lpCmdLine, int nCmdShow)
{
    //init the window
    if(!Init(hInstance, lpCmdLine, nCmdShow, FULLSCREEN))
    {
        PostQuitMessage(0);
    }

    // Now we're ready to recieve and process Windows messages.
    BOOL bGotMsg;
    MSG  msg;
    PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);
	
    while( WM_QUIT != msg.message  )
    {
        bGotMsg = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);
        if( bGotMsg )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            x->Update(FULLSCREEN);
            
            Sleep(1);
/*            if(!x->Update(FULLSCREEN))
                PostQuitMessage(0);
*/		}
    }

    delete x;

	// return final message
    return msg.wParam;
}
//---------------------------------------------------------------------------

bool Init(HINSTANCE hInstance, LPSTR /*lpCmdLine*/, int /*nCmdShow*/, bool fullScreen)
{
    WNDCLASS                    wc;

    // Set up and register window class
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = (WNDPROC) WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(DWORD);
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "X";
    if (!RegisterClass(&wc))
        return false;

    // Get dimensions of display
    int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Create a window and display
	HWND hWnd;

    //switch for fullscreen/windowed mode
    DWORD styleFlags = WS_VISIBLE;
    if(fullScreen)
                    //show no window, else it shows a white window on primary monitor
        styleFlags = NULL;//|= WS_POPUP;
    else
    {
        styleFlags |= WS_OVERLAPPEDWINDOW;
        ScreenWidth = 300;
        ScreenHeight = 200;
    }

    hWnd = CreateWindow("X",						    	// class
                        "3DEngine",							// caption
						styleFlags,	            			// style
						0,									// left
						0,									// top
						ScreenWidth,						// width
						ScreenHeight,						// height
                        NULL,								// parent window
                        NULL,								// menu
                        hInstance,							// instance
                        NULL);								// parms
    if (!hWnd)
        return false;

//    ShowWindow(hWnd, nCmdShow); //not need cos of WS_POPUP
    UpdateWindow(hWnd);

    //start the 3d engine
    x = new X();

    //this temp block selects the monitor to create the device on by reading the const at top
    //block will be replaced with a selection dialog once implemented into MapEditor

    Screen* ScreenList = x->GetDisplayDevices();
    Screen* nextScr = ScreenList;

    //if fullscreen dont need to test other monitors, cos its in windowed mode
    if(fullScreen)
    {
        //So, were in fullscreen mode, now search list of display devices for the
        // one that we want to use, its a DEFINE at the top for the mo
        int loopCounter = 0;
        // get searchin till we have looped enougth for the counter to match the desired device count
        // (and of course as long as its not NULL
        while(loopCounter < MONITOR && nextScr)
        {
            loopCounter++;
            nextScr = nextScr->pScreenNext;
        }
        if(nextScr == NULL)
        {
            MessageBox(NULL, "The display device you choose is not valid, the system will now exit.","No Device", MB_OK|MB_ICONERROR);
            return false;
        }
    }

    x->InitGraphics(hWnd, fullScreen, &nextScr->guid);


	// return success to caller
	return true;
}
//---------------------------------------------------------------------------

//------ Function to Initialize DirectDraw and the Application ------//
LRESULT CALLBACK WindowProc(HWND hWnd, unsigned uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
		case WM_DESTROY:
//			Cleanup();
            PostQuitMessage(0);
            break;

	    case WM_KEYDOWN:

	        switch (wParam) {

			case VK_UP:
				break;

			case VK_DOWN:
				break;

			case VK_RIGHT:
				break;

			case VK_LEFT:
				break;
			}
			break;

	    case WM_KEYUP:

	        switch (wParam) {

			case VK_UP:
			case VK_DOWN:
				break;

			case VK_RIGHT:
			case VK_LEFT:
				break;

			case VK_ESCAPE:

				// exit the program on escape
				DestroyWindow(hWnd);
				break;

			}
			break;

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

	return 0L;
}
//---------------------------------------------------------------------------


