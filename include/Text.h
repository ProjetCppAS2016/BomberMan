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

        void render_txt();
};

#endif // TEXT_H








