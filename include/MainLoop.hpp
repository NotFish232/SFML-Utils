#ifndef MAINLOOP_HPP
#define MAINLOOP_HPP

#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace sf {

class MainLoop {
private:
    RenderWindow m_window;
    std::vector<Entity *> m_entities;
    std::vector<Drawable *> m_drawables;
    int m_fps;

public:
    MainLoop(const std::string &title, int width, int height, int fps);
    ~MainLoop();

    void addEntity(Entity &entity);
    void addDrawable(Drawable &drawable);
    void signalCallback(const std::string &signal) const;
    Entity *getEntityCallback(const std::string &name) const;
    void checkCollisions();
    void run();
};

}

#endif