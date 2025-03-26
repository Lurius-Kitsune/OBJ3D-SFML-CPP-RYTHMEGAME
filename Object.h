#pragma once
#include "TransformableModifier.h"

class Object
{

public:
	FORCEINLINE virtual Drawable* GetDrawable() const = 0;
	
public:
	virtual ~Object() {};
};