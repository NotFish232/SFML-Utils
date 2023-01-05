#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <functional>

namespace sf {

class Entity : public sf::Sprite {
private:
    std::string m_name;
    std::function<void(const std::string &)> m_signalCallback;
    std::function<sf::Entity *(const std::string &)> m_getEntityCallback;
    bool m_visible;

protected:
    void emitSignal(const std::string &signal) const;
    sf::Entity* getEntity(const std::string &name) const;
    void setName(const std::string &name);
    virtual void showSelf();
    virtual void hideSelf();

public:
    Entity(bool visibility = true);
    ~Entity();
    virtual void init();
    virtual void input(const Event &event);
    virtual void process(float delta);
    virtual void fixedProcess();
    virtual void onCollision(const Entity &entity);
    virtual void onSignal(const std::string &signal);
    virtual const std::vector<sf::FloatRect> getBounds() const;

    bool isVisible() const;
    const std::string &getName() const;
    void setSignalCallback(const std::function<void(const std::string &)> &func);
    void setGetEntityCallback(const std::function<sf::Entity *(const std::string &)> &func);
    bool collidesWith(const sf::Entity &other) const;
};

}

#endif