#pragma once
#include "Graphics/WindowHandler.hpp"

namespace ws
{
class EventListener
{
protected:


public:
	virtual ~EventListener() = default;

	EventListener()
	{
		
	}
	
	virtual void OnCreateWindow(WindowHandler* window) = 0;

	virtual void OnCloseWindow(WindowHandler* window) = 0;
};
}