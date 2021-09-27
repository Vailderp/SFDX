#pragma once

#include "Graphics/BaseWindow.hpp"
#include "Graphics/EventListener.h"
#include <DirectXTK/Mouse.h>
#include <DirectXTK/Keyboard.h>

namespace ws
{
class MainWindow : public BaseWindow<MainWindow>
{
public:
	MainWindow() = default;

	MainWindow(EventListener* eventListener) :
		eventListener_(eventListener)
	{

	}

	void SetEventListener(EventListener* eventListener)
	{
		eventListener_ = eventListener;
	}
	
	LRESULT CALLBACK HandleMessage(
		_In_ HWND hWnd,
		_In_ UINT uMsg,
		_In_ WPARAM wParam, 
		_In_ LPARAM lParam
	) override
	{
		switch (uMsg)
		{
		case WM_CREATE:
			if (eventListener_ != nullptr)
			{
				eventListener_->OnCreateWindow(this);
			}
			break;
			
		case WM_CLOSE:
			if (eventListener_ != nullptr)
			{
				eventListener_->OnCloseWindow(this);
			}
			break;

		case WM_DESTROY:
			if (eventListener_ != nullptr)
			{
				eventListener_->OnCloseWindow(this);
			}
			PostQuitMessage(0);
			return 0;


		case WM_ACTIVATEAPP:
			DirectX::Keyboard::ProcessMessage(uMsg, wParam, lParam);
			DirectX::Mouse::ProcessMessage(uMsg, wParam, lParam);
		case WM_INPUT:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_MOUSEHOVER:
			DirectX::Mouse::ProcessMessage(uMsg, wParam, lParam);

		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		case WM_KEYUP:
		case WM_SYSKEYUP:
			DirectX::Keyboard::ProcessMessage(uMsg, wParam, lParam);
			break;
			
		return 0;

		default:
			return DefWindowProc(hWnd_, uMsg, wParam, lParam);
		}
		return TRUE;
	}
private:
	EventListener* eventListener_ = nullptr;
};
}