#pragma once
#include "TransformableModifier.h"

class Object : public ITransformableModifier
{

public:
	FORCEINLINE virtual Drawable* GetDrawable() const = 0;
	
public:
	virtual ~Object() {};
};