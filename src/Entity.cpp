#ifndef ENTITY_CPP
#define ENTITY_CPP

#include <SFML/Graphics.hpp>
#include <functional>

namespace sf {

class Entity : public Sprite {
private:
    std::string m_name;
    std::function<void(const std::string &)> m_signalCallback;

public:

    virtual void input(const Event &event) = 0;
    virtual void process(float delta) = 0;
    virtual void fixedProcess() = 0;
    virtual void onCollision(const Entity &entity) = 0;
    virtual void onSignal(const std::string &signal) = 0;

    void sendSignal(const std::string &signal) {
        m_signalCallback(signal);
    }

    void setSignalCallback(const std::function<void(const std::string &)> &func) {
        m_signalCallback = func;
    }

    const std::string &getName() const {
        return m_name;
    }

    void setName(const std::string &name) {
        m_name = name;
    }
};

}

#endif