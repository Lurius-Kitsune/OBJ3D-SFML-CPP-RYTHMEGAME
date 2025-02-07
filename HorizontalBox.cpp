#include "HorizontalBox.h"
#include "Level.h"

HorizontalBox::HorizontalBox(const BoxData& _data) : Box(_data)
{
	if (data.spaceBetween == -1.0f)
	{
		data.spaceBetween = _data.size.x * 0.05f;
	}
}

void HorizontalBox::Update()
{
	Super::Update();

	const Vector2f& _totalSize = GetSize();
	const u_int& _totalElement = GetElementCount();
	const float _spaceX = (_totalSize.x - data.spaceBetween * (_totalElement - 1)) / _totalElement;
	float _allElementsSize = 0.0f;
	for (Widget* _widget : widgets)
	{
		const Vector2f& _size = _widget->GetSize();
		const float _newScaleX = _spaceX / _size.x;
		const float _newScaleY = _totalSize.y / _size.y;
		const float _newScale = min(_newScaleX, _newScaleY);
		_widget->SetScale(Vector2f(_newScale, _newScale));
		_allElementsSize += _size.x * _newScale;
	}

	_allElementsSize += data.spaceBetween * (_totalElement - 1);

	float _currentX = (_totalSize.x - _allElementsSize) / 2.0f;
	for (Widget* _widget : widgets)
	{
		const float _computeSizeX = _widget->GetSize().x * _widget->GetScale().x;
		_widget->SetPosition(Vector2f(_currentX, _widget->GetPosition().y));
		_currentX += _computeSizeX + data.spaceBetween;
	}
}