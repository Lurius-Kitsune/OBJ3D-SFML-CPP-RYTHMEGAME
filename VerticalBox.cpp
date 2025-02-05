#include "VerticalBox.h"
#include "Level.h"

VerticalBox::VerticalBox(const float _posX, float _posY, const u_int _marging, const u_int& _count, const string& _path, const Vector2f& _size)
{
	spacing = 0;
	CreateVerticalBox(_posX, _posY, _marging, _count, _path, _size, spacing);
}

u_int VerticalBox::ComputeSpacing(float _sizeY, const u_int& _count, const Vector2f& _size)
{
	float _totalSpace = _size.y - _sizeY * _count;
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

void VerticalBox::CreateVerticalBox(const float _posX, float _posY, const u_int _marging, const u_int& _count, const string& _path, const Vector2f _size, float _spacing)
{
	float _sizeY = _size.y / _count - _marging;
	_spacing = ComputeSpacing(_sizeY, _count, _size);

	for (u_int _index = 0; _index < _count; _index++)
	{
		MeshActor* _boxes = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_size.x, _sizeY), _path)));
		_boxes->SetPosition(Vector2f(_posX, _posY));
		_posY += _sizeY + _spacing;
	}
}