#pragma once
#include "Widget.h"

namespace UI
{
	class PanelWidget : public Widget
	{
		VertexArray debugFrame;
	protected:
		bool debugMode;
		int maxChild;
		Vector2f size;

	protected:
		FORCEINLINE bool RegisterSlot(Widget* _widget)
		{
			if (!CanAddMoreChildren()) return false;

			Actor::AddChild(_widget, AT_KEEP_RELATIVE);
			return true;
		}

	public:
		//Adds a new child widget to the container.
		FORCEINLINE virtual bool AddChild(Widget* _widget)
		{
			if (!RegisterSlot(_widget)) return false;

			_widget->AddSlot(new Slot(this, _widget));
			return true;
		}

		//Returns true if the panel can accept another child widget.
		FORCEINLINE bool CanAddMoreChildren() const
		{
			return GetChildrenCount() < maxChild;
		}

		//Returns true if the panel supports more than one child.
		FORCEINLINE bool CanHaveMultipleChildren() const
		{
			return maxChild > 1;
		}

		//Gets the index of a specific child widget (-1 if not)
		FORCEINLINE int GetChildIndex(Widget* _Widget) const
		{
			int _index = 0;
			for (Actor* _actor : GetChildren())
			{
				if (Widget* _widget = Cast<Widget>(_actor))
				{
					return _index;
				}
				_index++;
			}
			return -1;
		}

		//Gets number of child widgets in the container.
		FORCEINLINE int GetChildrenCount() const
		{
			return CAST(int, GetChildren().size());
		}

		//Get all Widget Children
		FORCEINLINE set<Widget*> GetChildren() const
		{
			set<Widget*> _widgets;
			for (Actor* _actor : Actor::GetChildren())
			{
				if (Widget* _widget = Cast<Widget>(_actor))
				{
					_widgets.insert(_widget);
				}
			}
			return _widgets;
		}

		//The slots in the widget holding the child widgets of this panel.
		FORCEINLINE set<Slot*> GetSlots() const
		{
			set<Slot*> _slots;
			for (Actor* _actor : GetChildren())
			{
				if (Widget* _widget = Cast<Widget>(_actor))
				{
					_slots.insert(_widget->GetSlot());
				}
			}
			return _slots;
		}

		//Return the Size of the Panel
		FORCEINLINE virtual Vector2f GetSize() const override
		{
			return size;
		}

		//Remove all child widgets from the panel widget.
		FORCEINLINE virtual void ClearChildren()
		{
			for (Actor* _actor : GetChildren())
			{
				if (Widget* _widget = Cast<Widget>(_actor))
				{
					RemoveChild(_widget);
				}
			}
		}

		//Returns true if there are any child widgets in the panel
		FORCEINLINE bool HasAnyChildren() const
		{
			return GetChildrenCount() > 0;
		}

		//Returns true if panel contains this widget
		FORCEINLINE bool HasChild(Widget* _widget)
		{
			return GetChildren().contains(_widget);
		}

		//Removes a specific widget from the container.
		template <typename Type, typename ...Args, IS_BASE_OF(Widget, Type)>
		FORCEINLINE void RemoveChild(Type* _widget)
		{
			_widget->RemoveSlot();
			Actor::RemoveChild(_widget);
		}

		//Removes a child by it's index.
		FORCEINLINE void RemoveChildAtIndex(const int _index)
		{
			set<Actor*>::const_iterator _it = Actor::GetChildren().begin();
			advance(_it, _index);
			RemoveChild(Cast<Widget>(*_it));
		}

		//Display a Gradient Box to see the panel
		//Warning : Doesn't work with Rotation
		//Info : DebugMode can cause FPS drop
		FORCEINLINE void SetDebugMode(const bool _status)
		{
			debugMode = _status;
		}

		//Set the Size of the Panel
		FORCEINLINE virtual void SetSize(const Vector2f& _size)
		{
			size = _size;

			if (debugMode)
			{
				UpdateDebugFrame();
			}
		}

		//Set the Size of the Panel but with a multiplicator (ex : 0.5 = half the Initial Size)
		FORCEINLINE virtual void SetScale(const Vector2f& _scale)
		{
			Super::SetScale(_scale);

			SetSize(Vector2f(size.x * _scale.x, size.y * _scale.y));

			if (debugMode)
			{
				UpdateDebugFrame();
			}
		}

		FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
		{
			Super::SetPosition(_position);

			if (debugMode)
			{
				UpdateDebugFrame();
			}
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			Super::Move(_offset);

			if (debugMode)
			{
				UpdateDebugFrame();
			}
		}

	public:
		PanelWidget(Level* _level, const string& _name = "Panel", const RenderType& _type = Screen);
		virtual ~PanelWidget()
		{
			LOG(Display, "Destruction PanelWidget !");
		}

	private:
		void UpdateDebugFrame();

	public:
		virtual void Render(RenderWindow& _window) override;
	};
}