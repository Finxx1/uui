// SPDX-License-Identifier: Zlib
// This file is released under the Zlib/libpng license. See COPYING.txt in the root directory.
// UUI: Universal User Interface
// 2023-10-27 - Created
// Abstract - Windows-specific behavior (Eg. windowing)

#include <uui.h>

#include <Windows.h>

static LPTSTR uui__utf8_to_tchar(char* str) {
#ifndef UNICODE
	return str;
#else
	int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	LPTSTR r = malloc(len * sizeof(TCHAR));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, r, len);
	return r;
#endif
}

static bool uui__bool(BOOL b) {
	return b != FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE: {
			SetWindowLongPtr(hWnd, GWL_STYLE, 0);
			break;
		}
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

uui_window uui_make_window(void) {
	HINSTANCE hInstance = GetModuleHandle(NULL);
	
	WNDCLASS wc = {0};
	wc.style = CS_OWNDC; // For OpenGL rendering
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = _T("uui");
	wc.hbrBackground = (HBRUSH)0;
	RegisterClass(&wc);
	
	return CreateWindowW(_T("uui"), _T(""), 0, CW_USEDEFAULT, CW_USEDEFAULT, 1, 1, NULL, NULL, hInstance, NULL);
}


bool uui_title_window(uui_window window, char* txt) {
	LPTSTR text = uui__utf8_to_tchar(txt);
	
	bool r = uui__bool(SetWindowText(text));
	
	free(text);
	
	return r;
}

bool uui_position_window(uui_window window, int x, int y) {
	return uui__bool(SetWindowPos(window, HWND_NOTOPMOST, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER));
}

bool uui_size_window(uui_window window, int w, int h) {
	return uui__bool(SetWindowPos(window, HWND_NOTOPMOST, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER));
}

bool uui_show_window(uui_window window) {
	return uui__bool(ShowWindow(window, SW_SHOW));
}

bool uui_hide_window(uui_window window) {
	return uui__bool(window, SW_HIDE);
}

bool uui_make_topmost_window(uui_window window) {
	return uui__bool(SetWindowPos(window, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE));
}

bool uui_make_bottommost_window(uui_window window) {
	return uui__bool(SetWindowPos(window, HWND_BOTTOMMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE));
}

bool uui_hide_console(void) {
	return uui__bool(FreeConsole());
}

bool uui_show_console(void) {
	return uui__bool(FreeConsole());
}

void uui_run(uui_window window) {
	MSG msg;
	while (GetMessage(&msg, window, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}