#include "Sprite.h"
#include "SFML/Graphics/RenderTarget.hpp"

Sprite::Sprite(void)
    : DisplayObject()
    , m_sprite() {

}

Sprite::Sprite(const sf::Texture &texture)
    : DisplayObject()
    , m_sprite(texture) {

}


Sprite::Sprite(const sf::Texture &texture, const sf::IntRect &rectangle)
    : DisplayObject()
    , m_sprite(texture, rectangle) {

}

Sprite::~Sprite(void) {

}

void Sprite::setTexture(const sf::Texture &texture, bool resetRect) {
    m_sprite.setTexture(texture, resetRect);
}

void Sprite::setTextureRect(const sf::IntRect &rectangle) {
    m_sprite.setTextureRect(rectangle);
}

void Sprite::setColor(const sf::Color &color) {
    m_sprite.setColor(color);
}

const sf::Texture* Sprite::getTexture(void) const {
    return m_sprite.getTexture();
}

const sf::IntRect& Sprite::getTextureRect(void) const {
    return m_sprite.getTextureRect();
}

const sf::Color& Sprite::getColor(void) const {
    return m_sprite.getColor();
}

sf::FloatRect Sprite::getLocalBounds(void) const {
    return m_sprite.getLocalBounds();
}

sf::FloatRect Sprite::getGlobalBounds(void) const {
    return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void Sprite::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
