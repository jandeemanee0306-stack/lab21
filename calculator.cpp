#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
HWND t1, t2;
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
    case WM_CREATE: {
      CreateWindow("STATIC", "Please input two numbers", WS_CHILD | WS_VISIBLE | SS_CENTER, 25, 10, 200, 20, hwnd, NULL, NULL, NULL);
		 t1 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 50, 40, 150, 25, hwnd, NULL, NULL, NULL);
		 t2 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 50, 70, 150, 25, hwnd, NULL, NULL, NULL);

		CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 50, 110, 30, 30, hwnd, (HMENU)1, NULL, NULL);
        CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 90, 110, 30, 30, hwnd, (HMENU)2, NULL, NULL);
        CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 130, 110, 30, 30, hwnd, (HMENU)3, NULL, NULL);
        CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 170, 110, 30, 30, hwnd, (HMENU)4, NULL, NULL);
		break;
    }
	case WM_COMMAND: {
            if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {
                char val1[20], val2[20], resStr[50];

                GetWindowText(t1, val1, 20);
                GetWindowText(t2, val2, 20);

                double n1 = atof(val1);
                double n2 = atof(val2);
                double result = 0;

                
                if (LOWORD(wParam) == 1) result = n1 + n2;
                if (LOWORD(wParam) == 2) result = n1 - n2;
                if (LOWORD(wParam) == 3) result = n1 * n2;
                if (LOWORD(wParam) == 4) {
                    if(n2 != 0) result = n1 / n2;
                    else {
                        MessageBox(hwnd, "Error: Divide by Zero", "Result", MB_OK | MB_ICONERROR);
                        return 0;
                    }
                }

                
                sprintf(resStr, "%f", result);
                MessageBox(hwnd, resStr, "Result", MB_OK);
            }
            break;
		}
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(10,200, 600));
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Calculator",WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
