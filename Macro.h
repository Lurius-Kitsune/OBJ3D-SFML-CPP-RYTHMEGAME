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
#define SAME_VALUE(_first, _second) is_same_v<_first, _second>
#define ENABLE_IF(_element) enable_if_t<_element>
#define IS_BASE_OF(_base, _type) typename = enable_if_t<is_base_of_v<_base, _type>>
#define TYPE(_type) decay_t<decltype(_type)>
#define TYPE_ID(_type) typeid(_type)
#define TYPE_NAME(_type) CAST(string, TYPE_ID(_type).name())
#define TYPE_INDEX_NAME(_typeIndex) CAST(string, _typeIndex.name())

using namespace std;
using namespace sf;
using namespace priv;
using namespace placeholders;

typedef unsigned short u_short;
typedef unsigned int u_int;
typedef long long l_long;