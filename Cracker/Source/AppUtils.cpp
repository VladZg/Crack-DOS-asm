#ifndef APP_UTILS_CPP
#define APP_UTILS_CPP

#include "../AppConfig.h"
#include <stdlib.h>
#include "../Include/CrackUtils.h"
#include "../Include/AppUtils.h"

int StartApp()
{
    int loading_progress       = 0;
    int glasses_y_position     = 0;
    int glasses_final_position = 215;

    RenderWindow window(sf::VideoMode(540, 480), "AbObA TiMaSoK Cracker! (He-He)");

    Font* font = new Font;
    font->loadFromFile("./fonts/modern.ttf");

    char loading_progress_str[20] = {};
    sprintf(loading_progress_str, "%d%% loaded...", loading_progress);

    Text* vzlom_title_text    = CreateTextObject(font, "vzlom started ..." , 28, Color::Green  , Text::Style::Bold, 140.0, 40.0 );
    Text* vzlom_progress_text = CreateTextObject(font, loading_progress_str, 28, Color::Green  , Text::Style::Bold, 170.0, 400.0);
    Text* cracked_title_text  = CreateTextObject(font, "acess granted!!!"  , 28, Color::Magenta, Text::Style::Bold, 130.0, 85.0 );

    Music* loading_music = CreateMusicObject("./audio/loading.wav");
    Music* cracked_music = CreateMusicObject("./audio/cracked.wav");

    Sprite* background_sprite = CreateSpriteObject("./images/background.jpg", 0  , 0                 );
    Sprite* boom_sprite       = CreateSpriteObject("./images/boom.png"      , 415, 215               );
    Sprite* bin_sprite        = CreateSpriteObject("./images/binary.jpeg"   , 0  , 0                 );
    Sprite* cracked_sprite    = CreateSpriteObject("./images/cracked.jpeg"  , 0  , 0                 );
    Sprite* hacker_sprite     = CreateSpriteObject("./images/mem.jpeg"      , 105, 0                 );
    Sprite* glasses_sprite    = CreateSpriteObject("./images/glasses.png"   , 125, glasses_y_position);

    StretchSprite(background_sprite, 540.0, 480.0);
    StretchSprite(boom_sprite      , 40.0 , 60.0 );
    StretchSprite(bin_sprite       , 540.0, 480.0);
    StretchSprite(cracked_sprite   , 540.0, 480.0);
    StretchSprite(hacker_sprite    , 350.0, 180.0);
    StretchSprite(glasses_sprite   , 220.0, 130.0);

    bin_sprite->setColor(   Color(255, 255, 255, 75));
    hacker_sprite->setColor(Color(255, 255, 255, 50));

    int is_cracking = 0;

    while (window.isOpen())
    {
        window.clear();
        window.draw(*background_sprite);

        if (is_cracking && loading_progress <= 100)
        {
            window.draw(*boom_sprite);
            window.draw(*bin_sprite);
            window.draw(*vzlom_title_text);

            sprintf(loading_progress_str, "%d%% cracked...", ++loading_progress);
            vzlom_progress_text->setString(loading_progress_str);
            window.draw(*vzlom_progress_text);

            sleep(milliseconds(155));
        }

        if (loading_progress > 100)
        {
            window.draw(*cracked_sprite);
            window.draw(*hacker_sprite);
            window.draw(*cracked_title_text);
            window.draw(*glasses_sprite);
        }

        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;

            case Event::KeyPressed:
                if (event.key.code == Keyboard::Enter && loading_progress <= 100)
                {
                    CrackProgramm("./files/not_cracked/CRACK_1.COM", "./files/cracked/CRACKED_1_1.COM", 0xA);
                    CrackProgramm("./files/not_cracked/CRACK_1.COM", "./files/cracked/CRACKED_1_2.COM", 0xB);
                    CrackProgramm("./files/not_cracked/CRACK_1.COM", "./files/cracked/CRACKED_1_3.COM", 0xC);
                    CrackProgramm("./files/not_cracked/CRACK_1.COM", "./files/cracked/CRACKED_1_4.COM", 0xD);
                    // CrackProgramm("./files/not_cracked/CRACK_2.COM", "./files/cracked/CRACKED_2_L.COM", 0xC);
                    // CrackProgramm("./files/not_cracked/CRACK_2.COM", "./files/cracked/CRACKED_2_H.COM", 0xD);
                    is_cracking = ~is_cracking;
                    is_cracking ? loading_music->play() : loading_music->stop();
                }
                break;

//             case Event::KeyReleased:
//                 if (event.key.code == Keyboard::A)
//                     flag = 0;
//                 break;

            default:
                break;
            }
        }

        if (loading_progress == 101)
        {
            loading_music->stop();
            cracked_music->play();

            sleep(milliseconds(1500));
            loading_progress++;
        }

        else if (loading_progress == 102)
        {
            while (glasses_y_position <= glasses_final_position)
            {
                window.clear();
                window.draw(*cracked_sprite);
                glasses_sprite->setPosition(125, glasses_y_position++);
                window.draw(*glasses_sprite);
                window.display();
                sleep(milliseconds(15));
            }

            loading_progress++;
        }

        window.display();
    }

    return 1;
}

Music* CreateMusicObject(const char* source)
{
    Music* music = new Music;
    music->openFromFile(source);
    assert(music != nullptr);

    return music;
}

Text* CreateTextObject(Font* font, const char* msg, int fontsize, Color color, Text::Style style, float x_position, float y_position)
{
    assert(msg != nullptr);
    Text* text = new Text;
    assert(text != nullptr);
    text->setFont(*font);
    text->setString(msg);
    text->setCharacterSize(fontsize);
    text->setFillColor(color);
    text->setStyle(style);
    text->setPosition(x_position, y_position);

    return text;
}

Sprite* CreateSpriteObject(const char* source, float x_position, float y_position)
{
    assert(source != nullptr);

    Image* image = new Image;
    assert(image != nullptr);
    image->loadFromFile(source);

    Texture* texture = new Texture;
    assert(texture != nullptr);
    texture->loadFromImage(*image);

    Sprite* sprite = new Sprite;
    assert(sprite != nullptr);
    sprite->setTexture(*texture);
    sprite->setPosition(x_position, y_position);

    return sprite;
}

int StretchSprite(Sprite* sprite, float width, float height)
{
    Vector2f targetSize(width, height);

    sprite->setScale(targetSize.x / sprite->getLocalBounds().width,
                     targetSize.y / sprite->getLocalBounds().height);

    return 1;
}

#endif
