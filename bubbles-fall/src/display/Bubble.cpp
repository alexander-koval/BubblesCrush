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

const sf::Color& Bubble::getColor(void) const {
    return m_shape.getFillColor();
}

sf::FloatRect Bubble::getLocalBounds(void) const {
    return m_shape.getLocalBounds();
}

sf::FloatRect Bubble::getGlobalBounds(void) const {
    return getTransform().transformRect(m_shape.getGlobalBounds());
}

void Bubble::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
}

void Bubble::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_shape, states);
}
