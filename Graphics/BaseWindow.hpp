#pragma once
#include <Windows.h>
#include "../Util/MessageLogger.h"
#include "Graphics/WindowHandler.hpp"

namespace ws
{
template <class DERIVED_TYPE>
class BaseWindow : public WindowHandler
{
protected:
	WNDCLASSEX wcex_{};
	HWND hWnd_;
	int nCmdShow_;
	int width_;
	int height_;
	int position_x_;
	int position_y_;
	LPCWSTR class_name_;
	LPCWSTR tittle_;
public:
	
	BaseWindow():
		hWnd_(nullptr),
		nCmdShow_(0),
		width_(0),
		height_(0),
		position_x_(0),
		position_y_(0),
		class_name_(nullptr),
		tittle_(nullptr)
	{
		 
	}

	virtual ~BaseWindow()
	{
		if (hWnd_ != NULL)
		{
			UnregisterClass(class_name_, wcex_.hInstance);
			DestroyWindow(hWnd_);
		}
	}

	bool Initialize(
		_In_ HINSTANCE hInstance,
		_In_ int nCmdShow,
		_In_ LPCWSTR className)
	{
		nCmdShow_ = nCmdShow;
		class_name_ = className;
		ZeroMemory(&wcex_, sizeof(WNDCLASSEX));
		wcex_.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wcex_.lpfnWndProc = WindowProc;
		wcex_.cbClsExtra = 0;
		wcex_.cbWndExtra = 0;
		wcex_.hInstance = hInstance;
		wcex_.hIcon = LoadIcon(hInstance, IDI_WARNING);
		wcex_.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
		wcex_.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex_.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex_.lpszMenuName = NULL;
		wcex_.lpszClassName = class_name_;
		wcex_.cbSize = sizeof(WNDCLASSEX);
		
		if (!RegisterClassEx(&wcex_))
		{
			message_logger::warning(static_cast<HRESULT>(GetLastError()));
			return false;
		}
		return true;
	}

	bool Create(LPCWSTR tittle, const int width, const int height, const int position_x, const int position_y)
	{
		tittle_ = tittle;
		width_ = width;
		height_ = height;
		position_x_ = position_x;
		position_y_ = position_y;



		hWnd_ = CreateWindowEx(
			0,
			class_name_,
			tittle_,
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			position_x_, position_y_,
			width_, height_,
			NULL,
			NULL,
			wcex_.hInstance,
			this
		);

		if (!hWnd_)
		{
			message_logger::warning(GetLastError());
			return false;
		}
		
		return true;
	}
	
	void OpenWindow() const override
	{

		if (hWnd_ != NULL)
		{
			ShowWindow(hWnd_, nCmdShow_);
		}

		if (hWnd_ != NULL)
		{
			UpdateWindow(hWnd_);
		}
		
	}

	void CloseWindow() const override
	{
		if (hWnd_ != NULL)
		{
			UnregisterClass(class_name_, wcex_.hInstance);
			DestroyWindow(hWnd_);
		}
	}
	
	bool IsOpenAndProcessMessages()
	{
		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));

		if (PeekMessage(
			&msg, 
			hWnd_,
			0,
			0, 
			PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_NULL)
		{
			if (!IsWindow(hWnd_))
			{
				hWnd_ = NULL;
				UnregisterClass(L"class", wcex_.hInstance);
				return false;
			}
		}

		return true;
	}

	HWND GetWindow() const override
	{
		return hWnd_;
	}

	UINT GetWindowWidth() const override
	{
		return this->width_;
	}

	UINT GetWindowHeight() const override
	{
		return this->height_;
	}

	UINT GetWindowPositionX() const override
	{
		return this->position_x_;
	}
	UINT GetWindowPositionY() const override
	{
		return this->position_y_;
	}

	static LRESULT CALLBACK WindowProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
	{
		DERIVED_TYPE* pThis = NULL;

		if (uMsg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
			pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)pThis);
			pThis->hWnd_ = hWnd;
		}
		else
		{
			pThis = (DERIVED_TYPE*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		}
		if (pThis)
		{
			return pThis->HandleMessage(hWnd, uMsg, wParam, lParam);
		}
		else
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}

protected:
	virtual LRESULT CALLBACK HandleMessage(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam) = 0;
	
};
}