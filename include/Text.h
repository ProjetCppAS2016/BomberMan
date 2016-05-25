#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <SDL/SDL_ttf.h>
#include "Surface.h"

class Text : public Surface
{
    public:
        Text();
        Text(std::string);
        Text(std::string, std::string, int);
        virtual ~Text();
        Text(const Text& other);
        Text& operator=(const Text& rhs);

        void setFont(std::string);
        void setText(std::string t) { value = t; }
        void setDefault_size(int s) { default_size = s; }
        void setDefault_type(std::string t) { default_type = t; }
        void setDefault_color(SDL_Color *c) { *default_color = *c; }
        void setDefault_color(Uint8, Uint8, Uint8);
        TTF_Font* getDefault_font() { return default_font; }
        std::string getText() { return value; }
        std::string getDefault_type() { return default_type; }
        SDL_Color* getDefault_color() { return default_color; }
        void setFont_style(int s) { font_style = s; }

        void render();
        void render(std::string);
        void render(int, int, int);
        void render(std::string, int);
        void close_font() { TTF_CloseFont(default_font); }

    protected:

    private:
        std::string value;
        int default_size;
        std::string font_name;
        TTF_Font *default_font;
        std::string default_type;
        SDL_Color *default_color;
        int font_style;

        void render_txt()
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
};

#endif // TEXT_H








