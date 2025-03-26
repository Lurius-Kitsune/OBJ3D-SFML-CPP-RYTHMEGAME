#pragma once
#include "ImageWidget.h"
#include "PlayerController.h"
#include "InputManager.h"

namespace UI
{
	struct CallbackData
	{
		vector<function<void()>> onClickActions;
		vector<function<void()>> onRealeaseActions;
		vector<function<void()>> onHoverActions;
		vector<function<void()>> onUnhoversActions;
		vector<function<void(const Vector2f&)>> onDragActions;
	};

	class ButtonWidget : public ImageWidget
	{
		bool isPressed;
		bool isHovered;
		unique_ptr<CallbackData> callbackData;
		Input::InputManager* inputManager;

	public:
		FORCEINLINE FloatRect GetGlobalBox() const
		{
			return image->GetShape()->GetDrawable()->getGlobalBounds();
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
		FORCEINLINE virtual void BindOnDragAction(const function<void(const Vector2f&)>& _action)
		{
			callbackData.get()->onDragActions.push_back(_action);
		}
		#pragma endregion

	public:
		ButtonWidget(Level* _level, const RectangleShapeData& _data, const string _name = "Button", const RenderType& _renderType = Screen);

	public:
		virtual void OnClick();
		virtual void OnRelease();
		virtual void OnHover();
		virtual void OnUnhover();
		virtual void OnDrag(const Vector2f& _mousePosition);
		virtual void Render(RenderWindow& _window) override;
		virtual void BindActions(Input::InputManager& _inputManager) override;
	};
};