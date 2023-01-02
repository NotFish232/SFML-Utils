#ifndef MAINLOOP_CPP
#define MAINLOOP_CPP

#include "Entity.cpp"
#include <SFML/Graphics.hpp>
#include <vector>

namespace sf {

class MainLoop {
private:
    RenderWindow m_window;
    std::vector<Entity> m_entities;
    std::vector<Drawable> m_drawables;
    int m_fps;

public:
    MainLoop(const std::string &title, int width, int height, int fps)
        : m_window(VideoMode(width, height), title) {
        m_fps = fps;
    }
    void addEntity(const Entity &entity) {
        m_entities.push_back(entity);
    }

    void addDrawable(const Drawable &drawable) {
        m_drawables.push_back(drawable);
    }

    void checkCollisions() {
        for (int i = 0; i < m_entities.size(); ++i) {
            for (int j = i + 1; j < m_entities.size(); ++j) {
                Entity &entity1 = m_entities[i], &entity2 = m_entities[j];
                if (entity1.getGlobalBounds().intersects(entity2.getGlobalBounds())) {
                    entity1.onCollision(entity2);
                    entity2.onCollision(entity1);
                }
            }
        }
    }

    void run() {
        Clock clock;
        Time last_time;
        while (m_window.isOpen()) {
            Event event;
            while (m_window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    m_window.close();
                }
                for (auto &entity : m_entities) {
                    entity.input(event);
                }
            }
            checkCollisions();

            float delta = (clock.getElapsedTime() - last_time).asSeconds();
            last_time = clock.getElapsedTime();
            for (auto &entity : m_entities) {
                entity.process(delta);
            }

            if (clock.getElapsedTime().asMilliseconds() > (1000 / m_fps)) {
                last_time = Time();
                clock.restart();

                for (auto &entity: m_entities) {
                    entity.fixedProcess();
                }

                m_window.clear(Color::White);
                for (const auto &drawable : m_drawables) {
                    m_window.draw(drawable);
                }
                for (const auto &entity : m_entities) {
                    m_window.draw(entity);
                }

                m_window.display();
            }
        }
    }
};

};

#endif
