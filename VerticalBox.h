#pragma once
#include "Box.h"

namespace UI
{
	class VerticalBox : public Box
	{
	public:
		VerticalBox(Level* _level, const BoxData& _data);

	public:
		virtual void Update() override;
		virtual void Render(RenderWindow& _window) override {};
	};
}