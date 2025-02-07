#pragma once
#include "ImageWidget.h"
#include "LabelWidget.h"
using MouseMouvement = Event::MouseMoved;
namespace UI
{
	struct CallbackData
	{
		vector<function<void()>> onClickActions;
		vector<function<void()>> onRealeaseActions;
		vector<function<void()>> onHoverActions;
		vector<function<void()>> onUnhoversActions;
		vector<function<void(const MouseMouvement*)>> onDragActions;
	};

	class ButtonWidget : public ImageWidget
	{
		unique_ptr<CallbackData> callbackData;
		bool isHovered;
		bool isPressed;

	public:
		FORCEINLINE FloatRect GetGlobalBox() const
		{
			return image->GetHitbox();
		}

		#pragma region ButtonWidget
		FORCEINLINE void SetIsHovered(const bool _isHovered) 
		{ 
			isHovered = _isHovered; 
		}
		FORCEINLINE void SetIsPressed(const bool _isPressed) 
		{ 
			isPressed = _isPressed; 
		}
		FORCEINLINE bool GetIsHovered() const 
		{ 
			return isHovered; 
		}
		FORCEINLINE bool GetIsPressed() const 
		{ 
			return isPressed; 
		}

		FORCEINLINE virtual void BindOnClickAction(const function<void()>& _action)
		{
			callbackData.get()->onClickActions.push_back(_action);
		}
		FORCEINLINE virtual void BindOnReleaseAction(const function<void()>& _action)
		{
			callbackData.get()->onRealeaseActions.push_back(_action);
		}
		FORCEINLINE virtual void BindOnHoverAction(const function<void()>& _action)
		{
			callbackData.get()->onHoverActions.push_back(_action);
		}
		FORCEINLINE virtual void BindOnUnhoverAction(const function<void()>& _action)
		{
			callbackData.get()->onUnhoversActions.push_back(_action);
		}
		FORCEINLINE virtual void BindOnDragAction(const function<void(const MouseMouvement*)>& _action)
		{
			callbackData.get()->onDragActions.push_back(_action);
		}
		#pragma endregion
	public:
		ButtonWidget(const string _name, const RectangleShapeData& _data, const RenderType& _renderType);
		virtual ~ButtonWidget();

	public:
		virtual void OnClick();
		virtual void OnRelease();
		virtual void OnHover();
		virtual void OnUnhover();
		virtual void OnDrag(const MouseMouvement* _mouseMovement);
		virtual void Render(RenderWindow& _window) override;
	};
};
