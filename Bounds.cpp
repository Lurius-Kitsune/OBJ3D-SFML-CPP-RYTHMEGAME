#include "Bounds.h"
#include "MeshComponent.h"
#include "Actor.h"

BoundsData::BoundsData()
{
	position = Vector2f();
}

BoundsData::BoundsData(const Vector2f& _position)
{
	position = _position;
}


RectangleBoundsData::RectangleBoundsData()
{
	size = Vector2f();
	rotation = Angle();
}


RectangleBoundsData::RectangleBoundsData(const Vector2f& _position, const Vector2f& _size, const Angle& _rotation) : BoundsData(_position)
{
	size = _size;
	rotation = _rotation;
}

RectangleBoundsData::RectangleBoundsData(const FloatRect& _rect, const Angle& _rotation) : BoundsData(_rect.position)
{
	size = _rect.size;
	rotation = _rotation;
}


CircleBoundsData::CircleBoundsData()
{
	radius = 0.0f;
	position = Vector2f();
	pointsCount = 0;
}

CircleBoundsData::CircleBoundsData(const float _radius, const Vector2f& _position, const int _pointsCount) : BoundsData(_position)
{
	radius = _radius;
	pointsCount = _pointsCount;
}


Bounds::Bounds(BoundsData* _data)
{
	data = _data;
}

Bounds::Bounds(const Bounds& _bounds)
{
	data = _bounds.data;
}


bool Bounds::Contains(const Vector2f& _point, RectangleBoundsData* _data) const
{
	if (!((int)_data->rotation.asDegrees() % 90))
	{
		return FloatRect(_data->position - _data->size / 2.0f, _data->size).contains(_point);
	}

	const vector<Vector2f>& _cornerPoints = GetPoints();

	// left = rectangle corner with lowest "x"
	const Vector2f& _left = GetMinX(_cornerPoints);
	// right = rectangle corner with highest "x"
	const Vector2f& _right = GetMaxX(_cornerPoints);
	// top = rectangle corner with highest "y"
	const Vector2f& _top = GetMaxY(_cornerPoints);
	// _bottom = rectangle corner with lowest "y"
	const Vector2f& _bottom = GetMinY(_cornerPoints);

	if (_point.x < _left.x)   return false;
	if (_point.x > _right.x)  return false;
	if (_point.y > _top.y)    return false;
	if (_point.y < _bottom.y) return false;

	if (CheckIfInTheDownLeftCorner(_point, _bottom.x, _left.y))
	{
		if (CheckIfInUnderTheDownLeftTangent(_point, _bottom, _left))
		{
			return false;
		}
	}

	if (CheckIfInTheDownRightCorner(_point, _bottom.x, _right.y))
	{
		if (CheckIfInUnderTheDownRightTangent(_point, _bottom, _right))
		{
			return false;
		}
	}

	if (CheckIfInTheTopRightCorner(_point, _top.x, _right.y))
	{
		if (CheckIfInAboveTheTopRightTangent(_point, _top, _right))
		{
			return false;
		}
	}

	if (CheckIfInTheTopLeftCorner(_point, _top.x, _left.y))
	{
		if (CheckIfInAboveTheTopLeftTangent(_point, _top, _left))
		{
			return false;
		}
	}

	return true;
}

bool Bounds::Contains(const Vector2f& _point, CircleBoundsData* _data) const
{
	return Distance(_point, _data->position) <= _data->radius;
}

#pragma region Utilities

vector<Vector2f> Bounds::GetPoints() const
{
	if (RectangleBoundsData* _data = Cast<RectangleBoundsData>(data)) return GetPoints(_data);
	if (CircleBoundsData* _data = Cast<CircleBoundsData>(data)) return GetPoints(_data);
	return vector<Vector2f>();
}

vector<Vector2f> Bounds::GetPoints(RectangleBoundsData* _data) const
{
	return vector<Vector2f>
	{
		Around(_data->position + _data->size / 2.0f, _data),
		Around(_data->position - _data->size / 2.0f, _data),
		Around(Vector2f(_data->position.x + _data->size.x / 2.0f, _data->position.y - _data->size.y / 2.0f), _data),
		Around(Vector2f(_data->position.x - _data->size.x / 2.0f, _data->position.y + _data->size.y / 2.0f), _data)
	};
}

vector<Vector2f> Bounds::GetPoints(CircleBoundsData* _data) const
{
	Vector2f _firstPoint = Vector2f(_data->position.x, _data->position.y + _data->radius);
	vector<Vector2f> _finalVector = { _firstPoint };
	const int _pointsCount = _data->pointsCount;
	const int _pointsUse = _pointsCount > 15 ? 15 : _pointsCount;

	for (int _index = 1; _index < _pointsUse; _index++)
	{
		_finalVector.push_back(Around(_firstPoint, 360.0f / _pointsUse * (float)_index, _data));
	}

	return _finalVector;
}


Vector2f Bounds::Around(Vector2f _point, RectangleBoundsData* _data) const
{
	const float _angle = _data->rotation.asRadians();

	_point.x -= _data->position.x;
	_point.y -= _data->position.y;
	const float _x = (_point.x * cosf(_angle) - _point.y * sinf(_angle)) + _data->position.x;
	const float _y = (_point.x * sinf(_angle) + _point.y * cosf(_angle)) + _data->position.y;

	return Vector2f(_x, _y);
}

