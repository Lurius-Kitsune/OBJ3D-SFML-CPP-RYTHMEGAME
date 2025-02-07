#include "VerticalBox.h"
#include "Level.h"

VerticalBox::VerticalBox(const BoxData& _data) : Box(_data)
{
	if (data.spaceBetween == -1.0f)
	{
		data.spaceBetween = _data.size.y * 0.05f;
	}
}

void VerticalBox::Update()
{
	Super::Update();

	const Vector2f& _totalSize = GetSize();
	const u_int& _totalElement = GetElementCount();
	const float _spaceY = (_totalSize.y - data.spaceBetween * (_totalElement - 1)) / _totalElement;
	float _allElementsSize = 0.0f;
	for (Widget* _widget : widgets)
	{
		const Vector2f& _size = _widget->GetSize();
		const float _newScaleX = _totalSize.x / _size.x;
		const float _newScaleY = _spaceY / _size.y;
		const float _newScale = min(_newScaleX, _newScaleY);
		_widget->SetScale(Vector2f(_newScale, _newScale));
		_allElementsSize += _size.y * _newScale;
	}
	_allElementsSize += data.spaceBetween * (_totalElement - 1);

	float _currentY = (_totalSize.y - _allElementsSize) / 2.0f;
	for (Widget* _widget : widgets)
	{
		const float _computeSizeY = _widget->GetSize().y * _widget->GetScale().y;
		_widget->SetPosition(Vector2f(_widget->GetPosition().x, _currentY));
		_currentY += _computeSizeY + data.spaceBetween;
	}
}