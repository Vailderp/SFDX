#pragma once
#include <Windows.h>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <stdexcept>

#include "../Util/MessageLogger.h"
#include "../Util/DataImpl.h"
#include <vector>
#include "DirectXTK/SimpleMath.h"
#include <DirectXTK/WICTextureLoader.h>

#define __VSCBBUFFER16 alignas(1 << (8 / 2))
#define _DX dx::

namespace DX
{
	inline bool __fastcall ThrowFailed(const HRESULT hr)
	{
		if (FAILED(hr))
		{
			message_logger::error(hr);
			return false;
		}
		return true;
	}

	inline void __fastcall ThrowFailed(const HRESULT hr, const int _Code)
	{
		if (FAILED(hr))
		{
			message_logger::error(hr);
			exit(_Code);
		}
	}
}

namespace dx
{
	class RenderTarget;
	class BaseRenderTarget;

class AdapterData
{
public:
	AdapterData(IDXGIAdapter* pAdapter) : 
		pAdapter_(pAdapter)
	{
		HRESULT hr = pAdapter_->GetDesc(&this->AdapterDesc_);
		if (FAILED(hr))
		{
			message_logger::error(hr);
		}
	}

	IDXGIAdapter* GetAdapter(void) const
	{
		return pAdapter_;
	}

	DXGI_ADAPTER_DESC GetAdapterDesc(void) const
	{
		return AdapterDesc_;
	}

private:
	IDXGIAdapter* pAdapter_ = nullptr;
	DXGI_ADAPTER_DESC AdapterDesc_;
};



class AdapterReader
{
public:
	static std::vector<AdapterData> GetAdapterData(void)
	{
		if (adapters.empty())
		{

			Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

			HRESULT hr = CreateDXGIFactory(
				__uuidof(IDXGIFactory),
				reinterpret_cast<tu::Ptr2<void>>(pFactory.GetAddressOf())
			);

			if (FAILED(hr))
			{
				message_logger::error(hr);
			}

			IDXGIAdapter* pAdapter;
			UINT index = 0;
			while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
			{
				adapters.emplace_back(pAdapter);
				index++;
			}
			return adapters;
		}
		else
		{
			return adapters;
		}
	}

	static inline std::vector<AdapterData> adapters;

};

class ViewPort
{
	friend class DirectXRenderGraphics;

public:

	ViewPort(void) = default;

	ViewPort(
		const DirectX::XMINT2 size, 
		const DirectX::XMINT2 topLeft = { 0, 0 }) :
		size_(size),
		topLeft_(topLeft)
	{

	}

	ViewPort(
		const int width,
		const int height, 
		const int topLeftX = 0,
		const int topLeftY = 0) :
		size_{ width, height },
		topLeft_{topLeftX, topLeftY}
	{

	}

	void SetSize(DirectX::XMINT2 size)
	{
		size_ = size;
	}

	void SetSize(
		const int width,
		const int height
	)
	{
		size_.x = width;
		size_.y = height;
	}

	void SetTopLeft(DirectX::XMINT2 topLeft)
	{
		topLeft_ = topLeft;
	}

	void SetTopLeft(
		const int topLeftX = 0,
		const int topLeftY = 0
	)
	{
		topLeft_.x = topLeftX;
		topLeft_.y = topLeftY;
	}

	const DirectX::XMINT2& GetSize() const
	{
		return size_;
	}

	const DirectX::XMINT2& GetTopLeft() const
	{
		return topLeft_;
	}

private:
	DirectX::XMINT2 size_;
	DirectX::XMINT2 topLeft_;
};

struct Color
{
	Color(
		const float r = 0.0F, 
		const float g = 0.0F, 
		const float b = 0.0F,
		const float a = 1.0F
	) : 
		r(r),
		g(g),
		b(b),
		a(a)
	{

	}

	float r;
	float g;
	float b;
	float a;
};

template<typename _Value_type>
struct Vector2
{
	Vector2(
		const _Value_type x = 0,
		const _Value_type y = 0
	) :
		x(x),
		y(y)
	{

	}

