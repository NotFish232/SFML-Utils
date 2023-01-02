#ifndef ENTITY_CPP
#define ENTITY_CPP

#include <SFML/Graphics.hpp>

namespace sf {

class Entity : public Sprite {
private:
    std::string m_name;
public:
    virtual void input(const Event &event);
    virtual void process(float delta);
    virtual void fixedProcess();
    virtual void onCollision(const Entity &entity);
    const std::string &getName() const {
        return m_name;
    }
};

}

#endif