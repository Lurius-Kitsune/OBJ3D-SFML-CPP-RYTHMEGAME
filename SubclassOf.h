#pragma once
#include "Macro.h"

template <typename T>
class SubclassOf
{
	T* objectRef = nullptr;

public:
	FORCEINLINE T GetObject() const
	{
		return *objectRef;
	}

public:
	SubclassOf() = default;
	SubclassOf(const T& _objectRef)
	{
		objectRef = new T(_objectRef);
	}
	SubclassOf(const SubclassOf<T>& _other)
	{
		objectRef = new T(_other.GetObject());
	}
	SubclassOf(T&& _value)
	{
		objectRef = new T(move(_value));
	}
	~SubclassOf()
	{
		delete objectRef;
	}

public:
	SubclassOf& operator = (const SubclassOf<T>& _other)
	{
		if (this != &_other)
		{
			delete objectRef;
		}

		objectRef = new T(_other.GetObject());
		return *this;
	}
	SubclassOf& operator = (SubclassOf<T>&& _other)
	{
		if (this != &_other)
		{
			delete objectRef;
		}

		objectRef = new T(move(_other.GetObject()));
		return *this;
	}
};