	_Value_type x;
	_Value_type y;
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector2ui = Vector2<unsigned int>;
using Position2Df = Vector2f;

template<typename _Value_type>
struct Vector3
{
	Vector3(
		const _Value_type x = 0,
		const _Value_type y = 0,
		const _Value_type z = 0
	) :
		x(x),
		y(y),
		z(z)
	{

	}

	_Value_type x;
	_Value_type y;
	_Value_type z;
};

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;
using Vector2ui = Vector2<unsigned int>;
using Position3Df = Vector3f;

class Vertex2D
{
public:
	Vertex2D(void) :
		pos{ 0,0 },
		color{1, 1, 1, 1}
	{
		
	}

	Vertex2D(
		const Position2Df position = {},
		const Color color = {}
	) :
		pos{ position.x, position.y },
		color{ color.r, color.g, color.b, color.a }
	{

	}

	DirectX::XMFLOAT2 pos;
	DirectX::XMFLOAT4 color;
};

class Vertex3D
{
public:
	Vertex3D(void) :
		pos{ 0, 0, 0 },
		color{ 1, 1, 1, 1 }
	{

	}

	Vertex3D(
		const Position3Df position = {}, 
		const Color color = {}
	) :
		pos{ position.x, position.y, position.z },
		color{ color.r, color.g, color.b, color.a }
	{

	}

	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
};

class VertexTexture2D
{
public:
	VertexTexture2D(
		const Position2Df position = {},
		const Position2Df textureCoord = {}
	) :
		pos{ position.x, position.y },
		texCoord(textureCoord.x, textureCoord.y)
	{
		
	}

	DirectX::XMFLOAT2 pos;
	DirectX::XMFLOAT2 texCoord;
};



template<class VertexND>
class VertexBuffer : public std::vector<VertexND>
{
public:

	VertexBuffer(void) = default;

	UINT GetByteWidth(void) const
	{
		return static_cast<UINT>(sizeof(VertexND) * this->size());
	}

	using type = VertexND;
};

using VertexBuffer2D = VertexBuffer<Vertex2D>;
using VertexBuffer3D = VertexBuffer<Vertex3D>;
using VertexTextureBuffer2D = VertexBuffer<VertexTexture2D>;
//using VertexTextureBuffer3D = VertexBuffer<VertexTexture3D>;

template<typename VertexND>
class Drawable;

template<typename VertexND>
class VertexBufferable;

class VertexPixelShaderable;

class ConstantBufferable;

class ShaderLayout;

template <typename VertexND>
class DrawableHelper
{
public:
	static bool __fastcall CreateShaderLayout(
		VertexPixelShaderable* pVertexPixelShaderable,
		Microsoft::WRL::ComPtr<ID3D11Device>& device,
		std::wstring vertexShaderFilePath,
		std::wstring pixelShaderFilePath
	);

	static bool __fastcall CreateShaderLayout(
		VertexPixelShaderable* pVertexPixelShaderable,
		Microsoft::WRL::ComPtr<ID3D11Device>& device,
		ShaderLayout& shaderLayout,
		std::wstring vertexShaderFilePath,
		std::wstring pixelShaderFilePath
	);

	template <typename ConstantBufferType>
	static bool __fastcall CreateConstantBuffer(
		ConstantBufferable* pDrawable,
		Microsoft::WRL::ComPtr<ID3D11Device>& device
	);

	static bool __fastcall Initialize(
		VertexBufferable<VertexND>* pVertexBufferable,
		const Microsoft::WRL::ComPtr<ID3D11Device>& device
	);

	template <typename ConstantBufferType>
	static bool __fastcall SetConstantBufferValue(
		ConstantBufferable* pDrawable,
		RenderTarget& renderTarget,
		INT bufferOffset,
		const ConstantBufferType& constant
	);

	static void __fastcall ActivateVertexConstantBuffer(
		ConstantBufferable* pDrawable,
		const RenderTarget& renderTarget
	);
};

class RenderTarget;

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

	bool Initialize(
		const Microsoft::WRL::ComPtr<ID3D11Device>& device, 
		std::wstring shader_file_path,
		D3D11_INPUT_ELEMENT_DESC* layoutDesc, 
		UINT numElements)
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
			message_logger::error(hr, reinterpret_cast<LPWSTR>(shaderBuffer_->GetBufferPointer()));
			return false;
		}

