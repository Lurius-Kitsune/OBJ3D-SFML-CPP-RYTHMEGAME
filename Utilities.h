#pragma once
#include "Macro.h"

u_int GetUniqueID();
int GetRandomNumberInRange(const int _min, const int _max);
float DegToRad(const float _degrees);
float RadToDeg(const float _radians);
float Lerp(const float _start, const float _end, const float _time);
float Lerp_Constant(const float _start, const float _end, const float _time);
float DotProduct(const Vector2f& _direction, const Vector2f& _normal);
float EaseOutQuart(const float _time);

template <typename T>
T GetRandomNumberInRange(const T& _min, const T& _max)
{
    random_device _rSeed; // Obtient un graine aléatoire
    mt19937 _gen(_rSeed()); // Initialise le générateur avec la graine
    uniform_real_distribution<T> _distr(_min, _max); // Définit la distribution (les limites)

    return _distr(_gen); // Génération du nombre
}

template <typename Type, typename BaseType, IS_BASE_OF(BaseType, Type)>
Type* Cast(BaseType* _baseType)
{
    if (!_baseType) return nullptr;
	return dynamic_cast<Type*>(_baseType);
}