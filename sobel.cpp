#include <iostream>
#include <chrono>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <fmt/core.h>

namespace ch = std::chrono;

static int image_width1;
static int image_height1;
static int image_channels;
sf::Uint8* blur_image_pixels = nullptr;

double last_time = 0;

std::tuple<sf::Uint8, sf::Uint8, sf::Uint8> process_pixel_sobel(const sf::Uint8 *image, int width, int height, int x, int y) {
    int r_x = 0;
    int g_x = 0;
    int b_x = 0;

    int r_y = 0;
    int g_y = 0;
    int b_y = 0;

    int sobel_x[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
    int sobel_y[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

    for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j <=y+ 1; j++) {
            int index = (j * width + i)*image_channels;

            if (index >= 0 && index <= width * height * 4) {
                int matrixIndex = (i-x + 1) * 3 + (j-y + 1);

                int weight_x = sobel_x[matrixIndex];
                int weight_y = sobel_y[matrixIndex];

                r_x += image[index] * weight_x;
                g_x += image[index + 1] * weight_x;
                b_x += image[index + 2] * weight_x;

                r_y += image[index] * weight_y;
                g_y += image[index + 1] * weight_y;
                b_y += image[index + 2] * weight_y;
            }
        }
    }

    int r = std::clamp((std::abs(r_x) + std::abs(r_y))/2, 0, 255);
    int g = std::clamp((std::abs(g_x) + std::abs(g_y))/2, 0, 255);
    int b = std::clamp((std::abs(b_x) + std::abs(b_y))/2, 0, 255);

    return { r, g, b };
}

void sobel_image(const sf::Uint8 *image) {
    if (!blur_image_pixels)
        blur_image_pixels = new sf::Uint8[image_width1 * image_height1 * image_channels];

    for (int i = 0; i < image_width1; i++) {
        for (int j = 0; j < image_height1; j++) {

            auto [r, g, b] = process_pixel_sobel(image, image_width1, image_height1,i,j);

            int index = (j * image_width1 + i) * image_channels;

            blur_image_pixels[index] = r;
            blur_image_pixels[index + 1] = g;
            blur_image_pixels[index + 2] = b;
            blur_image_pixels[index + 3] = 255;
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
    std::string filename = "C:/Programacion Paralela/correccion_examen2/lobo.jpeg";

    sf::Image im;
    im.loadFromFile(filename);

    image_width1 = im.getSize().x;
    image_height1 = im.getSize().y;
    image_channels = 4;

    sf::Texture texture;
    texture.create(image_width1, image_height1);
    texture.update(im.getPixelsPtr());

    int w = 1600;
    int h = 900;

    sf::RenderWindow  window(sf::VideoMode(w, h), "OMP Blur example");

    sf::Sprite sprite;
    {
        sprite.setTexture(texture);

        float scaleFactorX = w * 1.0 / im.getSize().x;
        float scaleFactorY = h * 1.0 / im.getSize().y;
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
                    texture.update(im.getPixelsPtr());
                    last_time = 0;
                }
                else if(event.key.scancode==sf::Keyboard::Scan::B) {
                    auto start = ch::high_resolution_clock::now();
                    {
                        sobel_image(im.getPixelsPtr());
                        auto end = ch::high_resolution_clock::now();
                        ch::duration<double, std::milli> tiempo = end - start;

                        last_time = tiempo.count();
                    }

                    texture.update(blur_image_pixels);
                }
            }
            else if(event.type==sf::Event::Resized) {
                float scaleFactorX = event.size.width *1.0 / im.getSize().x;
                float scaleFactorY = event.size.height *1.0 /im.getSize().y;

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