		return true;
	}
};



class BaseDrawable
{
public:
	BaseDrawable(void) = default;
	virtual ~BaseDrawable(void) = default;
	virtual void draw(BaseRenderTarget& renderTarget) = 0;
};

class ConstantBuffers : public std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>>
{
	template <typename VertexND>
	friend void DrawableHelper<VertexND>::ActivateVertexConstantBuffer(
		ConstantBufferable* pDrawable,
		const RenderTarget& renderTarget);
private:
	ID3D11Buffer** addresses = nullptr;
	ID3D11Buffer*** addressesOf = nullptr;
	UINT constantBuffersQuantity = 0;
public:
	ConstantBuffers(void) = default;
	ConstantBuffers(const Microsoft::WRL::ComPtr<ID3D11Buffer> buffer)
	{
		this->emplace_back(buffer.Get());
	}

	ConstantBuffers(const std::vector<Microsoft::WRL::ComPtr<ID3D11Buffer>> buffers)
	{
		for (Microsoft::WRL::ComPtr<ID3D11Buffer> buffer : buffers)
		{
			this->emplace_back(buffer.Get());
		}
	}

	void BeginCreating(const INT num)
	{
		addresses = reinterpret_cast<tu::PtrInf<tu::Ptr1<ID3D11Buffer>, 1>>
		(malloc(sizeof(tu::PtrInf<tu::Ptr1<ID3D11Buffer>, 0>) * num));

		addressesOf = reinterpret_cast<tu::PtrInf<tu::Ptr2<ID3D11Buffer>, 1>>
		(malloc(sizeof(tu::PtrInf<tu::Ptr2<ID3D11Buffer>, 0>) * num));

		constantBuffersQuantity = num;
	}

	size_t GenerateNew(void);

	void EndCreating(void) const
	{
		for(UINT i = 0; i < constantBuffersQuantity; i++)
		{
			addresses[i] = *addressesOf[i];
		}
		delete[] addressesOf;
	}
};

class ConstantBufferable
{
	template <typename VertexND>
	template <typename ConstantBufferType>
	friend bool __fastcall DrawableHelper<VertexND>::CreateConstantBuffer(
		ConstantBufferable* pDrawable,
		Microsoft::WRL::ComPtr<ID3D11Device>& device
	);

	template <typename VertexND>
	template <typename ConstantBufferType>
	friend bool __fastcall DrawableHelper<VertexND>::SetConstantBufferValue(
		ConstantBufferable* pDrawable,
		RenderTarget& renderTarget,
		const INT bufferOffset,
		const ConstantBufferType& constant
	);

	template <typename VertexND>
	friend void __fastcall DrawableHelper<VertexND>::ActivateVertexConstantBuffer(
		ConstantBufferable* pDrawable,
		const RenderTarget& renderTarget
	);

public:
	ConstantBufferable(void) = default;

protected:
	ConstantBuffers constantBuffers_;
};

template<typename VertexND>
class VertexBufferable
{
	template <class VertexND>
	friend bool __fastcall DrawableHelper<VertexND>::Initialize(
		VertexBufferable<VertexND>* drawable,
		const Microsoft::WRL::ComPtr<ID3D11Device>& device);
public:
	VertexBufferable(void) = default;

	VertexBuffer<VertexND>& GetVertexBuffer(void)
	{
		return vertexBuffer;
	}

	Microsoft::WRL::ComPtr<ID3D11Buffer>& GetDXVertexBuffer(void)
	{
		return DXVertexBuffer;
	}

	void SetVertexBuffer(VertexBuffer<VertexND> vertexBuffer)
	{
		this->vertexBuffer = vertexBuffer;
	}

	using VertexType = VertexND;
	using DrawableHelper = DrawableHelper<VertexType>;

protected:
	VertexBuffer<VertexND> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> DXVertexBuffer;
};

