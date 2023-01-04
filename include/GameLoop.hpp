#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace sf {

class GameLoop {
private:
    RenderWindow m_window;
    std::vector<Entity *> m_entities;
    std::vector<Drawable *> m_drawables;
    int m_fps;

public:
    GameLoop(const std::string &title, int width, int height, int fps);
    ~GameLoop();

    void addEntity(Entity &entity);
    void addDrawable(Drawable &drawable);
    void signalCallback(const std::string &signal) const;
    Entity *getEntityCallback(const std::string &name) const;
    void checkCollisions();
    void run();
};

}

#endif