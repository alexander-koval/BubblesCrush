#include "Physical.h"
#include "DisplayObject.h"

Physical::Physical(void)
    : m_velocity(0, 0)
    , m_position(0, 0)
    , m_radius(0)
    , m_isDead(false) {

}

Physical::~Physical(void) {

}

void Physical::setPosition(float x, float y) {
    m_position.x = x;
    m_position.y = y;
}

void Physical::setPosition(const sf::Vector2f &position) {
    setPosition(position.x, position.y);
}

const sf::Vector2f& Physical::getPosition(void) const {
    return m_position;
}

void Physical::setVelocity(sf::Vector2f& velocity) {
    m_velocity = velocity;
}

void Physical::setVelocity(float vx, float vy) {
    m_velocity.x = vx;
    m_velocity.y = vy;
}

const sf::Vector2f& Physical::getVelocity(void) const {
    return m_velocity;
}

void Physical::setRadius(float radius) {
    m_radius = radius;
}

float Physical::getRadius(void) const {
    return m_radius;
}

bool Physical::isDead(void) const {
    return m_isDead;
}

void Physical::setDead(bool value) {
    m_isDead = value;
}

void Physical::setGraphics(std::weak_ptr<DisplayObject> displayObject) {
    m_graphics = displayObject;
}

DisplayObject::Ptr Physical::getGraphics(void) {
    std::shared_ptr<DisplayObject> graphics = m_graphics.lock();
    return graphics;
}

void Physical::move(const sf::Vector2f &offset) {
    setPosition(m_position.x + offset.x, m_position.y + offset.y);
}

void Physical::move(float offsetX, float offsetY) {
    setPosition(m_position.x + offsetX, m_position.y + offsetY);
}

void Physical::update(sf::Time dt) {
    DisplayObject::Ptr graphics = m_graphics.lock();
    if (graphics) setPosition(graphics->getPosition());
    move(m_velocity * dt.asSeconds());
}

