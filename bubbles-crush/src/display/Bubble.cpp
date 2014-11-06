#include "Bubble.h"
#include "Utils.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

Bubble::Bubble(void)
    : Shape()
    , m_entity()
    , m_circleShape(nullptr) {
    std::unique_ptr<sf::CircleShape> shape(new sf::CircleShape());
    m_circleShape = shape.get();
    Shape::setShape(std::move(shape));
    centerOrigin(*m_circleShape);
    m_entity.setGraphics(this);
}

Bubble::Bubble(float radius, const sf::Color& color)
    : Shape()
    , m_entity()
    , m_circleShape(nullptr) {
    std::unique_ptr<sf::CircleShape> shape(new sf::CircleShape(radius));
    m_circleShape = shape.get();
    centerOrigin(*m_circleShape);
    Shape::setFillColor(color);
    m_entity.setRadius(radius);
    m_entity.setGraphics(this);
}

void Bubble::setVelocity(sf::Vector2f &velocity) {
    m_entity.setVelocity(velocity);
}

void Bubble::setVelocity(float vx, float vy) {
    m_entity.setVelocity(vx, vy);
}

const sf::Vector2f& Bubble::getVelocity(void) const {
    return m_entity.getVelocity();
}

void Bubble::setRadius(float radius) {
    m_circleShape->setRadius(radius);
    m_entity.setRadius(radius);
    centerOrigin(*m_circleShape);
}

float Bubble::getRadius(void) const {
    return m_circleShape->getRadius();
}

bool Bubble::isDead(void) const {
    return m_entity.isDead();
}

void Bubble::setDead(bool value) {
    return m_entity.setDead(value);
}

Physical& Bubble::getPhysics(void) {
    return m_entity;
}

void Bubble::updateCurrent(sf::Time dt) {
//    m_entity.setPosition(this->getPosition());
    m_entity.update(dt);
    setPosition(m_entity.getPosition());
}
