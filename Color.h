#pragma once
#include "Macro.h"

#define BLACK "\x1B[38;5;232m"
#define DARK_GRAY "\x1B[38;5;237m"
#define GRAY "\x1B[38;5;244m"
#define LIGHT_GRAY "\x1B[38;5;249m"
#define WHITE "\x1B[38;5;255m"
#define DARK_RED "\x1B[38;5;124m"
#define RED "\x1B[38;5;196m"
#define DARK_ORANGE "\x1B[38;5;130m"
#define ORANGE "\x1B[38;5;208m"
#define DARK_YELLOW "\x1B[38;5;136m"
#define YELLOW "\x1B[38;5;226m"
#define LIME "\x1B[38;5;82m"
#define GREEN "\x1B[38;5;106m"
#define BLUE "\x1B[38;5;63m"
#define LIGHT_BLUE "\x1B[38;5;12m"
#define CYAN "\x1B[38;5;51m"
#define PINK "\x1B[38;5;219m"
#define MAGENTA "\x1B[38;5;199m"
#define PURPLE "\x1B[38;5;99m"
#define BROWN "\x1B[38;5;130m"

#define BG_BLACK "\x1B[48;5;232m"
#define BG_DARK_GRAY "\x1B[48;5;237m"
#define BG_GRAY "\x1B[48;5;244m"
#define BG_LIGHT_GRAY "\x1B[48;5;249m"
#define BG_WHITE "\x1B[48;5;255m"
#define BG_DARK_RED "\x1B[48;5;124m"
#define BG_RED "\x1B[48;5;196m"
#define BG_DARK_ORANGE "\x1B[48;5;130m"
#define BG_ORANGE "\x1B[48;5;208m"
#define BG_DARK_YELLOW "\x1B[48;5;136m"
#define BG_YELLOW "\x1B[48;5;226m"
#define BG_LIME "\x1B[48;5;82m"
#define BG_GREEN "\x1B[48;5;106m"
#define BG_BLUE "\x1B[48;5;63m"
#define BG_LIGHT_BLUE "\x1B[48;5;12m"
#define BG_CYAN "\x1B[48;5;51m"
#define BG_PINK "\x1B[48;5;219m"
#define BG_MAGENTA "\x1B[48;5;199m"
#define BG_PURPLE "\x1B[48;5;99m"
#define BG_BROWN "\x1B[48;5;130m"

#define COLOR_RESET "\033[0m"
#define UNDERLINE "\033[4m"
#define SWAP "\033[7m" // Swap background and foreground colors

#define BLINK_TEXT "\033[5m"	
#define BLINK_TEXT_OFF "\033[25m"	
#define ITALIC "\033[3m"
#define ITALIC_OFF "\033[23m"
#define CROSSED "\033[9m"
#define CROSSED_OFF "\033[0m"

#define BOLD "\x1B[1m"
#define RESET_BOLD "\x1B[0m"

// x => Color code between 0 and 255
#define COLOR(x) string("\x1B[38;5;" + x) + "m"
#define BG_COLOR(x) "\x1B[48;5;"<<x<<"m"

#define CUSTOM_RGB(r,g,b)"\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m"
#define BG_RGB(r,g,b) "\x1b[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m"
#define TEXT_RGB(r,g,b) "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m"

struct ColorData
{
	int r;
	int g;
	int b;

	ColorData()
	{
		r = g = b = 0;
	}

	ColorData(const int _r, const int _g, const int _b)
	{
		r = _r;
		g = _g;
		b = _b;
	}

	string ToString(const bool _textOnly) const
	{
		if (_textOnly) return TEXT_RGB(r, g, b);
		return BG_RGB(r, g, b);
	}
};

struct Gradient
{
	ColorData gradA;
	ColorData gradB;

	Gradient() = default;
	Gradient(const ColorData& _a, const ColorData& _b)
	{
		gradA = _a;
		gradB = _b;
	}

	string GradientString(const string& _text, const bool _textOnly = true) const;
	ColorData ClampGradient(const int _index, const int _maxDisplayChar) const;
};