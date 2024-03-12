#include <iostream>
#include <chrono>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>

namespace ch = std::chrono;

static int image_width;
static int image_height;
static int image_channels;

std::vector<sf::Uint8> espejo_pixels ;
//sf::Uint8 *espejo_pixels = nullptr;

double last_time = 0;


void espejo_image(const sf::Uint8 *image) {

    espejo_pixels.resize(image_width * image_height * image_channels);
    // espejo_pixels = new sf::Uint8[image_width * image_height * image_channels];

#pragma omp parallel for default(none) shared(image_height,image_width,espejo_pixels,image)
    for (int i = 0; i < image_height; i++) {
        int start = (i * image_width * 4);
        int end = start + (image_width * 4) - 1;
        int condicion = end;

        while (start < condicion) {

            espejo_pixels[start] = image[end-3];
            espejo_pixels[start + 1] = image[end-2];
            espejo_pixels[start + 2] = image[end-1];
            espejo_pixels[start + 3] = image[end];
            start += 4;
            end -= 4;
        }
    }

}


int main() {

    sf::Text text;
    sf::Font font;
    {
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setString("Mandelbrot set");
        text.setCharacterSize(24); // in pixels, not points!
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setPosition(10,10);
    }

    sf::Text textOptions;
    {
        font.loadFromFile("arial.ttf");
        textOptions.setFont(font);
        textOptions.setCharacterSize(24);
        textOptions.setFillColor(sf::Color::White);
        textOptions.setStyle(sf::Text::Bold);
        textOptions.setString("OPTIONS: [R] Reset [B] Blur");
    }

    //load image
    std::string filename1 = "C:/Programacion Paralela/correccion_examen2/dog.jpg";

    sf::Image im1;
    im1.loadFromFile(filename1);



    image_width = im1.getSize().x;
    image_height = im1.getSize().y;
    image_channels = 4;

    sf::Texture texture;
    texture.create(image_width, image_height);
    texture.update(im1.getPixelsPtr());

    int w = 1600;
    int h = 900;

    sf::RenderWindow  window(sf::VideoMode(w, h), "OMP Suma example");

    sf::Sprite sprite;
    {
        sprite.setTexture(texture);

        float scaleFactorX = w * 1.0 / im1.getSize().x;
        float scaleFactorY = h * 1.0 / im1.getSize().y;
        sprite.scale(scaleFactorX, scaleFactorY);
    }

    sf::Clock clock;

    sf::Clock clockFrames;
    int frames = 0;
    int fps = 0;

    textOptions.setPosition(10, window.getView().getSize().y-40);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if(event.type==sf::Event::KeyReleased) {
                if(event.key.scancode==sf::Keyboard::Scan::R) {
                    texture.update(im1.getPixelsPtr());
                    last_time = 0;
                }
                else if(event.key.scancode==sf::Keyboard::Scan::B) {
                    auto start = ch::high_resolution_clock::now();
                    {
                        espejo_image(im1.getPixelsPtr());
                        auto end = ch::high_resolution_clock::now();
                        ch::duration<double, std::milli> tiempo = end - start;

                        last_time = tiempo.count();
                    }

                    texture.update(espejo_pixels.data());
                }
            }
            else if(event.type==sf::Event::Resized) {
                float scaleFactorX = event.size.width *1.0 / im1.getSize().x;
                float scaleFactorY = event.size.height *1.0 /im1.getSize().y;

                sprite = sf::Sprite();
                sprite.setTexture(texture);
                sprite.scale(scaleFactorX, scaleFactorY);
            }
        }

        auto msg = fmt::format("Blur time: {}ms, FPS: {}", last_time, fps);
        text.setString(msg);

        if(clockFrames.getElapsedTime().asSeconds()>=1.0) {
            fps = frames;
            frames = 0;
            clockFrames.restart();
        }
        frames++;

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.draw(text);
        window.draw(textOptions);
        window.display();
    }

    return 0;
}
