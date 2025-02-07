#pragma once
#include "Box.h"

class VerticalBox : public Box
{

public:
	VerticalBox() = default;
	VerticalBox(const BoxData& _data);

public:
	virtual void Update() override;

	virtual void Render(RenderWindow& _window) override {};
};