#pragma once
#include "CoreMinimal.h"

namespace UI
{
	class Slot
	{
		VertexArray debugFrame;
	protected:
		bool debugMode;
		Vector2f position;
		Vector2f size;
		class PanelWidget* parent;
		class Widget* content;

	public:
		//Get the Parent of the Slot
		FORCEINLINE PanelWidget* GetParent() const
		{
			return parent;
		}
		//Get the Widget containing in the Slot
		FORCEINLINE Widget* GetContent() const
		{
			return content;
		}
		FORCEINLINE Vector2f GetPosition() const
		{
			return position;
		}
		//Get the Size of the Slot
		FORCEINLINE Vector2f GetSize() const
		{
			return size;
		}
		//Set the Size of the Slot
		FORCEINLINE void SetSize(const Vector2f& _size)
		{
			size = _size;
			if (debugMode)
			{
				UpdateDebugFrame();
			}
		}
		FORCEINLINE void SetPosition(const Vector2f& _position)
		{
			position = _position;
			if (debugMode)
			{
				UpdateDebugFrame();
			}
		}
		//Display a Gradient Box to see the Slot
		//Warning : Doesn't work with Rotation
		//Info : DebugMode can cause FPS drop
		FORCEINLINE void SetDebugMode(const bool _status)
		{
			UpdateDebugMode(_status);
		}
		FORCEINLINE virtual bool GetDebugMode() const
		{
			return debugMode;
		}

	public:
		Slot(PanelWidget* _parent, Widget* _content);
		virtual ~Slot() = default;

	public:
		void RenderDebugFrame(RenderWindow& _window);
		void UpdateDebugFrame();
		void UpdateDebugMode(const bool _status);
	};
}