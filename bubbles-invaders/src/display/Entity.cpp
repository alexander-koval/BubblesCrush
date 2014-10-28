#include "Entity.h"
#include <cassert>

Entity::Entity(void)
    : DisplayObject(),
      m_velocity(0, 0),
      m_isDead(false) {

}

void Entity::setVelocity(sf::Vector2f velocity) {
    m_velocity = velocity;
}

void Entity::setVelocity(float vx, float vy) {
    m_velocity.x = vx;
    m_velocity.y = vy;
}

sf::Vector2f Entity::getVelocity(void) const {
    return m_velocity;
}

bool Entity::isDead(void) const {
    return m_isDead;
}

void Entity::setDead(bool value) {
    m_isDead = value;
}

void Entity::updateCurrent(sf::Time dt) {
    move(m_velocity * dt.asSeconds());
}
