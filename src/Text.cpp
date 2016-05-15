#include "Text.h"

using namespace std;

Text::Text() : value(""), default_size(0), default_font(NULL)
{}
Text::Text(string text) : value(text), default_size(0), default_font(NULL)
{}
Text::Text(string text, string font, int d_size) : value(text),
                                                    default_size(d_size),
                                                    default_font(TTF_OpenFont(font.c_str(),default_size))
{}

void Text::setDefault_font(string f)
{ default_font = TTF_OpenFont(f.c_str(), default_size); }

void Text::setDefault_color(int r, int g, int b)
{
    default_color.r = r;
    default_color.g = g;
    default_color.b = b;
}

Text::~Text()
{ TTF_CloseFont(default_font); }

Text::Text(const Text& other) : value(other.value), default_size(other.default_size)
{}

Text& Text::operator=(const Text& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    value = rhs.value;
    default_size = rhs.default_size;

    return *this;
}








