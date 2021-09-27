#pragma once
#include <iostream>
#include <Windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3dcompiler.h>

template<class ID3D11ShaderType>
class IShader
{
public:
	IShader() = default;

	ID3D11ShaderType* GetShader() const
	{
		return shader_.Get();
	}

	ID3D10Blob* GetShaderBuffer() const
	{
		return shaderBuffer_.Get();
	}

	ID3D11InputLayout* GetInputLayout() const
	{
		return inputLayout_.Get();
	}

protected:
	Microsoft::WRL::ComPtr<ID3D11ShaderType> shader_ = nullptr;
	Microsoft::WRL::ComPtr<ID3D10Blob> shaderBuffer_ = nullptr;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout_;
};

class VertexShader : public IShader<ID3D11VertexShader>
{
public:
	VertexShader() = default;

	bool Initialize(const Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shader_file_path, D3D11_INPUT_ELEMENT_DESC* layoutDesc, UINT
	                numElements)
	{
		HRESULT hr;
		hr = D3DReadFileToBlob(
			shader_file_path.c_str(), 
			shaderBuffer_.GetAddressOf());

		if (FAILED(hr))
		{
			message_logger::error(hr, L"No vertex shader found at this address");
			return false;
		}

		hr = device->CreateVertexShader(
			shaderBuffer_->GetBufferPointer(),
			this->shaderBuffer_->GetBufferSize(),
			NULL,
			this->shader_.GetAddressOf());

		if (FAILED(hr))
		{
			message_logger::error(hr, L"Vertex shader can't load. Try to use .cso file in folder with your .exe");
			return false;
		}

		hr = device->CreateInputLayout(
			layoutDesc,
			numElements,
			this->shaderBuffer_->GetBufferPointer(),
			this->shaderBuffer_->GetBufferSize(),
			this->inputLayout_.ReleaseAndGetAddressOf()
		);

		if (FAILED(hr))
		{
			message_logger::error(hr);
			return false;
		}

		return true;
	}
};

class PixelShader : public IShader<ID3D11PixelShader>
{
public:
	PixelShader() = default;

	bool Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring shader_file_path)
	{
		HRESULT hr;
		hr = D3DReadFileToBlob(
			shader_file_path.c_str(),
			shaderBuffer_.GetAddressOf());

		if (FAILED(hr))
		{
			message_logger::error(hr, L"Pixel shader can't load. Try to use .cso file in folder with your .exe");
			return false;
		}

		hr = device->CreatePixelShader(
			shaderBuffer_->GetBufferPointer(),
			this->shaderBuffer_->GetBufferSize(),
			NULL,
			this->shader_.GetAddressOf());

		if (FAILED(hr))
		{
			message_logger::error(hr, (LPWSTR)(shaderBuffer_->GetBufferPointer()));
			return false;
		}

		return true;
	}
};