#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <cassert>

using namespace sf;

Sprite LoadBackgroundImage(Window window, char* filename, Sprite* sprite);
int CrackProgramm(const char* filename);

int loading_progress = 0;
int glasses_y_position = 0;
int glasses_final_position = 215;

int main()
{
    RenderWindow window(sf::VideoMode(540, 480), "AbObA TiMaSoK Cracker! (He-He)");

    Font font;
    font.loadFromFile("./fonts/modern.ttf");

    Text vzlom_title_text;
    vzlom_title_text.setFont(font);
    vzlom_title_text.setString("vzlom started ...");
    vzlom_title_text.setCharacterSize(28);
    vzlom_title_text.setFillColor(Color::Green);
    vzlom_title_text.setStyle(Text::Bold);
    vzlom_title_text.setPosition(140, 40);

    Text vzlom_progress_text;
    vzlom_progress_text.setFont(font);
    char loading_progress_str[20] = {};
    sprintf(loading_progress_str, "%d%% loaded...", loading_progress);
    vzlom_progress_text.setString(loading_progress_str);
    vzlom_progress_text.setCharacterSize(28);
    vzlom_progress_text.setFillColor(Color::Green);
    vzlom_progress_text.setStyle(Text::Bold);
    vzlom_progress_text.setPosition(170, 400);

    Text cracked_title_text;
    cracked_title_text.setFont(font);
    cracked_title_text.setString("acess granted!!!");
    cracked_title_text.setCharacterSize(28);
    cracked_title_text.setFillColor(Color::Magenta);
    cracked_title_text.setStyle(Text::Bold);
    cracked_title_text.setPosition(130, 85);

    Music loading_music;
    loading_music.openFromFile("./audio/loading.wav");

    Music cracked_music;
    cracked_music.openFromFile("./audio/cracked.wav");

    Image background_image;
    background_image.loadFromFile("./images/background.jpg");

    Image boom_image;
    boom_image.loadFromFile("./images/boom.png");

    Image bin_image;
    bin_image.loadFromFile("./images/binary.jpeg");

    Image cracked_image;
    cracked_image.loadFromFile("./images/cracked.jpeg");

    Image hacker_image;
    hacker_image.loadFromFile("./images/mem.jpeg");

    Image glasses_image;
    glasses_image.loadFromFile("./images/glasses.png");

    Texture background_texture;
    background_texture.loadFromImage(background_image);

    Texture boom_texture;
    boom_texture.loadFromImage(boom_image);

    Texture bin_texture;
    bin_texture.loadFromImage(bin_image);

    Texture cracked_texture;
    cracked_texture.loadFromImage(cracked_image);

    Texture hacker_texture;
    hacker_texture.loadFromImage(hacker_image);

    Texture glasses_texture;
    glasses_texture.loadFromImage(glasses_image);

    Sprite background_sprite;
    background_sprite.setTexture(background_texture);
    background_sprite.setPosition(0, 0);

    Sprite boom_sprite;
    boom_sprite.setTexture(boom_texture);
    boom_sprite.setPosition(415, 215);

    Sprite bin_sprite;
    bin_sprite.setTexture(bin_texture);
    bin_sprite.setPosition(0, 0);

    Sprite cracked_sprite;
    cracked_sprite.setTexture(cracked_texture);
    cracked_sprite.setPosition(0, 0);

    Sprite hacker_sprite;
    hacker_sprite.setTexture(hacker_texture);
    hacker_sprite.setPosition(105, 0);

    Sprite glasses_sprite;
    glasses_sprite.setTexture(glasses_texture);
    glasses_sprite.setPosition(125, glasses_y_position);

    Vector2f background_targetSize(540.0f, 480.0f);
    Vector2f boom_targetSize(40.0f, 60.0f);
    Vector2f hacker_targetSize(350.0f, 180.0f);
    Vector2f glasses_targetSize(220.0f, 130.0f);

    background_sprite.setScale( background_targetSize.x / background_sprite.getLocalBounds().width,
                                background_targetSize.y / background_sprite.getLocalBounds().height);

    boom_sprite.setScale( boom_targetSize.x / boom_sprite.getLocalBounds().width,
                          boom_targetSize.y / boom_sprite.getLocalBounds().height);

    bin_sprite.setScale( background_targetSize.x / bin_sprite.getLocalBounds().width,
                         background_targetSize.y / bin_sprite.getLocalBounds().height);

    cracked_sprite.setScale( background_targetSize.x / cracked_sprite.getLocalBounds().width,
                             background_targetSize.y / cracked_sprite.getLocalBounds().height);

    hacker_sprite.setScale( hacker_targetSize.x / hacker_sprite.getLocalBounds().width,
                            hacker_targetSize.y / hacker_sprite.getLocalBounds().height);

    glasses_sprite.setScale( glasses_targetSize.x / glasses_sprite.getLocalBounds().width,
                             glasses_targetSize.y / glasses_sprite.getLocalBounds().height);

    // background_sprite.setColor(Color(255, 255, 255, 127));
    bin_sprite.setColor(Color(255, 255, 255, 75));
    hacker_sprite.setColor(Color(255, 255, 255, 50));

    window.draw(background_sprite);

    int is_boom = 0;

    while (window.isOpen())
    {
        window.clear();
        window.draw(background_sprite);

        if (is_boom && loading_progress <= 100)
        {
            window.draw(boom_sprite);
            window.draw(bin_sprite);
            window.draw(vzlom_title_text);

            sprintf(loading_progress_str, "%d%% cracked...", ++loading_progress);
            vzlom_progress_text.setString(loading_progress_str);
            window.draw(vzlom_progress_text);

            sleep(milliseconds(155)); //155
        }

        if (loading_progress > 100)
        {
            window.draw(cracked_sprite);
            window.draw(hacker_sprite);
            window.draw(cracked_title_text);
            window.draw(glasses_sprite);
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
                    CrackProgramm("./Hack.com");
                    is_boom = ~is_boom;
                    is_boom ? loading_music.play() : loading_music.stop();
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
            loading_music.stop();
            cracked_music.play();

            sleep(milliseconds(1500));
            loading_progress++;
        }

        else if (loading_progress == 102)
        {
            while (glasses_y_position <= glasses_final_position)
            {
                window.clear();
                window.draw(cracked_sprite);
                glasses_sprite.setPosition(125, glasses_y_position++);
                window.draw(glasses_sprite);
                window.display();
                sleep(milliseconds(15));
            }

            loading_progress++;
        }

        window.display();
    }

    return 0;
}

int CrackProgramm(const char* filename)
{
    assert(filename != nullptr);
    FILE* file = fopen(filename, "w+");
    assert(file != nullptr);

    fprintf(stdout, "CRACKED!\n");

    return 1;
}
