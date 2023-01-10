#include "../include/Entity.hpp"

using namespace std;
using namespace sf;

Entity::Entity(bool visibility) {
    m_visible = visibility;
}

Entity::~Entity() {
}

void Entity::init() {
}

void Entity::emitSignal(const string &signal) const {
    m_signalCallback(signal);
}

Entity *Entity::getEntity(const string &name) const {
    return m_getEntityCallback(name);
}

void Entity::setName(const string &name) {
    m_name = name;
}

void Entity::showSelf() {
    m_visible = true;
}

void Entity::hideSelf() {
    m_visible = false;
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

bool Entity::isVisible() const {
    return m_visible;
}

const vector<FloatRect> Entity::getBounds() const {
    return {};
}

void Entity::setSignalCallback(const function<void(const string &)> &func) {
    m_signalCallback = func;
}

void Entity::setGetEntityCallback(const function<Entity *(const string &)> &func) {
    m_getEntityCallback = func;
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