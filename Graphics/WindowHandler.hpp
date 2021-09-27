#pragma once
#define _WS ws::

namespace ws
{
class WindowHandler
{
public:
	WindowHandler() = default;
	virtual ~WindowHandler() = default;
	
	virtual void CloseWindow() const = 0;
	virtual void OpenWindow() const = 0;
	virtual HWND GetWindow() const = 0;
	virtual UINT GetWindowWidth() const = 0;
	virtual UINT GetWindowHeight() const = 0;
	virtual UINT GetWindowPositionX() const = 0;
	virtual UINT GetWindowPositionY() const = 0;
	WindowHandler* GetWindowHandler()
	{
		return this;
	}

};
}