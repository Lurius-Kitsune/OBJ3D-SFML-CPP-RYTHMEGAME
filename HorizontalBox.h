#pragma once
#include "CoreMinimal.h"
#include "Label.h"

using namespace UI;

class HorizontalBox
{
	float posX;
	float posY;
	float spacing;
	u_int marging;
	u_int count;
	Vector2f size;

public:
	HorizontalBox(float _posX, const float _posY, const u_int& _marging, const u_int& _count, const string& _path, const Vector2f& _size);

public:
	u_int ComputeSpacing(float _sizeX, const u_int& _count, const Vector2f& _size);
	void CreateHorizontalBox(float _posX, const float _posY, const u_int& _marging, const u_int& _count, const string& _path, const Vector2f& _size, float _spacing);
};