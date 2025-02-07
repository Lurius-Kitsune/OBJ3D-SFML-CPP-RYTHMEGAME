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
Vector2f ComputeNormal(const FloatRect& _rect);
float Length(const Vector2f& _vector);
void Normalize(Vector2f& _vector);
float Distance(const float _first, const float _second);
float Distance(const Vector2f& _first, const Vector2f& _second);
Vector2f ComputeNormal(const FloatRect& _rect);

template <typename T>
T GetRandomNumberInRange(const T& _min, const T& _max)
{
    random_device _rSeed; // Obtient un graine al�atoire
    mt19937 _gen(_rSeed()); // Initialise le g�n�rateur avec la graine
    uniform_real_distribution<T> _distr(_min, _max); // D�finit la distribution (les limites)

    return _distr(_gen); // G�n�ration du nombre
}

template <typename Type, typename BaseType, IS_BASE_OF(BaseType, Type)>
Type* Cast(BaseType* _baseType)
{
    if (!_baseType) return nullptr;
	return dynamic_cast<Type*>(_baseType);
}

template<typename T, typename K>
bool Instanceof(K _object)
{
    return is_same<T, decltype(_object)>::value;
}