class VertexPixelShaderable
{
	template <class VertexND>
	friend bool __fastcall DrawableHelper<VertexND>::CreateShaderLayout(
		VertexPixelShaderable* pVertexPixelShaderable,
		Microsoft::WRL::ComPtr<ID3D11Device>& device,
		std::wstring vertexShaderFilePath,
		std::wstring pixelShaderFilePath
	);

	template <typename VertexND>
	friend bool __fastcall DrawableHelper<VertexND>::CreateShaderLayout(
		VertexPixelShaderable* pVertexPixelShaderable,
		Microsoft::WRL::ComPtr<ID3D11Device>& device,
		ShaderLayout& shaderLayout,
		std::wstring vertexShaderFilePath,
		std::wstring pixelShaderFilePath
	);

public:
	VertexPixelShaderable(void) = default;

protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> DXInputLayout;
	VertexShader vertexShader;
	PixelShader pixelShader;
};

class ShaderLayout;

class Texture
{

	friend class ShaderLayout;

	friend class RenderTarget;

public:

	Texture(void) = default;

	Texture(
		std::wstring_view textureFilePath,
		const Microsoft::WRL::ComPtr<ID3D11Device>& device
	)
	{
		LoadFromFile(textureFilePath, device);
	}

	void LoadFromFile(
		std::wstring_view textureFilePath, 
		const Microsoft::WRL::ComPtr<ID3D11Device>& device
	)
	{
		if(!DX::ThrowFailed(
			DirectX::CreateWICTextureFromFile(
				device.Get(), 
				textureFilePath.data(),
				nullptr, 
				DXTexture_.GetAddressOf())
		))
		{
			D3D11_TEXTURE2D_DESC textureDesc;
			Microsoft::WRL::ComPtr<ID3D11Texture2D> DXTextureInterface;
			this->DXTexture_->QueryInterface<ID3D11Texture2D>(DXTextureInterface.GetAddressOf());
			DXTextureInterface->GetDesc(&textureDesc);
			this->size_ = Vector2ui(textureDesc.Width, textureDesc.Height);
			throw std::runtime_error("Texture can't load");
		}
	}

	void SetReverse(const bool x, const bool y) const
	{
		isReversed_.x = x;
		isReversed_.y = y;
	}

	[[nodiscard]]
	Vector2<bool>& GetReverse() const
	{
		return isReversed_;
	}

	const Vector2ui& GetSize() const
	{
		return this->size_;
	}

private:
	static inline Microsoft::WRL::ComPtr<ID3D11SamplerState> DXSamplerState_;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> DXTexture_;
	Vector2ui size_;
	mutable Vector2<bool> isReversed_;
};

template<typename VertexND>
class Drawable :
					public BaseDrawable,
					public ConstantBufferable,
					public VertexBufferable<VertexND>,
					public VertexPixelShaderable
{
	friend class DirectXRenderGraphics;
	template <class VertexND>
	friend class DrawableHelper;

public:
	~Drawable() override = default;
	void draw(RenderTarget& renderTarget) override = 0;
};

class ShaderLayout
{
	template<typename  VertexND>
	friend static bool __fastcall DrawableHelper<VertexND>::CreateShaderLayout(
		VertexPixelShaderable* pVertexPixelShaderable,
		Microsoft::WRL::ComPtr<ID3D11Device>& device,
		ShaderLayout& shaderLayout,
		std::wstring vertexShaderFilePath,
		std::wstring pixelShaderFilePath);

public:
struct INPUT_ELEMENT_DESC : D3D11_INPUT_ELEMENT_DESC
{
	INPUT_ELEMENT_DESC(
		DXGI_FORMAT dxgiFormat,
		std::string_view descName, 
		D3D11_INPUT_CLASSIFICATION input_classification =
		D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA) :
		D3D11_INPUT_ELEMENT_DESC({
			descName.data(),
			0U,
			dxgiFormat,
			0U,
			0U,
			input_classification,
			0U })
	{}
};

private:
	static inline bool texturingIsEnabled = false;

public:
	static bool __fastcall EnableTextures(const Microsoft::WRL::ComPtr<ID3D11Device>& device)
	{
		if (!texturingIsEnabled)
		{
			texturingIsEnabled = true;
			D3D11_SAMPLER_DESC samplerDesc;
			ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_NEVER;
			samplerDesc.MinLOD = NULL;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
			if (!DX::ThrowFailed(
				device->CreateSamplerState(
					&samplerDesc,
					Texture::DXSamplerState_.GetAddressOf()
				)
			))
			{
				return false;
			}
		}
	}

public:
	ShaderLayout(void) = default;

