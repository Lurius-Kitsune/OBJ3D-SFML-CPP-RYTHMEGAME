#include "Utilities.h"
#include "Logger.h"

u_int GetUniqueID()
{
	static u_int _id = 0;
	return ++_id;
}

int GetRandomNumberInRange(const int _min, const int _max)
{
    random_device _rSeed; // Obtient un graine al�atoire
    mt19937 _gen(_rSeed()); // Initialise le g�n�rateur avec la graine
    uniform_int_distribution<> _distr(_min, _max); // D�finit la distribution (les limites)

    return _distr(_gen); // G�n�ration du nombre
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

vector<string> ReadAllFile(const string& _path)
{
    ifstream _file = ifstream(_path);

    if (!_file.is_open())
	{
		LOG(Error, "File not found at " + _path);
		return vector<string>();
	}

    vector<string> _lines;
    string _line;
    while(getline(_file, _line))
	{
		_lines.push_back(_line);
	}
    return _lines;
}

vector<string> SplitString(const string& _string, const char _delimiter)
{
    vector<string> _result;
	stringstream _ss(_string);
	string _item;

	while (getline(_ss, _item, _delimiter))
	{
		_result.push_back(_item);
	}

	return _result;
}

float EaseInQuart(const float _time)
{
    return _time * _time * _time * _time;
}