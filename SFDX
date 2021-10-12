#pragma once
#include "Camera.h"
#include "Graphics/DXGraphics.h"
#include "Graphics/RenderWindow.h"
#define DENAME(T) #T
#define _DS ds::
#define _2D ds::G2D::

namespace ds
{
	struct __VSCBBUFFER16 Transform2D
	{
		Transform2D() :
			position_(0, 0),
			rotation_(0),
			positionMatrix_(DirectX::XMMatrixIdentity()),
			rotationMatrix_(DirectX::XMMatrixIdentity())
		{

		}
		mutable _DX Vector2f position_;
		mutable _DX Vector2f origin_;
		mutable float rotation_;
		mutable DirectX::XMMATRIX positionMatrix_;
		mutable DirectX::XMMATRIX originMatrix_;
		mutable DirectX::XMMATRIX rotationMatrix_;
	};

	struct __VSCBBUFFER16 Transform3D
	{
		Transform3D() :
			position_(0, 0, 0),
			rotation_(0, 0, 0),
			positionMatrix_(DirectX::XMMatrixIdentity()),
			rotationMatrix_(DirectX::XMMatrixIdentity())
		{

		}
		mutable _DX Vector3f position_;
		mutable _DX Vector3f origin_;
		mutable _DX Vector3f rotation_;
		mutable DirectX::XMMATRIX positionMatrix_;
		mutable DirectX::XMMATRIX originMatrix_;
		mutable DirectX::XMMATRIX rotationMatrix_;
	};

	class Transformable2D : protected Transform2D
	{
	protected:
		mutable bool has_changed = false;

	public:
		Transformable2D()
		{
			this->positionMatrix_ = DirectX::XMMatrixTranslation(position_.x, position_.y, 0);
			this->originMatrix_ = DirectX::XMMatrixTranslation(origin_.x, origin_.y, 0);
			this->rotationMatrix_ = DirectX::XMMatrixRotationZ(rotation_);
		}

		void setPosition(const _DX Vector2f position) const
		{
			this->position_ = position;
			this->positionMatrix_ = DirectX::XMMatrixTranslation(position_.x, position_.y, 0);

		}

		void setPosition(const float x, const float y) const
		{
			this->position_.x = x;
			this->position_.y = y;
			this->positionMatrix_ = DirectX::XMMatrixTranslation(position_.x, position_.y, 0);
		}

		void move(const _DX Vector2f position) const
		{
			this->position_.x += position.x;
			this->position_.y += position.y;
			this->positionMatrix_ = DirectX::XMMatrixTranslation(position_.x, position_.y, 0);
		}

		void move(const float x, const float y) const
		{
			this->position_.x += x;
			this->position_.y += y;
			this->positionMatrix_ = DirectX::XMMatrixTranslation(position_.x, position_.y, 0);
		}

		void setOrigin(const _DX Vector2f origin) const
		{
			this->origin_ = origin;
			this->originMatrix_ = DirectX::XMMatrixTranslation(origin_.x, origin_.y, 0);

		}

		void setOrigin(const float x, const float y) const
		{
			this->origin_.x = x;
			this->origin_.y = y;
			this->originMatrix_ = DirectX::XMMatrixTranslation(origin_.x, origin_.y, 0);
		}

		void origin(const _DX Vector2f origin) const
		{
			this->origin_.x += origin.x;
			this->origin_.y += origin.y;
			this->originMatrix_ = DirectX::XMMatrixTranslation(origin_.x, origin_.y, 0);
		}

		void origin(const float x, const float y) const
		{
			this->origin_.x += x;
			this->origin_.y += y;
			this->originMatrix_ = DirectX::XMMatrixTranslation(origin_.x, origin_.y, 0);
		}

		void setRotation(const float rotation) const
		{
			this->rotation_ = rotation;
			this->rotationMatrix_ = DirectX::XMMatrixRotationZ(this->rotation_);
		}

		void rotate(const float rotation) const
		{
			this->rotation_ += rotation;
			this->rotationMatrix_ = DirectX::XMMatrixRotationZ(this->rotation_);
		}

		const _DX Vector2f getPosition() const
		{
			return this->position_;
		}

		const _DX Vector2f getOrigin() const
		{
			return this->origin_;
		}

		const float getRotation() const
		{
			return this->rotation_;
		}

