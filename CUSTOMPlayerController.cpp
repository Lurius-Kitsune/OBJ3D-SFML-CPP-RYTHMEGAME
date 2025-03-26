#include "CUSTOMPlayerController.h"
#include "CUSTOMPawn.h"

CUSTOMPlayerController::CUSTOMPlayerController(Level* _level, const string& _name) : PlayerController(_level, _name)
{

}

CUSTOMPlayerController::CUSTOMPlayerController(const PlayerController& _other) : PlayerController(_other)
{

}

Pawn* CUSTOMPlayerController::GetPawnRef() const
{
    return new CUSTOMPawn(level);
}