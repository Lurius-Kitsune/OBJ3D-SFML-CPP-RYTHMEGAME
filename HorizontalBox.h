#pragma once
#include "Box.h"

namespace UI
{
	class HorizontalBox : public Box
	{
	public:
		HorizontalBox(Level* _level, const BoxData& _data);

	public:
		virtual void Update() override;
		virtual void Render(RenderWindow& _window) override {};
	};
}