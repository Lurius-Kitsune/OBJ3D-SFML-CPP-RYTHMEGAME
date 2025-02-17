#pragma once
#include "Widget.h"
#include "MeshActor.h"

namespace UI
{
	struct ImageGradient
	{
		Color topLeft;
		Color topRight;
		Color bottomLeft;
		Color bottomRight;

		ImageGradient(const Color& _topLeft = Color(), const Color& _topRight = Color(),
				 const Color& _bottomLeft = Color(), const Color& _bottomRight = Color())
		{
			topLeft = ComputeTransparency(_topLeft);
			topRight = ComputeTransparency(_topRight);
			bottomLeft = ComputeTransparency(_bottomLeft);
			bottomRight = ComputeTransparency(_bottomRight);
		}

	private:
		Color ComputeTransparency(const Color& _color)
		{
			const uint8_t& _alpha = _color.a > 128 ? 128 : _color.a;
			return { _color.r, _color.g, _color.b, _alpha };
		}
	};

	class ImageWidget : public Widget
	{
		bool sizeToContent;
		Vector2f initialSize;
		VertexArray gradient;
		ImageGradient colorGradient;
		bool useGradient;
	protected:
		MeshComponent* image;

	public:
		FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
		{
			UpdatePosition(_position);
		}
		FORCEINLINE virtual void SetSize(const Vector2f _size)
		{
			UpdateSize(_size);
		}
		FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
		{
			Super::SetOrigin(_origin);
			image->GetShape()->SetOrigin(_origin);
		}
		FORCEINLINE virtual void SetOriginAtMiddle()
		{
			image->GetShape()->SetOrigin(image->GetShape()->GetDrawable()->getGeometricCenter());
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			UpdateMove(_offset);
		}
		FORCEINLINE virtual void SetFillColor(const Color& _color)
		{
			image->GetShape()->GetDrawable()->setFillColor(_color);
		}
		FORCEINLINE virtual void SetOutline(const float _thickness, const Color& _color)
		{
			image->GetShape()->GetDrawable()->setOutlineThickness(_thickness);
			image->GetShape()->GetDrawable()->setOutlineColor(_color);
		}
		FORCEINLINE virtual Vector2f GetSize() const override
		{
			return image->GetShape()->GetDrawable()->getLocalBounds().size;
		}
		FORCEINLINE virtual void SetTexture(const string& _path, const TextureExtensionType& _type = PNG)
		{
			if (_path.empty())
			{
				LOG(Error, "Cannot open file with an empty path !");
				M_TEXTURE.Load(image->GetShape(), "White", PNG);
			}
			else
			{
				M_TEXTURE.Load(image->GetShape(), _path, _type);
			}
		}
		FORCEINLINE virtual void SetRect(const IntRect& _rect)
		{
			M_TEXTURE.SetTextureRect(image->GetShape()->GetDrawable(), _rect);
		}
		//Only Set the Alpha of the Color
		FORCEINLINE virtual void SetTransparency(const u_int& _alpha)
		{
			SetFillColor(Color(GetFillColor().r, GetFillColor().g, GetFillColor().b, _alpha));
		}
		FORCEINLINE virtual Color GetFillColor() const
		{
			return image->GetShape()->GetDrawable()->getFillColor();
		}

	public:
		ImageWidget(Level* _level, const RectangleShapeData& _data, const string& _name = "Image", const RenderType& _type = Screen);
		ImageWidget(Level* _level, const CircleShapeData& _data, const string& _name = "Image", const RenderType& _type = Screen);
		ImageWidget(const ImageWidget& _other);

	private:
		void UpdateGradient();
		void UpdatePosition(const Vector2f& _position);
		void UpdateMove(const Vector2f& _offset);
		void UpdateSize(const Vector2f& _size);

	public:
		void SetSizeToContent(const bool _fillToContent);
		void SetGradient(const ImageGradient& _gradient);
		void SetGradient(const bool _useGradient);
		virtual void Render(RenderWindow& _window) override;
	};
}