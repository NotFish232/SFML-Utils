#include "../include/Entity.hpp"

using namespace std;
using namespace sf;

Entity::Entity() {
}

Entity::~Entity() {
}

void Entity::sendSignal(const string &signal) {
    m_signalCallback(signal);
}

void Entity::setName(const string &name) {
    m_name = name;
}

void Entity::input(const Event &event) {
}

void Entity::process(float delta) {
}

void Entity::fixedProcess() {
}

void Entity::onCollision(const Entity &entity) {
}

void Entity::onSignal(const string &signal) {
}

const vector<FloatRect> Entity::getBounds() const {
    return {getGlobalBounds()};
}

void Entity::setSignalCallback(const function<void(const string &)> &func) {
    m_signalCallback = func;
}

const string &Entity::getName() const {
    return m_name;
}

bool Entity::collidesWith(const Entity &other) const {
    for (const auto &bound : getBounds()) {
        for (const auto &other_bound : other.getBounds()) {
            if (bound.intersects(other_bound)) {
                return true;
            }
        }
    }
    return false;
}