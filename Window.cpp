#include "Window.h"
#include <gdiplus.h>
#include <iostream>
#include <string>

HWND TextBox;

Window::Window()
	: m_hInstance(GetModuleHandle(nullptr)),
	inMenu(true)
{
	Gdiplus::GdiplusStartupInput gdiPlusStartupInput;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiPlusStartupInput, nullptr);

	const wchar_t* CLASS_NAME = L"Tic Tac Toe Class";
	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.lpfnWndProc = WindowProc; //Windows Procedure

	RegisterClass(&wndClass);

	DWORD style = WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	int width = 640;
	int height = 480;

	RECT rect;

	rect.left = 100;
	rect.top = 100;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(0, CLASS_NAME, L"Tic Tac Toe", style, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, m_hInstance, nullptr);
	ShowWindow(m_hWnd, SW_SHOW);
}

Window::~Window()
{
	Gdiplus::GdiplusShutdown(gdiplusToken);
	const wchar_t* CLASS_NAME = L"Tic Tac Toe Class";
	UnregisterClass(CLASS_NAME,m_hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};
	while(PeekMessage(&msg,nullptr,0u,0u,PM_REMOVE))
	{
		if(msg.message==WM_QUIT)
		{
			return false;
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

void Window::Draw()
{
	HDC wdc = GetWindowDC(m_hWnd);
	HFONT hFont1 = CreateFont(72, 0, 0, 0, 0, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, TEXT("Tic Tac Toe"));
	if (inMenu) {
		RECT rect;
		GetClientRect(m_hWnd, &rect);
		SetTextColor(wdc, 0xffffffff);
		SetBkMode(wdc, TRANSPARENT);
		rect.left = 0;
		rect.top = 100;
		SelectObject(wdc, hFont1);
		DrawText(wdc, L"Tic Tac Toe", -1, &rect, DT_SINGLELINE | DT_NOCLIP | DT_CENTER);

		Gdiplus::Graphics graphics(wdc);
		Gdiplus::Image image(L"image.png");
		graphics.DrawImage(&image, Gdiplus::PointF(200.0f, 100.0f));
	}
	ReleaseDC(m_hWnd,wdc);
	DeleteObject(hFont1);
}

void Window::DrawPlayField()
{

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		CreateWindow(TEXT("BUTTON"), TEXT("Join Game"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 400, 100, 20, hWnd, (HMENU)1, nullptr, nullptr);
		CreateWindow(TEXT("BUTTON"), TEXT("Create Game"), WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 370, 100, 20, hWnd, (HMENU)2, nullptr, nullptr);
		TextBox = CreateWindow(L"EDIT",L"Game Code",WS_BORDER|WS_CHILD|WS_VISIBLE,10,430,100,20,hWnd,nullptr,nullptr,nullptr);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case 1:
			int stat;
			char text[10];
			stat = GetWindowTextA(TextBox,&text[0], 10);
			std::cout << text << std::endl;
			std::cout << stat << std::endl;
			if (stat==0)
			{
				::MessageBox(hWnd, L"Error: Enter game code!", L"Error", MB_ICONERROR);
			}
			break;
		case 2:

			break;
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}
