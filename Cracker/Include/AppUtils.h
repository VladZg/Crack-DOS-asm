#ifndef APP_UTILS_H
#define APP_UTILS_H

#include "../AppConfig.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <cassert>

using namespace sf;

Music* CreateMusicObject(const char* source);
Text* CreateTextObject(Font* font, const char* msg, int fontsize, Color color, Text::Style style, float x_position, float y_position);
Sprite* CreateSpriteObject(const char* source, float x_position, float y_position);
int StretchSprite(Sprite* sprite, float width, float height);

int StartApp(const char* inp_filename, const char* out_filename);

#endif
