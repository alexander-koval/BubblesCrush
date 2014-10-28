#include "Sprite.h"
#include "SFML/Graphics/RenderTarget.hpp"

Sprite::Sprite(const sf::Texture &texture)
    : DisplayObject()
    , m_sprite(texture) {

}

Sprite::Sprite(const sf::Texture &texture, const sf::IntRect &textureRect)
    : DisplayObject()
    , m_sprite(texture, textureRect) {

}

void Sprite::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
