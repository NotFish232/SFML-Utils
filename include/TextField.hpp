#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

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

    void initializeColors();
    std::string removeNewLines(const std::string &_str);

public:
    TextField();
    TextField(const Vector2f &size);
    ~TextField();

    void setPosition(const Vector2f &position);
    void setRotation(float angle);
    void setScale(const Vector2f &factors);
    void setOrigin(const Vector2f &origin);
    const Vector2f &getPosition() const;
    float getRotation() const;
    const Vector2f &getScale() const;
    const Vector2f &getOrigin() const;
    const Transform &getTransform() const;
    const Transform &getInverseTransform() const;

    void move(const Vector2f &offset);
    void rotate(float angle);
    void scale(const Vector2f &factor);

    void setDefaultColor(const Color &color);
    void setActiveColor(const Color &color);
    void setFont(const Font &font);
    void setMaxCharacters(size_t num);
    size_t getMaxCharacters() const;

    void setCallback(const std::function<void(const std::string &)> &func);
    inline void draw(RenderTarget &window, RenderStates states) const override;

    RectangleShape &getRect();
    Text &getText();

    void input(Event event);
};

}

#endif