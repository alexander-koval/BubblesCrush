#ifndef SPRITE_H
#define SPRITE_H

#include "DisplayObject.h"
#include "SFML/Graphics/Sprite.hpp"

class Sprite : public DisplayObject {
public:
    explicit Sprite(const sf::Texture& texture);
    explicit Sprite(const sf::Texture& texture, const sf::IntRect& textureRect);

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite m_sprite;
};


#endif // SPRITE_H
