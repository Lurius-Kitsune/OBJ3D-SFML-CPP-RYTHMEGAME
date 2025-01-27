#pragma once
#include "RectangleActor.h"
#include "InputManager.h"
class NoteReceiver : public RectangleActor
{
	// Position des 4 point
	Vector2f leftArrow;
	Vector2f downArrow;
	Vector2f upArrow;
	Vector2f rightArrow;

public:
	NoteReceiver(const RectangleShapeData& _data);
	NoteReceiver(const NoteReceiver& _other);

public:
	void InitInput();

private:
	void CheckInput(const Code& _code);
};

