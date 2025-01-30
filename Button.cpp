#include "Button.h"
#include "RenderType.h"

UI::Button::Button(const string& _name, const RenderType& _type, Track* _track) : UI::Widget(_name, _type)
{
	isSelected = false;
	border = new Image("Border", RectangleShapeData({ 300.0f, 64.0f }, "Background"));
	icon = new Image("Icon", RectangleShapeData({64.0f, 64.0f}, "Background"));
	title = new Label(_track->GetTitle(), Screen, "Test", TTF);
	artist = new Label(_track->GetArtist(), Screen, "Test", TTF);
	duration = new Label("Duration", Screen, "Test", TTF);
	difficulty = new Label("Difficulty", Screen, "Test", TTF);
}

void UI::Button::Render(RenderWindow& _window)
{
	/*if (visibility == Hidden) return; //TODO
	_window.draw(*border->GetDrawable());
	_window.draw(*icon->GetDrawable());
	_window.draw(*title->GetDrawable());
	_window.draw(*artist->GetDrawable());
	_window.draw(*duration->GetDrawable());
	_window.draw(*difficulty->GetDrawable());*/
}
