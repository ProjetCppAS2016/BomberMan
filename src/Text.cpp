#include "Text.h"

using namespace std;

Text::Text() : Surface(),
                value(""),
                default_size(0),
                font_name(""),
                default_font(NULL),
                default_type("solid"),
                default_color(NULL),
                font_style(TTF_STYLE_NORMAL)
{}
Text::Text(string text) : Surface(),
                            value(text),
                            default_size(0),
                            font_name(""),
                            default_font(NULL),
                            default_type("solid"),
                            default_color(NULL),
                            font_style(TTF_STYLE_NORMAL)
{}
Text::Text(string text, string font, int d_size) : Surface(),
                                                    value(text),
                                                    default_size(d_size),
                                                    font_name(font),
                                                    default_font(TTF_OpenFont(font.c_str(),d_size)),
                                                    default_type("solid"),
                                                    default_color(NULL),
                                                    font_style(TTF_STYLE_NORMAL)
{}

void Text::setFont(string f)
{
    font_name = f;
    default_font = TTF_OpenFont(f.c_str(), default_size);
}

void Text::setDefault_color(int r, int g, int b)
{
    if (default_color==NULL)
        default_color = (SDL_Color*) malloc(3*sizeof(int));
    default_color->r = r;
    default_color->g = g;
    default_color->b = b;
}

Text::~Text()
{
    if (default_color!=NULL)
        delete default_color;
}

Text::Text(const Text& other) : Surface(),
                                value(other.value),
                                default_size(other.default_size),
                                font_name(other.font_name),
                                default_font(TTF_OpenFont(font_name.c_str(),default_size)),
                                default_type(other.default_type),
                                default_color(other.default_color),
                                font_style(other.font_style)
{}

Text& Text::operator=(const Text& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    value = rhs.value;
    default_size = rhs.default_size;
    font_name = rhs.font_name;
    default_font = TTF_OpenFont(font_name.c_str(),default_size);
    default_type = rhs.default_type;
    default_color = rhs.default_color;
    font_style = rhs.font_style;

    return *this;
}

void Text::render(string f, int s)
{
    TTF_Font *tmp = default_font;
    default_font = TTF_OpenFont(f.c_str(), s);
    render_txt();
    default_font = tmp;
}

void Text::render(int r, int g, int b)
{
    int t_r = default_color->r, t_g = default_color->g, t_b = default_color->b;
    default_color->r = r;
    default_color->g = g;
    default_color->b = b;
    if (default_font!=NULL) render_txt();
    default_color->r = t_r;
    default_color->g = t_g;
    default_color->b = t_b;
}

void Text::render(string txt)
{
    string tmp = value;
    value = txt;
    if (default_font!=NULL) render_txt();
    value = tmp;
}

void Text::render()
{
    if (default_font!=NULL) render_txt();
}










