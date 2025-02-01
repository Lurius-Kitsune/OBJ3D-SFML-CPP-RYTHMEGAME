#include "Canvas.h"

UI::Canvas::Canvas(const string& _name, const RenderType& _type) : Widget(_name, _type)
{
	allWidgets = set<Widget*>();
}

void UI::Canvas::Render(RenderWindow& _window)
{
	
}

void UI::Canvas::Construct()
{
	Super::Construct();
	for (Actor* _actor : allWidgets)
	{
		if (Widget* _widget = Cast<Widget>(_actor))
		{
			_widget->Construct();
		}
	}
}

void UI::Canvas::UpdateWidgets()
{
	for (Widget* _widget : allWidgets)
	{
		_widget->SetPosition(GetPosition() + offSet[_widget]);
		_widget->SetRotation(_widget->GetRotation() + GetRotation());
		_widget->SetScale(Vector2f(_widget->GetScale().x * GetScale().x,
		_widget->GetScale().y * GetScale().y));
	}
}