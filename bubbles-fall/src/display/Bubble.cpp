#include "Bubble.h"
#include "Utils.h"
#include "SFML/Graphics/RenderTarget.hpp"

Bubble::Bubble(void)
    : Entity()
    , m_shape(sf::CircleShape()) {
    centerOrigin(m_shape);
}

Bubble::Bubble(float radius, sf::Color color)
    : Entity()
    , m_shape(sf::CircleShape(radius)) {
    centerOrigin(m_shape);
    m_shape.setFillColor(color);
}

void Bubble::setRadius(float radius) {
    m_shape.setRadius(radius);
    centerOrigin(m_shape);
}

float Bubble::getRadius(void) const {
    return m_shape.getRadius();
}

void Bubble::setColor(const sf::Color& color) {
    m_shape.setFillColor(color);
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
