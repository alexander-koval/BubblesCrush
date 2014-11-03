#include "Shape.h"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/RenderTarget.hpp"

Shape::Shape(void)
    : DisplayObject()
    , m_shape(nullptr) {

}

Shape::Shape(std::unique_ptr<sf::Shape> shape)
    : DisplayObject()
    , m_shape(std::move(shape)) {

}

void Shape::setShape(std::unique_ptr<sf::Shape> shape) {
    m_shape = std::move(shape);
}

void Shape::setTexture(const sf::Texture *texture, bool resetRect) {
    m_shape->setTexture(texture, resetRect);
}

void Shape::setTextureRect(const sf::IntRect &rect) {
    m_shape->setTextureRect(rect);
}

void Shape::setFillColor(const sf::Color &color) {
    m_shape->setFillColor(color);
}

void Shape::setOutlineThickness(float thickness) {
    m_shape->setOutlineThickness(thickness);
}

const sf::Shape* Shape::getShape(void) const {
    return m_shape.get();
}

const sf::Texture* Shape::getTexture(void) const {
    return m_shape->getTexture();
}

const sf::IntRect& Shape::getTextureRect(void) const {
    return m_shape->getTextureRect();
}

const sf::Color& Shape::getFillColor(void) const {
    return m_shape->getFillColor();
}

const sf::Color& Shape::getOutlineColor(void) const {
    return m_shape->getOutlineColor();
}

float Shape::getOutlineThickness(void) const {
    return m_shape->getOutlineThickness();
}

unsigned int Shape::getPointCount(void) const {
    return m_shape->getPointCount();
}

sf::Vector2f Shape::getPoint(unsigned int index) const {
    return m_shape->getPoint(index);
}

sf::FloatRect Shape::getLocalBounds(void) const {
    return m_shape->getLocalBounds();
}

sf::FloatRect Shape::getGlobalBounds(void) const {
    return getTransform().transformRect(m_shape->getGlobalBounds());
}

void Shape::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*m_shape, states);
}