	void PushElementDesc(const D3D11_INPUT_ELEMENT_DESC inputElementDesc)
	{
		DXLayout_.push_back(inputElementDesc);
	}

	decltype(auto) operator << (const D3D11_INPUT_ELEMENT_DESC inputElementDesc)
	{
		this->PushElementDesc(inputElementDesc);
		return *this;
	}

	void FormatAlignedByteOffset()
	{
		for (size_t i = 1; i < DXLayout_.size(); i++)
		{
			DXLayout_[i].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		}
	}

	UINT GelLength() const
	{
		return static_cast<UINT>(DXLayout_.size());
	}

	D3D11_INPUT_ELEMENT_DESC* GetDesc()
	{
		return DXLayout_.data();
	}

private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> DXLayout_;
};

template <class VertexND>
bool __fastcall DrawableHelper<VertexND>::CreateShaderLayout(
	VertexPixelShaderable* pVertexPixelShaderable, 
	Microsoft::WRL::ComPtr<ID3D11Device>& device,
	std::wstring vertexShaderFilePath, 
	std::wstring pixelShaderFilePath
)
{
	ShaderLayout shaderLayout;

	if constexpr (std::is_same_v<VertexND, Vertex3D>)
	{
		shaderLayout
		<< ShaderLayout::INPUT_ELEMENT_DESC(
			DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,
			"POSITION")
		<< ShaderLayout::INPUT_ELEMENT_DESC(
			DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 
			"COLOR");
	}
	else if constexpr (std::is_same_v<VertexND, Vertex2D>)
	{
		shaderLayout
		<< ShaderLayout::INPUT_ELEMENT_DESC(
			DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
			"POSITION")
		<< ShaderLayout::INPUT_ELEMENT_DESC(
			DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
			"COLOR");
	}
	else if constexpr (std::is_same_v<VertexND, VertexTexture2D>)
	{
		ShaderLayout::EnableTextures(device);
		
		shaderLayout
			<< ShaderLayout::INPUT_ELEMENT_DESC(
				DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
				"POSITION")
			<< ShaderLayout::INPUT_ELEMENT_DESC(
				DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,
				"TEXCOORD");
		//<< ShaderLayout::INPUT_ELEMENT_DESC(
			//DXGI_FORMAT::DX,
			//"TEXCOORD")
	}
	else
	{
		message_logger::error(L"Use only VertexND or VertexTypeND in bool CreateShaderLayout()");
		exit(-1);
	}

	shaderLayout.FormatAlignedByteOffset();

	if (!pVertexPixelShaderable->vertexShader.Initialize(
		device,
		vertexShaderFilePath, 
		shaderLayout.GetDesc(),
		shaderLayout.GelLength())
		)
	{
		return false;
	}

	if (!pVertexPixelShaderable->pixelShader.Initialize(device, pixelShaderFilePath))
	{
		return false;
	}

	return true;
}

template <typename VertexND>
bool __fastcall DrawableHelper<VertexND>::CreateShaderLayout(
	VertexPixelShaderable* pVertexPixelShaderable,
	Microsoft::WRL::ComPtr<ID3D11Device>& device, 
	ShaderLayout& shaderLayout, 
	std::wstring vertexShaderFilePath,
	std::wstring pixelShaderFilePath)
{
	if (!pVertexPixelShaderable->vertexShader.Initialize(
		device,
		vertexShaderFilePath, 
		shaderLayout.DXLayout_.data(),
		static_cast<UINT>(shaderLayout.DXLayout_.size()))
		)
	{
		return false;
	}

	if (!pVertexPixelShaderable->pixelShader.Initialize(
		device,
		pixelShaderFilePath)
		)
	{
		return false;
	}

	return true;
}

