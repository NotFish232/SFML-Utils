#include "../include/MainLoop.hpp"

using namespace std;
using namespace sf;

MainLoop::MainLoop(const string &title, int width, int height, int fps)
    : m_window(VideoMode(width, height), title) {
    m_fps = fps;
}

MainLoop::~MainLoop() {
}

void MainLoop::MainLoop::addEntity(Entity &entity) {
    using placeholders::_1;
    entity.setSignalCallback(bind(&MainLoop::signalCallback, this, _1));
    entity.setGetEntityCallback(bind(&MainLoop::getEntityCallback, this, _1));
    m_entities.push_back(&entity);
}

void MainLoop::addDrawable(Drawable &drawable) {
    m_drawables.push_back(&drawable);
}

void MainLoop::signalCallback(const string &signal) const {
    for (auto &entity : m_entities) {
        entity->onSignal(signal);
    }
}

Entity *MainLoop::getEntityCallback(const string &name) const {
    for (const auto &entity : m_entities) {
        if (entity->getName() == name) {
            return entity;
        }
    }
    return nullptr;
}

void MainLoop::checkCollisions() {
    for (int i = 0; i < m_entities.size(); ++i) {
        for (int j = i + 1; j < m_entities.size(); ++j) {
            auto a = m_entities[i], b = m_entities[j];
            if (a->collidesWith(*b)) {
                a->onCollision(*b);
                b->onCollision(*a);
            }
        }
    }
}

void MainLoop::run() {
    Clock clock;
    Time last_time;
    while (m_window.isOpen()) {
        Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                m_window.close();
            }
            for (auto &entity : m_entities) {
                entity->input(event);
            }
        }
        checkCollisions();

        float delta = (clock.getElapsedTime() - last_time).asSeconds();
        last_time = clock.getElapsedTime();
        for (auto &entity : m_entities) {
            entity->process(delta);
        }

        if (clock.getElapsedTime().asMilliseconds() > (1000 / m_fps)) {
            last_time = Time();
            clock.restart();

            for (auto &entity : m_entities) {
                entity->fixedProcess();
            }

            m_window.clear(Color::White);

            for (const auto &drawable : m_drawables) {
                m_window.draw(*drawable);
            }
            for (const auto &entity : m_entities) {
                m_window.draw(*entity);
            }

            m_window.display();
        }
    }
}