		DirectX::XMMATRIX& getRotationMatrix()
		{
			return this->rotationMatrix_;
		}

		DirectX::XMMATRIX& getPositionMatrix()
		{
			return this->rotationMatrix_;
		}

		DirectX::XMMATRIX& getOriginMatrix()
		{
			return this->rotationMatrix_;
		}
	};

	class Transformable3D : protected Transform3D
	{
	protected:
		mutable bool has_changed = false;

	public:
		Transformable3D()
		{
			this->positionMatrix_ = DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);
			this->originMatrix_ = DirectX::XMMatrixTranslation(origin_.x, origin_.y, origin_.z);
			this->rotationMatrix_ = DirectX::XMMatrixRotationRollPitchYaw(rotation_.x, rotation_.y, rotation_.z);
		}

		void setPosition(const _DX Vector3f position) const
		{
			this->position_ = position;
			this->positionMatrix_ = DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);

		}

		void setPosition(const float x, const float y, const float z) const
		{
			this->position_.x = x;
			this->position_.y = y;
			this->position_.z = z;
			this->positionMatrix_ = DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);
		}

		void move(const _DX Vector3f position) const
		{
			this->position_.x += position.x;
			this->position_.y += position.y;
			this->position_.z += position.z;
			this->positionMatrix_ = DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);
		}

		void move(const float x, const float y, const float z) const
		{
			this->position_.x += x;
			this->position_.y += y;
			this->position_.z += z;
			this->positionMatrix_ = DirectX::XMMatrixTranslation(position_.x, position_.y, position_.z);
		}

		void setOrigin(const _DX Vector3f origin) const
		{
			this->origin_ = origin;
			this->originMatrix_ = DirectX::XMMatrixTranslation(origin_.x, origin_.y, origin_.z);

		}

		void setOrigin(const float x, const float y, const float z) const
		{
			this->origin_.x = x;
			this->origin_.y = y;
			this->origin_.z = z;
			this->originMatrix_ = DirectX::XMMatrixTranslation(origin_.x, origin_.y, origin_.z);
		}

		void origin(const _DX Vector3f origin) const
		{
			this->origin_.x += origin.x;
			this->origin_.y += origin.y;
			this->origin_.z += origin.z;
			this->originMatrix_ = DirectX::XMMatrixTranslation(origin_.x, origin_.y, origin_.z);
		}

		void origin(const float x, const float y, const float z) const
		{
			this->origin_.x += x;
			this->origin_.y += y;
			this->origin_.z += z;
			this->originMatrix_ = DirectX::XMMatrixTranslation(origin_.x, origin_.y, origin_.z);
		}

		void setRotation(const _DX Vector3f rotation) const
		{
			this->rotation_ = rotation;
			this->rotationMatrix_ = DirectX::XMMatrixRotationRollPitchYaw(rotation_.x, rotation_.y, rotation_.z);
		}

		void setRotation(const float x, const float y, const float z) const
		{
			this->rotation_.x = x;
			this->rotation_.y = y;
			this->rotation_.z = z;
			this->rotationMatrix_ = DirectX::XMMatrixRotationRollPitchYaw(rotation_.x, rotation_.y, rotation_.z);
		}

		void rotate(const _DX Vector3f rotation) const
		{
			this->rotation_.x += rotation.x;
			this->rotation_.y += rotation.y;
			this->rotation_.z += rotation.z;
			this->rotationMatrix_ = DirectX::XMMatrixRotationRollPitchYaw(rotation_.x, rotation_.y, rotation_.z);
		}

		void rotate(const float x, const float y, const float z) const
		{
			this->rotation_.x += x;
			this->rotation_.y += y;
			this->rotation_.z += z;
			this->rotationMatrix_ = DirectX::XMMatrixRotationRollPitchYaw(rotation_.x, rotation_.y, rotation_.z);
		}

		const _DX Vector3f getPosition() const
		{
			return this->position_;
		}

		const _DX Vector3f getRotation() const
		{
			return this->rotation_;
		}

		const _DX Vector3f getOrigin() const
		{
			return this->origin_;
		}

		DirectX::XMMATRIX& getRotationMatrix()
		{
			return this->rotationMatrix_;
		}

		DirectX::XMMATRIX& getPositionMatrix()
		{
			return this->rotationMatrix_;
		}

		DirectX::XMMATRIX& getOriginMatrix()
		{
			return this->rotationMatrix_;
		}

	};

	namespace G2D 
	{ 
		inline void __fastcall AtFlotToAtWindow(_DX Vector2f& fvec); 
	}
	namespace G2D
	{
		inline void __fastcall AtWindowToAtFloat(_DX Vector2f& fvec);
	}

	class RenderWindow : public _WS RenderWindow
	{
		friend void __fastcall G2D::AtFlotToAtWindow(_DX Vector2f& fvec); 
		friend void __fastcall G2D::AtWindowToAtFloat(_DX Vector2f& fvec);
	public:

		RenderWindow(
			_WS EventListener* event_listener,
			_In_ HINSTANCE hInstance,
			_In_ int nCmdShow,
			LPCWSTR tittle, 
			const int width, 
			const int height, 
			const int position_x,
			const int position_y
		) :	_WS RenderWindow(event_listener)
		{
			if (!isCreated)
			{
				if (!this->Initialize(hInstance, nCmdShow, L"DSWND"))
				{
					throw std::runtime_error("unknown error");
				}
				this->Create(tittle, width, height, position_x, position_y);
				this->InitializeRenderContext();
				RenderWindow::window_ = this;
				isCreated = true;
			}
			else
			{
				throw std::runtime_error("Only one window can be created");
			}
		}

		RenderWindow(
			_WS EventListener& event_listener, 
			_In_ HINSTANCE hInstance,
			_In_ int nCmdShow,
			LPCWSTR tittle,
			const int width,
			const int height,
			const int position_x,
			const int position_y
		) : _WS RenderWindow(&event_listener)
		{
			if (!isCreated)
			{
				if (!this->Initialize(hInstance, nCmdShow, L"DSWND"))
				{
					throw std::runtime_error("unknown error");
				}
				this->Create(tittle, width, height, position_x, position_y);
				this->InitializeRenderContext();
				RenderWindow::window_ = this;
				isCreated = true;
			}
			else
			{
				throw std::runtime_error("Only one window can be created");
			}
		}

		static inline RenderWindow* window_ = nullptr;
	private:
		static inline bool isCreated = false;
	};

	class Textureable
	{
	public:
		Textureable() = default;

		void SetTexture(_DX Texture* const texture)
		{
			texture_ = texture;
		}

		void SetTexture(_DX Texture& texture)
		{
			texture_ = &texture;
		}

		void SetTexture(const _DX Texture texture) const
		{
			*texture_ = texture;
		}

		[[nodiscard]]
		_DX Texture& GetTexture() const
		{
			return *texture_;
		}

	protected:
		_DX Texture* texture_ = nullptr;
	};

	template<D3D11_PRIMITIVE_TOPOLOGY _PrimitiveTopology, typename VertexND>
	class Shape2D :	public _DS Textureable, 
					public _DS Transformable2D,
					public _DX BaseDrawable, 
					public _DX VertexBufferable<VertexND>, 
					public _DX ConstantBufferable
	{
	public:
		Shape2D() = default;

		void draw(_DX BaseRenderTarget& renderTarget) override = 0;

	};

	namespace G2D
	{
		inline void __fastcall AtFlotToAtWindow(_DX Vector2f& fvec)
		{
			fvec.x += 1;
			fvec.y += 1;
			fvec.x /= 2;
			fvec.y /= 2;
			fvec.x *= static_cast<float>(_DS RenderWindow::window_->GetWindowWidth());
			fvec.y *= static_cast<float>(_DS RenderWindow::window_->GetWindowHeight());
		}

		inline void __fastcall AtWindowToAtFloat(_DX Vector2f& fvec)
		{
			fvec.x /= static_cast<float>(_DS RenderWindow::window_->GetWindowWidth());
			fvec.y /= static_cast<float>(_DS RenderWindow::window_->GetWindowHeight());
			fvec.x *= 2;
			fvec.y *= 2;
			fvec.x -= 1;
			fvec.y -= 1;
		}

		typedef enum CoordinateSystemType
		{
			AtWindow,
			AtFloat
		} CoordinateSystemType;

		struct __VSCBBUFFER16 GUIBUUFER : _DX VSCBModel
		{

		};

		template<CoordinateSystemType _CoordinateSystemType>
		class RectangleShape : public _DS Shape2D<D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST, _DX VertexTexture2D>
		{
		public:
			RectangleShape(_DX Vector2f position = {0.5f, 0.5f}, _DX Vector2f size = { 0.5f, 0.5f })
			{
				if constexpr (_CoordinateSystemType == AtWindow)
				{
					AtWindowToAtFloat(position);
					AtWindowToAtFloat(size);
				}

				{
					using namespace dx;
					this->vertexBuffer.push_back(VertexTexture2D(Vector2f(position.x, position.y), Vector2f(0, 0)));
					this->vertexBuffer.push_back(VertexTexture2D(Vector2f(position.x, position.y + (-size.y)), Vector2f(0, 1)));
					this->vertexBuffer.push_back(VertexTexture2D(Vector2f(position.x + size.x, position.y + (-size.y)), Vector2f(1, 1)));

					this->vertexBuffer.push_back(VertexTexture2D(Vector2f(position.x + size.x, position.y), Vector2f(1, 0)));
					this->vertexBuffer.push_back(VertexTexture2D(Vector2(position.x + size.x, position.y + (-size.y)), Vector2f(1, 1)));
					this->vertexBuffer.push_back(VertexTexture2D(Vector2f(position.x, position.y), Vector2f(0, 0)));
				}
				this->constantBuffers_.BeginCreating(1);

				DrawableHelper::CreateConstantBuffer<_DX VSCBModel>(
					this,
					_DS RenderWindow::window_->GetDevice()
					);

				this->constantBuffers_.EndCreating();
				DrawableHelper::Initialize(
					this, 
					_DS RenderWindow::window_->GetDevice()
				);
			}

			void draw(_DX BaseRenderTarget& renderTarget) override
			{
				this->guiBuffer_.model = DirectX::XMMatrixTranspose(this->getTransformMatrix());

				_DX DrawableHelper<_DX VertexTexture2D>::SetConstantBufferValue<GUIBUUFER>(
					this,
					*_DS RenderWindow::window_,
					0,
					guiBuffer_
				);

				_DX DrawableHelper<_DX VertexTexture2D>::ActivateVertexConstantBuffer(
					this,
					*_DS RenderWindow::window_
				);
			}

		private:
			GUIBUUFER guiBuffer_;
		};

		template<D3D11_PRIMITIVE_TOPOLOGY _PRIMITIVE_TOPOLOGY, typename VertexND>
		class IScene : public _DS Shape2D<_PRIMITIVE_TOPOLOGY, VertexND>
		{
		public:
			IScene(const UINT constantBuffersNum = 1)
			{
				this->constantBuffers_.BeginCreating(constantBuffersNum);

				_DX DrawableHelper<VertexND>::template
					CreateConstantBuffer<_DX VSCBModel>(
						this,
						_DS RenderWindow::window_->GetDevice()
						);

				this->constantBuffers_.EndCreating();
			}

			void draw(_DX BaseRenderTarget& renderTarget) override = 0;

			void PushVertex(VertexND&& vertex)
			{
				this->vertexBuffer.push_back(vertex);
			}

			void ActivateVertexMemory()
			{
				_DX DrawableHelper<VertexND>::template
					Initialize(
						this,
						_DS RenderWindow::window_->GetDevice()
					);
			}

		};

		template<CoordinateSystemType _CoordinateSystemType, typename VertexND>
		class Scene : public _2D IScene<D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST, VertexND>
		{
		public:
			Scene(_DX Vector2f position = { 0.5f, 0.5f }, _DX Vector2f size = { 0.5f, 0.5f })
			{

			}

			void draw(_DX BaseRenderTarget& renderTarget) override
			{
				this->guiBuffer_.model = DirectX::XMMatrixTranspose(
					this->positionMatrix_ * this->rotationMatrix_
				);

				_DX DrawableHelper<_DX VertexTexture2D>::SetConstantBufferValue<GUIBUUFER>(
					this, 
					*(_DS RenderWindow::window_),
					NULL,
					guiBuffer_
					);

				_DX DrawableHelper<_DX VertexTexture2D>::ActivateVertexConstantBuffer(
					this, 
					*(_DS RenderWindow::window_)
				);
			}

			void PushVertex(VertexND&& vertex)
			{
				this->vertexBuffer.push_back(vertex);
			}

			void ActivateVertexMemory()
			{
				_DX DrawableHelper<VertexND>::template
					Initialize(
						this,
						_DS RenderWindow::window_->GetDevice()
					);
			}

		private:
			GUIBUUFER guiBuffer_;
		};

		template<typename T>
		struct Rect
		{
			Rect(const _DX Vector2<T> position, const _DX Vector2<T> size) : 
				position(position),
				size(size)
			{

			}
			_DX Vector2<T> position;
			_DX Vector2<T> size;
		};

		using Rectf = Rect<float>;
		using Recti = Rect<int>;

		class Rectangle
		{
		public:
			template<CoordinateSystemType _CoordinateSystemType>
			Rectangle(Scene<_CoordinateSystemType, _DX VertexTexture2D>* scene, Rectf rectangle, Rectf texture)
			{
				{
					using namespace dx;
					scene->PushVertex(VertexTexture2D(Vector2f(rectangle.position.x, rectangle.position.y), 
						Vector2f(texture.position.x, texture.position.y)));
					scene->PushVertex(VertexTexture2D(Vector2f(rectangle.position.x, rectangle.position.y + (-rectangle.size.y)), 
						Vector2f(texture.position.x, texture.position.y + texture.size.y)));
					scene->PushVertex(VertexTexture2D(Vector2f(rectangle.position.x + rectangle.size.x, 
						rectangle.position.y + (-rectangle.size.y)), 
						Vector2f(texture.position.x + texture.size.x, texture.position.y + texture.size.y)));

					scene->PushVertex(VertexTexture2D(Vector2f(rectangle.position.x + rectangle.size.x, rectangle.position.y),
						Vector2f(texture.position.x + texture.size.x, texture.position.y)));
					scene->PushVertex(VertexTexture2D(Vector2f(rectangle.position.x + rectangle.size.x, 
						rectangle.position.y + (-rectangle.size.y)), 
						Vector2f(texture.position.x + texture.size.x, texture.position.y + texture.size.y)));
					scene->PushVertex(VertexTexture2D(Vector2f(rectangle.position.x, rectangle.position.y), 
						Vector2f(texture.position.x, texture.position.y)));

				}
				//scene->ActivateVertexMemory();
			}
		};

		template<typename VertexND>
		class Renderer : public _DX VertexPixelShaderable, public _DX BaseRenderTarget
		{
		public:

			Renderer() = default;

			void Initalize()
			{
#ifdef	SHADER_DEVELOPMENT_STAGE
				_DX DrawableHelper<VertexND>::CreateShaderLayout(
					this, _DS RenderWindow::window_->GetDevice(),
					L"../x64/Release/VertexShader.cso",
					L"../x64/Release/PixelShader.cso"
				);
#else
				_DX DrawableHelper<VertexND>::CreateShaderLayout(
					this, _DS RenderWindow::window_->GetDevice(),
					L"VertexShader.cso",
					L"PixelShader.cso"
				);
#endif
			}

			template<D3D11_PRIMITIVE_TOPOLOGY _PrimitiveTopology>
			void Draw(Shape2D<_PrimitiveTopology, VertexND>& shape)
			{
				_DS RenderWindow::window_->deviceContext->IASetPrimitiveTopology(_PrimitiveTopology);

				shape.draw(*this);

				_DS RenderWindow::window_->deviceContext->IASetInputLayout(this->vertexShader.GetInputLayout());
				_DS RenderWindow::window_->deviceContext->VSSetShader(this->vertexShader.GetShader(), nullptr, 0);
				_DS RenderWindow::window_->deviceContext->PSSetShader(this->pixelShader.GetShader(), nullptr, 0);

				UINT stride = sizeof(VertexND);
				UINT offset = 0;

				_DS RenderWindow::window_->BindTexture(shape.GetTexture());
				_DS RenderWindow::window_->deviceContext->IASetVertexBuffers(0, 1, shape.GetDXVertexBuffer().GetAddressOf(), &stride, &offset);

				_DS RenderWindow::window_->deviceContext->Draw(static_cast<UINT>(shape.GetVertexBuffer().size()), 0);
			}

		private:
			GUIBUUFER guibuffer_{};
		};
	}
};