template <typename VertexND>
template <typename ConstantBufferType>
bool __fastcall DrawableHelper<VertexND>::CreateConstantBuffer(
	ConstantBufferable* pDrawable,
	Microsoft::WRL::ComPtr<ID3D11Device>& device)
{
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = NULL;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.ByteWidth = sizeof(ConstantBufferType);

	return DX::ThrowFailed(
		device->CreateBuffer(
			&bufferDesc, 
			nullptr,
			pDrawable->constantBuffers_.at(
				pDrawable->constantBuffers_.GenerateNew()
			).GetAddressOf()
		)
	);

}

template <class VertexND>
bool __fastcall DrawableHelper<VertexND>::Initialize(
	VertexBufferable<VertexND>* pVertexBufferable,
	const Microsoft::WRL::ComPtr<ID3D11Device>& device)
{
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = pVertexBufferable->vertexBuffer.GetByteWidth();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = NULL;
	vertexBufferDesc.MiscFlags = NULL;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = pVertexBufferable->vertexBuffer.data();
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	return DX::ThrowFailed(
		device->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			pVertexBufferable->DXVertexBuffer.GetAddressOf()
		)
	);

}

inline size_t ConstantBuffers::GenerateNew(void)
{
	this->push_back({});
	addressesOf[this->size() - 1] = (*this)[this->size() - 1].GetAddressOf();
	return this->size() - 1;
}


class DirectXRenderGraphics
{
public:
	DirectXRenderGraphics(void) = default;

	bool InitializeDirectXRenderContext(
		_In_ HWND hWnd, 
		const int width,
		const int height,
		const UINT currentFPS
	)
	{
		if (AdapterReader::GetAdapterData().empty())
		{
			return false;
		}
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof sd);
		sd.BufferCount = 1;
		sd.BufferDesc.Width = width;
		sd.BufferDesc.Height = height;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		sd.BufferDesc.RefreshRate.Numerator = currentFPS;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = hWnd;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		if (!DX::ThrowFailed(
			D3D11CreateDeviceAndSwapChain(
				AdapterReader::GetAdapterData()[NULL].GetAdapter(),
				D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
				nullptr,
				NULL,
				nullptr,
				0,
				D3D11_SDK_VERSION,
				&sd,
				this->swapChain.GetAddressOf(),
				this->device.GetAddressOf(),
				nullptr,
				this->deviceContext.GetAddressOf()
			)
		))
		{
			return false;
		}
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
		if(!DX::ThrowFailed(
			this->swapChain->GetBuffer(
				0, 
				__uuidof(ID3D11Texture2D),
				reinterpret_cast<tu::Ptr2<void>>(backBuffer.GetAddressOf()))
		))
		{
			return false;
		}
		if (!DX::ThrowFailed(
			this->device->CreateRenderTargetView(
				backBuffer.Get(),
				nullptr, 
				this->renderTargetView.GetAddressOf()
			)
		))
		{
			return false;
		}

		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.Width = width;
		depthStencilDesc.Height = height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = NULL;
		depthStencilDesc.MiscFlags = NULL;
		if (!DX::ThrowFailed(
			this->device->CreateTexture2D(
				&depthStencilDesc,
				nullptr,
				this->depthStencilBuffer.GetAddressOf()
			)
		))
		{
			return false;
		}
		if (!DX::ThrowFailed(
			this->device->CreateDepthStencilView(
				this->depthStencilBuffer.Get(),
				nullptr, 
				this->depthStencilView.GetAddressOf())
		))
		{
			return false;
		};
		this->deviceContext->OMSetRenderTargets(
			1,
			this->renderTargetView.GetAddressOf(),
			this->depthStencilView.Get()
		);
		D3D11_DEPTH_STENCIL_DESC depthStencilState;
		ZeroMemory(&depthStencilState, sizeof(decltype(depthStencilState)));
		depthStencilState.DepthEnable = TRUE;
		depthStencilState.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilState.DepthFunc = D3D11_COMPARISON_LESS;
		if (!DX::ThrowFailed(
			this->device->CreateDepthStencilState(
				&depthStencilState, 
				this->depthStencilState.GetAddressOf()
			)
		))
		{
			return false;
		}
		this->setViewPort(ViewPort(width, height));
		return true;
	}

	void setViewPort(ViewPort viewPort)
	{
		D3D11_VIEWPORT DXViewPort;
		ZeroMemory(&DXViewPort, sizeof(D3D11_VIEWPORT));
		DXViewPort.TopLeftX = static_cast<FLOAT>(viewPort.topLeft_.x);
		DXViewPort.TopLeftY = static_cast<FLOAT>(viewPort.topLeft_.y);
		DXViewPort.Width = static_cast<FLOAT>(viewPort.size_.x);
		DXViewPort.Height = static_cast<FLOAT>(viewPort.size_.y);
		DXViewPort.MaxDepth = 1.0F;
		DXViewPort.MinDepth = 0.0F;
		this->deviceContext->RSSetViewports(1, &DXViewPort);
		CD3D11_RASTERIZER_DESC rastDesc(
			D3D11_FILL_SOLID, 
			D3D11_CULL_NONE, 
			FALSE,
			D3D11_DEFAULT_DEPTH_BIAS, 
			D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
			D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS,
			TRUE,
			FALSE,
			TRUE /*this is MSAA enable*/, 
			FALSE);
		D3D11_RASTERIZER_DESC rasterizerDesc;
		ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.AntialiasedLineEnable = TRUE;
		HRESULT hr = this->device->CreateRasterizerState(
			&rastDesc,
			rasterizerState.GetAddressOf()
		);
		if (hr != S_OK)
		{
			message_logger::error(hr);
		}
	}

	Microsoft::WRL::ComPtr<ID3D11Device>& GetDevice()
	{
		return this->device;
	}

	Microsoft::WRL::ComPtr<ID3D11DeviceContext>& GetDeviceContext()
	{
		return this->deviceContext;
	}

	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;

