#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

namespace sf {

class Button : public sf::RectangleShape {
private:
    std::function<void(void)> m_onClickCallback;

public:
    Button();
    ~Button();
};

}

#endif