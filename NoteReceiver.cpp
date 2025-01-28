#include "NoteReceiver.h"
#include "GameManager.h"
#include "MargeurythmeGame.h"


NoteReceiver::NoteReceiver(const RectangleShapeData& _data)
: RectangleActor(_data)
{
	for (u_int _i = 0; _i > 4; _i++)
	{
		// TO DO AddNoteDirector
	}
}

NoteReceiver::NoteReceiver(const NoteReceiver& _other)
: RectangleActor(_other)
{
}

void NoteReceiver::InitInput()
{
	M_INPUT.BindAction([&]() { CheckInput(Code::Left); }, Code::Left);
}

void NoteReceiver::CheckInput(const Code& _code)
{
	LOG(Display, "PRESSED " + M_INPUT.KeyCodeToString(_code));
	//Question : comment detecter les flêche dans cette note


}
