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

void Text::setDefault_color(Uint8 r, Uint8 g, Uint8 b)
{
    if (default_color==NULL)
        default_color = new SDL_Color;
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

void Text::render_txt()
{
    if (default_color==NULL) {
        default_color = (SDL_Color*) malloc(3*sizeof(int));
        default_color->r = default_color->g = default_color->b = 0;
    }
    TTF_SetFontStyle(default_font, font_style);
    if (default_type=="solid")
        surface = TTF_RenderText_Solid(default_font, value.c_str(), *default_color);
    else if (default_type=="shaded") {
        SDL_Color bg;
        bg.r = 255 - default_color->r;
        bg.g = 255 - default_color->g;
        bg.b = 255 - default_color->b;
        surface = TTF_RenderText_Shaded(default_font, value.c_str(), *default_color, bg);
    }
    else if (default_type=="blended")
        surface = TTF_RenderText_Blended(default_font, value.c_str(), *default_color);
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










