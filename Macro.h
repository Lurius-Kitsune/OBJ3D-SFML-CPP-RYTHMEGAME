#pragma once
#pragma warning (disable : 4275)
#pragma warning( disable : 4244)

// STL
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <typeindex>
#include <typeinfo>
#include <exception>
#include <random>

// OLD
#include <math.h>
#include <conio.h>

// Collections
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <set>

/// SFML
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#define DEBUG_PATH
#ifdef DEBUG_PATH
#define PATH __FUNCTION__
#else
#define PATH __FILE__
#endif // DEBUG_FILE

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define Super __super
#define FILE_NAME (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define DEBUG_INFO "(File: " + CAST(string, PATH) + " | Line: " + to_string(__LINE__) + ")"
#define FORCEINLINE __forceinline
#define INLINE __inline
#define CAST(_type, _expr) static_cast<_type>(_expr)
#define SLEEP(_duration) sleep(_duration)
#define NO_DISCARD _NODISCARD
#define IS_BASE_OF(_base, _type) typename = enable_if_t<is_base_of_v<_base, _type>>

using namespace std;
using namespace sf;
using namespace priv;

typedef unsigned short u_short;
typedef unsigned int u_int;
typedef long long l_long;