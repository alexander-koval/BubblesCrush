#include "Sprite.h"
#include "PostEffect.h"
#include "SFML/Graphics/RenderTarget.hpp"

Sprite::Sprite(const sf::Texture &texture)
    : DisplayObject()
    , m_sprite(texture) {
    if (PostEffect::isSupported()) {
        m_sprite.setColor(sf::Color(40, 40, 40, 255));
    }
}

Sprite::Sprite(const sf::Texture &texture, const sf::IntRect &textureRect)
    : DisplayObject()
    , m_sprite(texture, textureRect) {

}

void Sprite::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_sprite, states);
}
