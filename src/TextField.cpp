#include "../include/TextField.hpp"

using namespace std;
using namespace sf;

void TextField::initializeColors() {
    m_defaultColor = Color(229, 228, 226);
    m_activeColor = Color(211, 211, 211);
    m_rect.setFillColor(m_defaultColor);
    m_text.setFillColor(Color::Black);
}

string TextField::removeNewLines(const string &_str) {
    string str(_str);
    str.erase(remove(str.begin(), str.end(), '\n'), str.end());
    return str;
}

TextField::TextField() {
    m_hasFocus = false;
    m_maxCharacters = 50;
    initializeColors();
}

TextField::TextField(const Vector2f &size) {
    m_rect.setSize(size);
    m_hasFocus = false;
    m_maxCharacters = 50;
    initializeColors();
}

TextField::~TextField() {
}

void TextField::setPosition(const Vector2f &position) {
    m_rect.setPosition(position);
    m_text.setPosition(position);
}

void TextField::setRotation(float angle) {
    m_rect.setRotation(angle);
    m_text.setRotation(angle);
}

void TextField::setScale(const Vector2f &factors) {
    m_rect.setScale(factors);
    m_text.setScale(factors);
}

void TextField::setOrigin(const Vector2f &origin) {
    m_rect.setOrigin(origin);
    m_text.setOrigin(origin);
}

const Vector2f &TextField::getPosition() const {
    assert(m_rect.getPosition() == m_text.getPosition());
    return m_rect.getPosition();
}

float TextField::getRotation() const {
    assert(m_rect.getRotation() == m_text.getRotation());
    return m_rect.getRotation();
}

const Vector2f &TextField::getScale() const {
    assert(m_rect.getScale() == m_text.getScale());
    return m_rect.getScale();
}

const Vector2f &TextField::getOrigin() const {
    assert(m_rect.getOrigin() == m_text.getOrigin());
    return m_rect.getOrigin();
}

const Transform &TextField::getTransform() const {
    assert(m_rect.getTransform() == m_text.getTransform());
    return m_rect.getTransform();
}

const Transform &TextField::getInverseTransform() const {
    assert(m_rect.getInverseTransform() == m_text.getInverseTransform());
    return m_rect.getInverseTransform();
}

void TextField::move(const Vector2f &offset) {
    m_rect.move(offset);
    m_text.move(offset);
}

void TextField::rotate(float angle) {
    m_rect.rotate(angle);
    m_text.rotate(angle);
}

void TextField::scale(const Vector2f &factor) {
    m_rect.scale(factor);
    m_text.scale(factor);
}

void TextField::setDefaultColor(const Color &color) {
    m_defaultColor = color;
    if (!m_hasFocus) {
        m_rect.setFillColor(color);
    }
}

void TextField::setActiveColor(const Color &color) {
    m_activeColor = color;
    if (m_hasFocus) {
        m_rect.setFillColor(color);
    }
}

void TextField::setFont(const Font &font) {
    m_text.setFont(font);
}

void TextField::setMaxCharacters(size_t num) {
    m_maxCharacters = num;
}

size_t TextField::getMaxCharacters() const {
    return m_maxCharacters;
}

void TextField::setCallback(const function<void(const string &)> &func) {
    m_callback = func;
}

void TextField::draw(RenderTarget &window, RenderStates states) const {
    window.draw(m_rect);
    window.draw(m_text);
}

RectangleShape &TextField::getRect() {
    return m_rect;
}

Text &TextField::getText() {
    return m_text;
}

void TextField::input(Event event) {
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
            string current = m_text.getString();
            if (current.length() != 0) {
                m_text.setString(current.substr(0, current.length() - 1));
            }
        } else if (event.key.code == Keyboard::Enter) {
            if (m_callback != NULL) {
                m_callback(removeNewLines(m_text.getString()));
            }
        }
        break;
    case Event::TextEntered: {
        if (!m_hasFocus || m_text.getString().getSize() >= m_maxCharacters) {
            break;
        }

        char ch = static_cast<char>(event.text.unicode);
        if (!isprint(ch)) {
            break;
        }

        string current = m_text.getString();
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