protected:

	Microsoft::WRL::ComPtr<ID3D11Device> device;
	Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerState;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;

};

class BaseRenderTarget
{
public:
	void Draw(BaseDrawable& drawable)
	{
		drawable.draw(*this);
	}
};

class RenderTarget : public DirectXRenderGraphics, public BaseRenderTarget
{
public:

	void BindTexture(Texture& texture) const
	{
		this->deviceContext->PSSetSamplers(
			0,
			1,
			texture.DXSamplerState_.GetAddressOf()
		);

		this->deviceContext->PSSetShaderResources(
			0, 
			1, 
			texture.DXTexture_.GetAddressOf()
		);
	}
};

template <typename VertexND>
template <typename ConstantBufferType>
bool __fastcall DrawableHelper<VertexND>::SetConstantBufferValue(
	ConstantBufferable* pDrawable,
	RenderTarget& renderTarget,
	const INT bufferOffset,
	const ConstantBufferType& constant)
{
	D3D11_MAPPED_SUBRESOURCE mappedSubresource;
	const bool result = DX::ThrowFailed(
		renderTarget.deviceContext->Map(
			pDrawable->constantBuffers_[bufferOffset].Get(), 
		NULL, 
		D3D11_MAP::D3D11_MAP_WRITE_DISCARD,
			0, &mappedSubresource
		));
	CopyMemory(
		mappedSubresource.pData,
		&constant,
		sizeof(ConstantBufferType)
	);
	renderTarget.deviceContext->Unmap(
		pDrawable->constantBuffers_[bufferOffset].Get(), 
		NULL);
	return result;
}

template <typename VertexND>
void __fastcall DrawableHelper<VertexND>::ActivateVertexConstantBuffer(
	ConstantBufferable* pDrawable,
	const RenderTarget& renderTarget
)
{
	renderTarget.deviceContext->VSSetConstantBuffers(
		0,
		static_cast<UINT>(pDrawable->constantBuffers_.size()),
		pDrawable->constantBuffers_.addresses);
}

struct __VSCBBUFFER16 VSCBModel
{
	DirectX::XMMATRIX model;
};

struct __VSCBBUFFER16 VSCBModelViewProjection
{
	DirectX::XMMATRIX model;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
};

} // namespace dx