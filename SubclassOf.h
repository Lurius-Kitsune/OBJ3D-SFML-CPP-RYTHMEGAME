#pragma once
#include "Macro.h"

template <typename T>
class SubclassOf
{
	T* objectRef;

public:
	FORCEINLINE T GetObject() const
	{
		return *objectRef;
	}

public:
	SubclassOf(const T& _objectRef)
	{
		objectRef = new T(_objectRef);
	}
	SubclassOf(const T* _objectRef)
	{
		objectRef = new T(*_objectRef);
	}
	SubclassOf(const SubclassOf<T>& _other)
	{
		objectRef = new T(*_other.objectRef);
	}
	~SubclassOf()
	{
		delete objectRef;
	}
};