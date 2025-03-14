#include "Utilities.h"

u_int GetUniqueID()
{
	static u_int _id = 0;
	return ++_id;
}

int GetRandomNumberInRange(const int _min, const int _max)
{
    random_device _rSeed; // Obtient un graine aléatoire
    mt19937 _gen(_rSeed()); // Initialise le générateur avec la graine
    uniform_int_distribution<> _distr(_min, _max); // Définit la distribution (les limites)

    return _distr(_gen); // Génération du nombre
}

float DegToRad(const float _degrees)
{
    return _degrees * pi / 180.0f;
}

float RadToDeg(const float _radians)
{
    return 180.0f / pi * _radians;
}

float Lerp(const float _start, const float _end, const float _time)
{
    return _start + _time * (_end - _start);
}

float Lerp_Constant(const float _start, const float _end, const float _time)
{
    return (1 - _time) * _start + _time * _end;
}

float DotProduct(const Vector2f& _direction, const Vector2f& _normal)
{
    return _direction.x * _normal.x + _direction.y * _normal.y;
}

float EaseOutQuart(const float _time)
{
    return 1 - powf(1 - _time, 4.0f);
}

float EaseInQuart(const float _time)
{
    return _time * _time * _time * _time;
}

float Length(const Vector2f& _vector)
{
    return sqrtf(powf(_vector.x, 2.0f) + powf(_vector.y, 2.0f));
}

void Normalize(Vector2f& _vector)
{
    _vector /= Length(_vector);
}

float Distance(const float _first, const float _second)
{
    return abs(_first - _second);
}

float Distance(const Vector2f& _first, const Vector2f& _second)
{
    return sqrtf(pow(_second.x - _first.x, 2.0f) + pow(_second.y - _first.y, 2.0f));
}

Vector2f ComputeNormal(const FloatRect& _rect)
{
    const Vector2f& _normal = Vector2f(-_rect.size.y, _rect.size.x);
    const float _norme = Length(_normal);
    return _normal / _norme;
}

Vector2f SmoothDamp(const Vector2f& _current, Vector2f _target, Vector2f& _currentVelocity, float _smoothTime, const float _deltaTime, const float _maxSpeed)
{
    float _outputX = 0.0f;
    float _outputY = 0.0f;

    // Based on Game Programming Gems 4 Chapter 1.10
    _smoothTime = max(0.0001f, _smoothTime);
    const float _omega = 2.0f / _smoothTime;

    float _x = _omega * _deltaTime;
    float _exp = 1.0f / (1.0f + _x + 0.48F * _x * _x + 0.235F * _x * _x * _x);

    float _changeX = _current.x - _target.x;
    float _changeY = _current.y - _target.y;
    const Vector2f& _originalTo = _target;

    // Clamp maximum speed
    float _maxChange = _maxSpeed * _smoothTime;

    float _maxChangeSq = _maxChange * _maxChange;
    float _sqrmag = _changeX * _changeX + _changeY * _changeY;
    if (_sqrmag > _maxChangeSq)
    {
        float mag = sqrtf(_sqrmag);
        _changeX = _changeX / mag * _maxChange;
        _changeY = _changeY / mag * _maxChange;
    }

    _target.x = _current.x - _changeX;
    _target.y = _current.y - _changeY;

    float temp_x = (_currentVelocity.x + _omega * _changeX) * _deltaTime;
    float temp_y = (_currentVelocity.y + _omega * _changeY) * _deltaTime;

    _currentVelocity.x = (_currentVelocity.x - _omega * temp_x) * _exp;
    _currentVelocity.y = (_currentVelocity.y - _omega * temp_y) * _exp;

    _outputX = _target.x + (_changeX + temp_x) * _exp;
    _outputY = _target.y + (_changeY + temp_y) * _exp;

    // Prevent overshooting
    float _origMinusCurrentX = _originalTo.x - _current.x;
    float _origMinusCurrentY = _originalTo.y - _current.y;
    float _outMinusOrigX = _outputX - _originalTo.x;
    float _outMinusOrigY = _outputY - _originalTo.y;

    if (_origMinusCurrentX * _outMinusOrigX + _origMinusCurrentY * _outMinusOrigY > 0)
    {
        _outputX = _originalTo.x;
        _outputY = _originalTo.y;

        _currentVelocity.x = (_outputX - _originalTo.x) / _deltaTime;
        _currentVelocity.y = (_outputY - _originalTo.y) / _deltaTime;
    }

    return { _outputX, _outputY };
}

vector<string> SplitString(const string& _string, const char _delimiter)
{
    vector<string> _result;
    stringstream _ss = stringstream(_string);
    string _item;

    while (getline(_ss, _item, _delimiter))
    {
        _result.push_back(_item);
    }

    return _result;
}