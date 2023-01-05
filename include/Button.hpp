#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <assert.h>
#include <functional>

namespace sf {

class Button : public Drawable, public Transformable {
private:
    std::function<void(void)> m_onClickCallback;
    RectangleShape m_rect;
    Text m_text;

public:
    Button();
    Button(const Vector2f &size);
    ~Button();


    void setSize(const Vector2f &size);
    void setPosition(const Vector2f &position);
    void setRotation(float angle);
    void setScale(const Vector2f &factors);
    void setOrigin(const Vector2f &origin);

    const Vector2f &getSize() const;
    const Vector2f &getPosition() const;
    float getRotation() const;
    const Vector2f &getScale() const;
    const Vector2f &getOrigin() const;
    const Transform &getTransform() const;
    const Transform &getInverseTransform() const;

    void move(const Vector2f &offset);
    void rotate(float angle);
    void scale(const Vector2f &factor);

    void setFont(const Font &font);
    void setText(const std::string &text);

    inline void draw(RenderTarget &window, RenderStates states) const override;

    RectangleShape &getRect();
    Text &getText();

    void input(const Event &event);
    void setOnClickCallback(const std::function<void(void)> &func);
};

}

#endif