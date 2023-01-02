#include <SFML/Graphics.hpp>
#include "Utils.hpp"

int main(int argc, char **argv) {
    using namespace sf;
    RenderWindow window(VideoMode(500, 200), "tests");
    TextField text_field({200, 200});
    text_field.setPosition({0, 0});
    Font font; font.loadFromFile("font.ttf");
    text_field.setFont(font);
    text_field.setCallback([](const std::string &str){
        std::cout << str << '\n';
    });

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            text_field.input(event);
        }
        window.clear(Color::White);
        window.draw(text_field);
        window.display();
    }

    return 0;
}