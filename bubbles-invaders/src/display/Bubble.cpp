#include "Bubble.h"
#include "Utils.h"
#include "CollisionUtils.h"
#include "SFML/Graphics/RenderTarget.hpp"

Bubble::Bubble(float radius, sf::Color color)
    : Entity()
    , m_shape(sf::CircleShape(radius)) {
    centerOrigin(m_shape);
    m_shape.setFillColor(color);
}

float Bubble::getMaxSpeed(void) const  {
    return 100.f;
}

float Bubble::getRadius(void) const {
    return m_shape.getRadius();
}

void Bubble::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
}

void Bubble::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}

void Bubble::collideWithWall(const sf::FloatRect& area) {
    collideWall(*this, area);
}

void Bubble::collideWithBubble(Bubble *bubble) {
    collideEntity(*this, *bubble);
}
