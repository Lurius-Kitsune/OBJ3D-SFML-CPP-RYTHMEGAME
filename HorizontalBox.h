#pragma once
#include "Box.h"

class HorizontalBox : public Box
{
	
public:
	HorizontalBox() = default;
	HorizontalBox(const BoxData& _data);

public:
	virtual void Update() override;
	
	virtual void Render(RenderWindow& _window) override {};
};