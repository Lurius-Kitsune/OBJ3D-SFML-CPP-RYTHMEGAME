#pragma once
#include "CoreMinimal.h"


class Actor;

struct BoundsData
{
	Vector2f position;

	BoundsData();
	BoundsData(const Vector2f& _position);
	virtual Vector2f GetPosition() const = 0;
};

struct RectangleBoundsData : public BoundsData
{
	Vector2f size;
	Angle rotation;

	RectangleBoundsData();
	RectangleBoundsData(const Vector2f& _position, const Vector2f& _size, const Angle& _rotation);
	RectangleBoundsData(const FloatRect& _rect, const Angle& _rotation);

	virtual Vector2f GetPosition() const override
	{
		return position;
	}
};

struct CircleBoundsData : public BoundsData
{
	float radius;
	int pointsCount;

	CircleBoundsData();
	CircleBoundsData(const float _radius, const Vector2f& _position, const int _pointsCount = 30);

	virtual Vector2f GetPosition() const override
	{
		return position;
	}
};

class Bounds
{
	BoundsData* data;

public:
	FORCEINLINE void SetBoundsData(BoundsData* _data)
	{
		delete data;
		data = nullptr;
		data = _data;
	}

	FORCEINLINE void SetPosition(const Vector2f& _position)
	{
		data->position = _position;
	}
	FORCEINLINE void SetSize(const Vector2f& _size)
	{
		if (RectangleBoundsData* _data = Cast<RectangleBoundsData>(data))
		{
			_data->size = _size;
			return;
		}
		if (CircleBoundsData* _data = Cast<CircleBoundsData>(data))
		{
			_data->radius *= _size.x;
		}
	}
	FORCEINLINE void MultiplieSize(const Vector2f& _factor)
	{
		if (RectangleBoundsData* _data = Cast<RectangleBoundsData>(data))
		{
			_data->size.x *= _factor.x;
			_data->size.y *= _factor.y;
			return;
		}
		if (CircleBoundsData* _data = Cast<CircleBoundsData>(data))
		{
			_data->radius *= _factor.x;
		}
	}
	FORCEINLINE void SetRotation(const Angle& _rotation)
	{
		if (RectangleBoundsData* _data = Cast<RectangleBoundsData>(data)) _data->rotation = _rotation;
	}
	FORCEINLINE BoundsData* GetData() const
	{
		return data;
	}

public:
	Bounds() = default;
	Bounds(BoundsData* _data);
	Bounds(const Bounds& _bounds);

private:
	bool Contains(const Vector2f& _point, RectangleBoundsData* _data) const;
	bool Contains(const Vector2f& _point, CircleBoundsData* _data) const;

	#pragma region Utilities

	vector<Vector2f> GetPoints() const;
	vector<Vector2f> GetPoints(RectangleBoundsData* _data) const;
	vector<Vector2f> GetPoints(CircleBoundsData* _data) const;

	Vector2f Around(Vector2f _point, RectangleBoundsData* _data) const;
	Vector2f Around(Vector2f _point, const float _degrees, CircleBoundsData* _data) const;

	Vector2f GetMinX(const vector<Vector2f>& _points) const;
	Vector2f GetMinY(const vector<Vector2f>& _points) const;
	Vector2f GetMaxX(const vector<Vector2f>& _points) const;
	Vector2f GetMaxY(const vector<Vector2f>& _points) const;

	#pragma endregion

	#pragma region Checks

	bool CheckIfInTheDownLeftCorner(const Vector2f& _point, const float _bottomX, const float _leftY) const;
	bool CheckIfInTheDownRightCorner(const Vector2f& _point, const float _bottomX, const float _rightY) const;
	bool CheckIfInTheTopRightCorner(const Vector2f& _point, const float _topX, const float _rightY) const;
	bool CheckIfInTheTopLeftCorner(const Vector2f& _point, const float _topX, const float _leftY) const;

	bool CheckIfInUnderTheDownLeftTangent(const Vector2f& _point, const Vector2f& _bottom, const Vector2f& _left) const;
	bool CheckIfInUnderTheDownRightTangent(const Vector2f& _point, const Vector2f& _bottom, const Vector2f& _right) const;
	bool CheckIfInAboveTheTopRightTangent(const Vector2f& _point, const Vector2f& _top, const Vector2f& _right) const;
	bool CheckIfInAboveTheTopLeftTangent(const Vector2f& _point, const Vector2f& _top, const Vector2f& _left) const;

	#pragma endregion

public:
	void UpdateBounds(Actor* _actor);
	bool Contains(const Vector2f& _point) const;
	Bounds* FindIntersections(Bounds* _other) const;
};