Vector2f Bounds::Around(Vector2f _point, const float _degrees, CircleBoundsData* _data) const
{
	const float _angle = DegToRad(_degrees);

	_point.x -= _data->position.x;
	_point.y -= _data->position.y;
	const float _x = (_point.x * cosf(_angle) - _point.y * sinf(_angle)) + _data->position.x;
	const float _y = (_point.x * sinf(_angle) + _point.y * cosf(_angle)) + _data->position.y;

	return Vector2f(_x, _y);
}


Vector2f Bounds::GetMinX(const vector<Vector2f>& _points) const
{
	if (_points.empty()) return Vector2f();

	Vector2f _min = _points[0];
	for (Vector2f _point : _points)
	{
		if (_point.x < _min.x) _min = _point;
	}
	return _min;
}

Vector2f Bounds::GetMinY(const vector<Vector2f>& _points) const
{
	if (_points.empty()) return Vector2f();

	Vector2f _min = _points[0];
	for (Vector2f _point : _points)
	{
		if (_point.y < _min.y) _min = _point;
	}
	return _min;
}

Vector2f Bounds::GetMaxX(const vector<Vector2f>& _points) const
{
	if (_points.empty()) return Vector2f();

	Vector2f _max = _points[0];
	for (Vector2f _point : _points)
	{
		if (_point.x > _max.x) _max = _point;
	}
	return _max;
}

Vector2f Bounds::GetMaxY(const vector<Vector2f>& _points) const
{
	if (_points.empty()) return Vector2f();

	Vector2f _max = _points[0];
	for (Vector2f _point : _points)
	{
		if (_point.y > _max.y) _max = _point;
	}
	return _max;
}

#pragma endregion

#pragma region Checks

bool Bounds::CheckIfInTheDownLeftCorner(const Vector2f& _point, const float _bottomX, const float _leftY) const
{
	return _point.x <= _bottomX && _point.y <= _leftY;
}

bool Bounds::CheckIfInTheDownRightCorner(const Vector2f& _point, const float _bottomX, const float _rightY) const
{
	return _point.x >= _bottomX && _point.y <= _rightY;
}

bool Bounds::CheckIfInTheTopRightCorner(const Vector2f& _point, const float _topX, const float _rightY) const
{
	return _point.x >= _topX && _point.y >= _rightY;
}

bool Bounds::CheckIfInTheTopLeftCorner(const Vector2f& _point, const float _topX, const float _leftY) const
{
	return _point.x <= _topX && _point.y >= _leftY;
}


bool Bounds::CheckIfInUnderTheDownLeftTangent(const Vector2f& _point, const Vector2f& _bottom, const Vector2f& _left) const
{
	return (_point.y - _bottom.y) * (_bottom.x - _left.x) < (_left.y - _bottom.y) * (_bottom.x - _point.x);
}

bool Bounds::CheckIfInUnderTheDownRightTangent(const Vector2f& _point, const Vector2f& _bottom, const Vector2f& _right) const
{
	return (_point.y - _bottom.y) * (_right.x - _bottom.x) < (_right.y - _bottom.y) * (_point.x - _bottom.x);
}

bool Bounds::CheckIfInAboveTheTopRightTangent(const Vector2f& _point, const Vector2f& _top, const Vector2f& _right) const
{
	return (_top.y - _point.y) * (_right.x - _top.x) < (_top.y - _right.y) * (_point.x - _top.x);
}

bool Bounds::CheckIfInAboveTheTopLeftTangent(const Vector2f& _point, const Vector2f& _top, const Vector2f& _left) const
{
	return (_top.y - _point.y) * (_top.x - _left.x) < (_top.y - _left.y) * (_top.x - _point.x);
}

#pragma endregion

void Bounds::UpdateBounds(Actor* _actor)
{
	if (MeshComponent* _meshComponent = _actor->GetComponent<MeshComponent>())
	{
		const Vector2f& _pos = _meshComponent->GetOwner()->GetPosition();
		if (_meshComponent->GetShape()->GetData().type == SOT_CIRCLE)
		{
			const float _radius = _meshComponent->GetShape()->GetData().data.circleData->radius;
			const u_int& _pointCount = CAST(u_int, _meshComponent->GetShape()->GetData().data.circleData->pointCount);
			SetBoundsData(new CircleBoundsData(_radius, _pos, _pointCount));
		}
		if (_meshComponent->GetShape()->GetData().type == SOT_RECTANGLE)
		{

			const Vector2f& _size = _meshComponent->GetShape()->GetData().data.rectangleData->size;
			const Angle& _rotation = _meshComponent->GetOwner()->GetRotation();
			SetBoundsData(new RectangleBoundsData({ _pos, _size }, _rotation));
		}
	}
}

bool Bounds::Contains(const Vector2f& _point) const
{
	if (RectangleBoundsData* _data = Cast<RectangleBoundsData>(data)) return Contains(_point, _data);
	if (CircleBoundsData* _data = Cast<CircleBoundsData>(data)) return Contains(_point, _data);
	return false;
}

Bounds* Bounds::FindIntersections(Bounds* _other) const
{
	const vector<Vector2f>& _cornerPoints = GetPoints();

	for (const Vector2f& _point : _cornerPoints)
	{
		if (_other->Contains(_point)) return _other;
	}

	return nullptr;
}