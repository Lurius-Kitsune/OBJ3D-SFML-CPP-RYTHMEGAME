#include "ProgressBarWidget.h"
#include "TextureManager.h"
#include "HUD.h"

UI::ProgressBarWidget::ProgressBarWidget(const ProgressType& _type, const RectangleShapeData& _data,
    const string _name, const float _maxValue, const RenderType& _renderType)
    : ImageWidget(_name, _data,_renderType)
{
    type = _type;
    foreground = new ImageWidget(_name + "Foreground", _data, _renderType);
    size = _data.size;
    UpdateOriginAndPosition(size);
    maxValue = _maxValue;
    currentValue = 0;
}

UI::ProgressBarWidget::~ProgressBarWidget()
{
    delete foreground;
}

void UI::ProgressBarWidget::UpdateOriginAndPosition(const Vector2f& _size)
{
	Shape* _fgShape = foreground->GetMeshActor()->GetMesh()->GetShape()->GetDrawable();
    const Vector2f& _barPosition = GetPosition();
    const Vector2f& _originOffset = _fgShape->getOrigin() - GetOrigin();

    if (type == PT_LEFT)
    {
        _fgShape->setOrigin(_fgShape->getOrigin() - Vector2f(_size.x / 2.0f, 0.0f) - _originOffset);
        _fgShape->setPosition(_barPosition - Vector2f(_size.x / 2.0f, 0.0f));
    }
    else if (type == PT_RIGHT)
    {
        _fgShape->setOrigin(_fgShape->getOrigin() + Vector2f(_size.x / 2.0f, 0.0f) - _originOffset);
        _fgShape->setPosition(_barPosition + Vector2f(_size.x / 2.0f, 0.0f));
    }
    else if (type == PT_TOP)
    {
        _fgShape->setOrigin(_fgShape->getOrigin() - Vector2f(0.0f, _size.y / 2.0f) - _originOffset);
        _fgShape->setPosition(_barPosition - Vector2f(0.0f, _size.y / 2.0f));
    }
    else if (type == PT_BOTTOM)
    {
        _fgShape->setOrigin(_fgShape->getOrigin() + Vector2f(0.0f, _size.y / 2.0f) - _originOffset);
        _fgShape->setPosition(_barPosition + Vector2f(0.0f, _size.y / 2.0f));
    }
	else if (type == PT_CENTER)
	{
        foreground->SetOriginAtMiddle();
		_fgShape->setPosition(_barPosition + _originOffset);
	}
}

IntRect UI::ProgressBarWidget::MakeRect(const float _percent)
{
    const Texture* _bgTexture = foreground->GetMeshActor()->GetMesh()->GetShape()->GetDrawable()->getTexture();
    const Vector2f& _textureSize = Vector2f(_bgTexture->getSize());
    FloatRect _rect;

    if (type == PT_CENTER)
    {
        const Vector2f& _position = Vector2f((_textureSize.x - _percent * _textureSize.x) / 2.0f,
                                    (_textureSize.x - _percent * _textureSize.x) / 2.0f);
        const Vector2f& _size = Vector2f(_percent * _textureSize.x, _percent * _textureSize.y);
        _rect = FloatRect(_position, _size);
    }
    else if (type == PT_LEFT || type == PT_TOP)
    {
        const Vector2f& _position = Vector2f(0.0f, 0.0f);
        const Vector2f& _size = Vector2f(_textureSize.x * (type == PT_LEFT ? _percent : 1.0f),
                                           _textureSize.y * (type == PT_TOP ? _percent : 1.0f));
        _rect = FloatRect(_position, _size);
    }
    else if (type == PT_RIGHT)
    {
        const Vector2f& _position = Vector2f(_textureSize.x - _percent * _textureSize.x, 0.0f);
        const Vector2f& _size = Vector2f(_percent * _textureSize.x, _textureSize.y);
        _rect = FloatRect(_position, _size);
    }
    else if (type == PT_BOTTOM)
    {
        const Vector2f& _position = Vector2f(0.0f, _textureSize.y - _percent * _textureSize.y);
        const Vector2f& _size = Vector2f(_textureSize.x, _percent * _textureSize.y);
        _rect = FloatRect(_position, _size);
    }
    return IntRect(_rect);
}


void UI::ProgressBarWidget::Render(RenderWindow& _window)
{
    if (visibility == Hidden) return;
    Super::Render(_window);
	foreground->Render(_window);
}

void UI::ProgressBarWidget::Update()
{
    Shape * _fgShape = foreground->GetMeshActor()->GetMesh()->GetShape()->GetDrawable();

    const float _fillPercent = currentValue / maxValue;
    const IntRect& _rect = MakeRect(_fillPercent);
    _fgShape->setTextureRect(_rect);

    Vector2i _directions[] = {
        Vector2i(1, 1),
        Vector2i(1, 0),
        Vector2i(0, 1),
        Vector2i(1, 0),
        Vector2i(0, 1),
    };

    Vector2f _scale = _fgShape->getScale();
    if (_directions[type].x) _scale.x = _fillPercent;
    if (_directions[type].y) _scale.y = _fillPercent;
    _fgShape->setScale(_scale);
}