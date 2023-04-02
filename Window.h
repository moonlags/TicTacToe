#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessages();
	void Draw();
	void DrawPlayField();
private:
	ULONG_PTR gdiplusToken;
	HINSTANCE m_hInstance;
	bool inMenu;
	HWND m_hWnd;
};

