#pragma once
#include "Graphics/MainWindow.h"
#include "Graphics/DXGraphics.h"

namespace ws
{
class RenderWindow : public MainWindow, public _DX RenderTarget
{
public:
	RenderWindow() = default;
	RenderWindow(EventListener* event_listener) :
		MainWindow(event_listener),
		verticalSyncEnabled(false)
	{

	}

	void Clear(const _DX Color color = {}) const
	{
		this->deviceContext->ClearRenderTargetView(
			this->renderTargetView.Get(),
			reinterpret_cast<const FLOAT*>(&color));
		this->deviceContext->ClearDepthStencilView(
			this->depthStencilView.Get(),
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0F,
			0);
		this->deviceContext->RSSetState(rasterizerState.Get());
		this->deviceContext->OMSetDepthStencilState(
			this->depthStencilState.Get(), NULL);
	}

	void Present() const
	{
		this->swapChain->Present(static_cast<UINT>(verticalSyncEnabled), NULL);
	}

	bool InitializeRenderContext(const unsigned int currentFPS = (0x000000ff >> 1 << 1))
	{
		return
			this->InitializeDirectXRenderContext(
				this->hWnd_,
				this->width_,
				this->height_,
				currentFPS);
	}

	void EnableVSync() const
	{
		verticalSyncEnabled = true;
	}

	void DisableVSync() const
	{
		verticalSyncEnabled = false;
	}

private:
	mutable bool verticalSyncEnabled;
};
}
