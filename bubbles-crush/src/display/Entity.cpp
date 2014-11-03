#include "Entity.h"
#include "DisplayObject.h"

Entity::Entity(void)
    : Physical()
    , m_velocity(0, 0)
    , m_position(0, 0)
    , m_displayObject(nullptr)
    , m_radius(0)
    , m_isDead(false) {

}

Entity::~Entity(void) {

}

void Entity::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
}

void Entity::setPosition(const sf::Vector2f &position) {
    setPosition(position.x, position.y);
}

const sf::Vector2f& Entity::getPosition(void) const {
    return m_position;
}

void Entity::setVelocity(sf::Vector2f& velocity) {
    m_velocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
    m_velocity.x = vx;
    m_velocity.y = vy;
}

const sf::Vector2f& Entity::getVelocity(void) const {
    return m_velocity;
}

void Entity::setRadius(float radius) {
    m_radius = radius;
}

float Entity::getRadius(void) const {
    return m_radius;
}

bool Entity::isDead(void) const {
    return m_isDead;
}

void Entity::setDead(bool value) {
    m_isDead = value;
}

void Entity::setGraphics(DisplayObject *displayObject) {
    m_displayObject = displayObject;
}

DisplayObject* Entity::getGraphics(void) {
    return m_displayObject;
}

void Entity::move(const sf::Vector2f &offset) {
    setPosition(m_position.x + offset.x, m_position.y + offset.y);
}

void Entity::move(float offsetX, float offsetY) {
    setPosition(m_position.x + offsetX, m_position.y + offsetY);
}

void Entity::updateCurrent(sf::Time dt) {
    if (m_displayObject) setPosition(m_displayObject->getPosition());
    move(m_velocity * dt.asSeconds());
}
