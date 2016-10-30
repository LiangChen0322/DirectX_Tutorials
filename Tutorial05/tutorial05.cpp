#include <windows.h>
#include <windowsx.h>

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
							UINT message,
							WPARAM wParam,
							LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine,
				   int nCmdShow)
{
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style  = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	RECT wr = {0, 0, 500, 400};		// set the size, but not the position
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);		// adjust the size

	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
						  L"WindowClass1",		// Name of the window class
						  L"First Windowed Program",	// title of the window
						  WS_OVERLAPPEDWINDOW,
						  300,					// x-position of the window
						  300,					// y-position of the window
						  wr.right - wr.left,	// width of the window
						  wr.bottom - wr.top,	// height of the window
						  NULL,					// we have no parent window, NULL
						  NULL,					// we aren't using menus, NULL
						  hInstance,			// application handle
						  NULL);				// used with multiple windows, NULL

	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// enter the main loop:

	// this struct holds Windows event messages
	MSG msg = {0};

	// Enter the infinite message loop
	while (true) {
		// Check to see if anny messages are waiting in the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			// translate keystroke messages int the right format
			TranslateMessage(&msg);

			// Send the message to the WindowProc function
			DispatchMessage(&msg);

			// Check to see if it's time to quit
			if (msg.message == WM_QUIT)
				break;
		} else {
			// Run game code here
			// ...
			// ...
		}
	}

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		case WM_DESTROY: {
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc (hWnd, message, wParam, lParam);
}
