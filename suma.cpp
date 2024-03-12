#include <iostream>
#include <chrono>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>

namespace ch = std::chrono;

static int image_width;
static int image_height;
static int image_channels;

sf::Uint8 *suma_pixels = nullptr;


double last_time = 0;


void sum_image(const sf::Uint8 *image, const sf::Uint8 *image2) {
    if (!suma_pixels)
        suma_pixels = new sf::Uint8[image_width * image_height * image_channels];

#pragma omp parallel for collapse(2)
    for (int i = 0; i < image_width; i++) {
        for (int j = 0; j < image_height; j++) {

            int index = (j * image_width + i) * image_channels;

            suma_pixels[index] = (image[index]+ image2[index])/2 ;
            suma_pixels[index + 1] = (image[index+1]+ image2[index+1])/2 ;
            suma_pixels[index + 2] = (image[index+2]+ image2[index+2])/2;
            suma_pixels[index + 3] = 255 ;
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
    std::string filename1 = "C:/Programacion Paralela/correccion_examen2/im1.jpg";
    std::string filename2 = "C:/Programacion Paralela/correccion_examen2/im2.jpg";

    sf::Image im1;
    im1.loadFromFile(filename1);

    sf::Image im2;
    im2.loadFromFile(filename2);


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
                        sum_image(im1.getPixelsPtr(),im2.getPixelsPtr());
                        auto end = ch::high_resolution_clock::now();
                        ch::duration<double, std::milli> tiempo = end - start;

                        last_time = tiempo.count();
                    }

                    texture.update(suma_pixels);
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


