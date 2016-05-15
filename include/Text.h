#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <SDL/SDL_ttf.h>

class Text
{
    public:
        Text();
        Text(std::string);
        Text(std::string, std::string, int);
        ~Text();
        Text(const Text& other);
        Text& operator=(const Text& other);

        void setDefault_font(std::string);
        void setText(std::string t) { value = t; }
        void setDefault_size(int s) { default_size = s; }
        void setDefault_type(std::string t) { default_type = t; }
        void setDefault_color(SDL_Color c) { default_color = c; }
        void setDefault_color(int, int, int);
        TTF_Font* getDefault_font() { return default_font; }
        std::string getText() { return value; }
        std::string getDefault_type() { return default_type; }
        SDL_Color getDefault_color() { return default_color; }

    protected:

    private:
        std::string value;
        int default_size;
        TTF_Font* default_font;
        std::string default_type;
        SDL_Color default_color;
};

#endif // TEXT_H
