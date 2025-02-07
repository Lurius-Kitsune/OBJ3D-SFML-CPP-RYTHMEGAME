#pragma once
#include "Widget.h"
#include "MeshActor.h"
#include "TextureManager.h"
namespace UI
{
	struct Gradient
	{
		Color topLeft;
		Color topRight;
		Color bottomLeft;
		Color bottomRight;

		Gradient(const Color& _topLeft = Color(), const Color& _topRight = Color(),
			const Color& _bottomLeft = Color(), const Color& _bottomRight = Color())
		{
			topLeft = _topLeft;
			topRight = _topRight;
			bottomLeft = _bottomLeft;
			bottomRight = _bottomRight;
		}
	};

	class ImageWidget : public Widget
	{
		bool sizeToContent;
		Vector2f initialSize;
		VertexArray gradient;
		Gradient colorGradient;
	protected:
		MeshActor* image;

	public:
		FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
		{
			UpdatePosition(_position);
		}
		FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
		{
			Super::SetRotation(_rotation);
			image->SetRotation(_rotation);
		}
		FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
		{
			Super::SetScale(_scale);
			image->SetScale(_scale);
		}
		FORCEINLINE virtual void SetSize(const Vector2f _size)
		{
			UpdateSize(_size);
		}
		FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
		{
			Super::SetOrigin(_origin);
			image->SetOrigin(_origin);
		}
		FORCEINLINE virtual void SetOriginAtMiddle()
		{
			SetOrigin(image->GetMesh()->GetShape()->GetDrawable()->getGeometricCenter());
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			Super::Move(_offset);
			image->Move(_offset);
		}
		FORCEINLINE virtual void Rotate(const Angle& _angle) override
		{
			Super::Rotate(_angle);
			image->Rotate(_angle);
		}
		FORCEINLINE virtual void Scale(const Vector2f& _factor) override
		{
			Super::Scale(_factor);
			image->Scale(_factor);
		}
		FORCEINLINE virtual void SetFillColor(const Color& _color)
		{
			image->GetMesh()->GetShape()->GetDrawable()->setFillColor(_color);
		}
		FORCEINLINE virtual void SetOutline(const float _thickness, const Color& _color)
		{
			image->GetMesh()->GetShape()->GetDrawable()->setOutlineThickness(_thickness);
			image->GetMesh()->GetShape()->GetDrawable()->setOutlineColor(_color);
		}
		FORCEINLINE virtual Vector2f GetSize() const override
		{
			return image->GetMesh()->GetShape()->GetDrawable()->getLocalBounds().size;
		}
		FORCEINLINE virtual MeshActor* GetMeshActor() const
		{
			return image;
		}
		FORCEINLINE virtual void SetTexture(const string& _path, const TextureExtensionType& _type = PNG)
		{
			if (_path.empty())
			{
				M_TEXTURE.Load(image->GetMesh()->GetShape(), "White", PNG);
			}
			else
			{
				M_TEXTURE.Load(image->GetMesh()->GetShape(), _path, _type);
			}
		}
		FORCEINLINE virtual void SetTransparency(const u_int& _alpha)
		{
			SetFillColor(Color(GetFillColor().r, GetFillColor().g, GetFillColor().b, _alpha));
		}
		FORCEINLINE virtual Color GetFillColor() const
		{
			return image->GetMesh()->GetShape()->GetDrawable()->getFillColor();
		}

	public:
		ImageWidget(const string& _name, const RectangleShapeData& _data, const RenderType& _type = Screen);
		ImageWidget(const string& _name, const CircleShapeData& _data, const RenderType& _type = Screen);
		virtual ~ImageWidget() override;
	private:
		void UpdateGradient();
		void UpdatePosition(const Vector2f& _position);
		void UpdateSize(const Vector2f& _size);

	public:
		void SetSizeToContent(const bool _fillToContent);
		void SetGradient(const Gradient& _gradient);
		virtual void Render(RenderWindow& _window) override;
	};
}

