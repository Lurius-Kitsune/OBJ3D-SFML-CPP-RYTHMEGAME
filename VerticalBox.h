#pragma once
#include "CoreMinimal.h"
#include "Widget.h"

using namespace UI;

class VerticalBox
{
	float posX;
	float posY;
	float spacing;
	u_int marging;
	u_int count;
	string path;
	Vector2f size;

public:
	VerticalBox(const float _posX, float _posY, const u_int _marging, const u_int& _count, const string& _path, const Vector2f& _size);

public:
	u_int ComputeSpacing(float _sizeY, const u_int& _count, const Vector2f& _size);
	void CreateVerticalBox(const float _posX, float _posY, const u_int _marging,const u_int& _count, const string& _path, const Vector2f _size, float _spacing);
};

