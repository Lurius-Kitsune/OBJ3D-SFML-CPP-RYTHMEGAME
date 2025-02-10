#pragma once
#include "Level.h"

class CUSTOMLevel : public Level
{
public:
	CUSTOMLevel(const string& _name);

protected:
	virtual void InitLevel() override;
};