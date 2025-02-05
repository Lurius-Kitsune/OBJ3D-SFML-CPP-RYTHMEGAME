#include "HorizontalBox.h"
#include "Level.h"

HorizontalBox::HorizontalBox(float _posX, const float _posY, const u_int& _marging, const u_int& _count, const string& _path, const Vector2f& _size)
{
	spacing = 0;
	CreateHorizontalBox(_posX, _posY, _marging, _count, _path, _size, spacing);
}

u_int HorizontalBox::ComputeSpacing(float _sizeX, const u_int& _count, const Vector2f& _size)
{
	float _totalSpace = _size.x - _sizeX * _count;
	const u_int _numbreOfSpacing = _count - 1;
	float _finalSpacing;
	if (_numbreOfSpacing == 0)
	{
		_finalSpacing = _totalSpace;
	}
	else
	{
		_finalSpacing = _totalSpace / _numbreOfSpacing;
	}
	return _finalSpacing;
}

void HorizontalBox::CreateHorizontalBox(float _posX, const float _posY, const u_int& _marging, const u_int& _count, const string& _path, const Vector2f& _size, float _spacing)
{
	float _sizeX = _size.x / _count - _marging;
	_spacing = ComputeSpacing(_sizeX, _count, _size);

	for (u_int _index = 0; _index < _count; _index++)
	{
		MeshActor* _boxes = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_sizeX, _size.y), _path)));
		_boxes->SetPosition(Vector2f(_posX, _posY));
		_posX += _sizeX + _spacing;
	}
}