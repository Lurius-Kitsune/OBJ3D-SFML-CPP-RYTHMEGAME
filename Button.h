#pragma once
#include "Widget.h"

#include "Image.h"
#include "Label.h"
#include "Song.h"

namespace UI
{
	class Button : public Widget
	{
		bool isSelected;
		Image* border;
		Image* icon;
		Label* title;
		Label* artist;
		Label* duration;
		Label* difficulty;

	public:
		Button(const string& _name, const RenderType& _type, Song* _song);

	public:
		virtual void Render(RenderWindow& _window) override;
	};
}


