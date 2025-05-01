#pragma once
#include "LabelWidget.h"
namespace UI
{
    class FloatingLabelWidget : public LabelWidget
    {
        float  moveSpeed = -30;
		float fadeSpeed = 0.01f;
    public:
        FloatingLabelWidget(Level* _level, const string& _text = "Unknown", const string& _name = "Label", const RenderType& _type = Screen);
		virtual ~FloatingLabelWidget() = default;

    public:
        virtual void Render(RenderWindow& _window) override;
 
    };
}

