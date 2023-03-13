#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>

using namespace sf;

Sprite LoadBackgroundImage(Window window, char* filename, Sprite* sprite);
int num = 0;

int main()
{
    RenderWindow window(sf::VideoMode(540, 480), "AbObA TiMaSoK Cracker! (He-He)");

    Music music;
    music.openFromFile("./audio/audio1.wav");

    Image background_image;
    background_image.loadFromFile("./images/background.jpg");

    Image boom_image;
    boom_image.loadFromFile("./images/boom.png");

    Image bin_image;
    bin_image.loadFromFile("./images/binary.jpeg");

    Texture background_texture;
    background_texture.loadFromImage(background_image);

    Texture boom_texture;
    boom_texture.loadFromImage(boom_image);

    Texture bin_texture;
    bin_texture.loadFromImage(bin_image);

    Sprite background_sprite;
    background_sprite.setTexture(background_texture);
    background_sprite.setPosition(0, 0);

    Sprite boom_sprite;
    boom_sprite.setTexture(boom_texture);
    boom_sprite.setPosition(415, 215);

    Sprite bin_sprite;
    bin_sprite.setTexture(bin_texture);
    bin_sprite.setPosition(0, 0);

    Vector2f background_targetSize(540.0f, 480.0f);
    Vector2f boom_targetSize(40.0f, 60.0f);

    background_sprite.setScale( background_targetSize.x / background_sprite.getLocalBounds().width,
                                background_targetSize.y / background_sprite.getLocalBounds().height);

    boom_sprite.setScale( boom_targetSize.x / boom_sprite.getLocalBounds().width,
                          boom_targetSize.y / boom_sprite.getLocalBounds().height);

    bin_sprite.setScale( background_targetSize.x / bin_sprite.getLocalBounds().width,
                         background_targetSize.y / bin_sprite.getLocalBounds().height);

    background_sprite.setColor(Color(255, 255, 255, 127));
    bin_sprite.setColor(Color(255, 255, 255, 75));

    window.draw(background_sprite);
    window.draw(boom_sprite);
    window.draw(bin_sprite);

    int is_boom = 0;

    while (window.isOpen())
    {
        window.clear();
        window.draw(background_sprite);

        if (is_boom)
        {
            window.draw(boom_sprite);
            window.draw(bin_sprite);
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
                if (event.key.code == Keyboard::Enter)
                    is_boom = ~is_boom;
                    is_boom ? music.play() : music.stop();

                break;

//             case Event::KeyReleased:
//                 if (event.key.code == Keyboard::A)
//                     flag = 0;
//                 break;

            default:
                break;
            }
        }

        window.display();
    }

    return 0;
}
