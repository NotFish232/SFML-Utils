#ifndef TEXTFIELD_CPP
#define TEXTFIELD_CPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <assert.h>
#include <functional>
#include <iostream>

namespace sf {

class TextField : public Drawable, public Transformable {
private:
    RectangleShape m_rect;
    Text m_text;
    size_t m_maxCharacters;
    bool m_hasFocus;
    Color m_defaultColor, m_activeColor;
    std::function<void(const std::string &)> m_callback;

    void initializeColors() {
        m_defaultColor = Color(229, 228, 226);
        m_activeColor = Color(211, 211, 211);
        m_rect.setFillColor(m_defaultColor);
        m_text.setFillColor(Color::Black);
    }

    std::string removeNewLines(const std::string &_str) {
        std::string str(_str);
        str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
        return str;
    }

public:
    TextField() {
        m_hasFocus = false;
        m_maxCharacters = 50;
        initializeColors();
    }

    TextField(const Vector2f &size) {
        m_rect.setSize(size);
        m_hasFocus = false;
        m_maxCharacters = 50;
        initializeColors();
    }

    void setPosition(const Vector2f &position) {
        m_rect.setPosition(position);
        m_text.setPosition(position);
    }

    void setRotation(float angle) {
        m_rect.setRotation(angle);
        m_text.setRotation(angle);
    }

    void setScale(const Vector2f &factors) {
        m_rect.setScale(factors);
        m_text.setScale(factors);
    }

    void setOrigin(const Vector2f &origin) {
        m_rect.setOrigin(origin);
        m_text.setOrigin(origin);
    }

    const Vector2f &getPosition() const {
        assert(m_rect.getPosition() == m_text.getPosition());
        return m_rect.getPosition();
    }

    float getRotation() const {
        assert(m_rect.getRotation() == m_text.getRotation());
        return m_rect.getRotation();
    }

    const Vector2f &getScale() const {
        assert(m_rect.getScale() == m_text.getScale());
        return m_rect.getScale();
    }

    const Vector2f &getOrigin() const {
        assert(m_rect.getOrigin() == m_text.getOrigin());
        return m_rect.getOrigin();
    }

    void move(const Vector2f &offset) {
        m_rect.move(offset);
        m_text.move(offset);
    }

    void rotate(float angle) {
        m_rect.rotate(angle);
        m_text.rotate(angle);
    }

    void scale(const Vector2f &factor) {
        m_rect.scale(factor);
        m_text.scale(factor);
    }

    const Transform &getTransform() const {
        assert(m_rect.getTransform() == m_text.getTransform());
        return m_rect.getTransform();
    }

    const Transform &getInverseTransform() const {
        assert(m_rect.getInverseTransform() == m_text.getInverseTransform());
        return m_rect.getInverseTransform();
    }

    void setDefaultColor(const Color &color) {
        m_defaultColor = color;
        if (!m_hasFocus) {
            m_rect.setFillColor(color);
        }
    }

    void setActiveColor(const Color &color) {
        m_activeColor = color;
        if (m_hasFocus) {
            m_rect.setFillColor(color);
        }
    }

    void setFont(const Font &font) {
        m_text.setFont(font);
    }

    void setMaxCharacters(size_t num) {
        m_maxCharacters = num;
    }

    size_t getMaxCharacters() const {
        return m_maxCharacters;
    }

    void setCallback(const std::function<void(const std::string &)> &func) {
        m_callback = func;
    }

    inline void draw(RenderTarget &window, RenderStates states) const override {
        window.draw(m_rect);
        window.draw(m_text);
    }

    // plug into input loop for it to function
    void input(Event event) {
        switch (event.type) {
        case Event::MouseButtonPressed: {
            if (event.mouseButton.button != Mouse::Left) {
                break;
            }
            auto mouseButton = event.mouseButton;
            Vector2f mousePosition{(float)mouseButton.x, (float)mouseButton.y};
            if (m_rect.getGlobalBounds().contains(mousePosition)) {
                m_hasFocus = true;
                m_rect.setFillColor(m_activeColor);
            } else {
                m_hasFocus = false;
                m_rect.setFillColor(m_defaultColor);
            }
            break;
        }
        case Event::KeyPressed:
            if (event.key.code == Keyboard::Backspace) {
                std::string current = m_text.getString();
                if (current.length() != 0) {
                    m_text.setString(current.substr(0, current.length() - 1));
                }
            } else if (event.key.code == Keyboard::Enter) {
                if (m_callback != NULL) {
                    m_callback(removeNewLines(m_text.getString()));
                } else
                    std::cout << "hi \n";
            }
            break;
        case Event::TextEntered: {
            if (!m_hasFocus || m_text.getString().getSize() >= m_maxCharacters) {
                break;
            }

            char ch = static_cast<char>(event.text.unicode);
            if (!std::isprint(ch)) {
                break;
            }

            std::string current = m_text.getString();
            m_text.setString(current + ch);

            if (m_text.getLocalBounds().width > m_rect.getLocalBounds().width) {
                m_text.setString(current + '\n' + ch);
            }

            break;
        }

        default:
            break;
        }
    }

    RectangleShape &getRect() {
        return m_rect;
    }

    Text &getText() {
        return m_text;
    }

};

}

#endif