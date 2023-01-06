#include "../include/Button.hpp"

using namespace std;
using namespace sf;

Button::Button() {
    m_text.setFillColor(Color::Black);
}

Button::Button(const Vector2f &size) {
    m_rect.setSize(size);
    m_text.setFillColor(Color::Black);
}

Button::~Button() {
}

void Button::setSize(const Vector2f &size) {
    m_rect.setSize(size);
}

void Button::setPosition(const Vector2f &position) {
    m_rect.setPosition(position);
    m_text.setPosition(position);
}

void Button::setRotation(float angle) {
    m_rect.setRotation(angle);
    m_text.setRotation(angle);
}

void Button::setScale(const Vector2f &factors) {
    m_rect.setScale(factors);
    m_text.setScale(factors);
}

void Button::setOrigin(const Vector2f &origin) {
    m_rect.setOrigin(origin);
}

const Vector2f &Button::getSize() const {
    return m_rect.getSize();
}

const Vector2f &Button::getPosition() const {
    assert(m_rect.getPosition() == m_text.getPosition());
    return m_rect.getPosition();
}

float Button::getRotation() const {
    assert(m_rect.getRotation() == m_text.getRotation());
    return m_rect.getRotation();
}

const Vector2f &Button::getScale() const {
    assert(m_rect.getScale() == m_text.getScale());
    return m_rect.getScale();
}

const Vector2f &Button::getOrigin() const {
    return m_rect.getOrigin();
}

const Transform &Button::getTransform() const {
    assert(m_rect.getTransform() == m_text.getTransform());
    return m_rect.getTransform();
}

const Transform &Button::getInverseTransform() const {
    assert(m_rect.getInverseTransform() == m_text.getInverseTransform());
    return m_rect.getInverseTransform();
}

void Button::move(const Vector2f &offset) {
    m_rect.move(offset);
    m_text.move(offset);
}

void Button::rotate(float angle) {
    m_rect.rotate(angle);
    m_text.rotate(angle);
}

void Button::scale(const Vector2f &factor) {
    m_rect.scale(factor);
    m_text.scale(factor);
}

void Button::setFont(const Font &font) {
    m_text.setFont(font);
}

void Button::setText(const string &text) {
    m_text.setString(text);
    auto floatRect = m_text.getLocalBounds();
    m_text.setOrigin({floatRect.left + floatRect.width / 2, floatRect.top + floatRect.height / 2});
}

void Button::draw(RenderTarget &window, RenderStates states) const {
    window.draw(m_rect);
    window.draw(m_text);
}

RectangleShape &Button::getRect() {
    return m_rect;
}
Text &Button::getText() {
    return m_text;
}

void Button::input(const Event &event) {
    if (event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left) {
            auto mouseButton = event.mouseButton;
            Vector2f mousePosition{(float)mouseButton.x, (float)mouseButton.y};

            if (m_rect.getGlobalBounds().contains(mousePosition)) {
                if (m_onClickCallback != NULL) {
                    m_onClickCallback();
                }
            }
        }
    }
}

void Button::setOnClickCallback(const function<void(void)> &func) {
    m_onClickCallback = func;
}
