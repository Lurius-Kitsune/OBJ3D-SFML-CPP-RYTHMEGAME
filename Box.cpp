#include "Box.h"

using namespace UI;

Box::Box(const BoxData& _data) : Widget("Widget")
{
	widgets = vector<Widget*>();
	data = _data;
}

void Box::Update()
{

}