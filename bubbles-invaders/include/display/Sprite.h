#ifndef SPRITE_H
#define SPRITE_H

#include "DisplayObject.h"
#include "SFML/Graphics/Sprite.hpp"

class Sprite : public DisplayObject {
public:
    explicit Sprite(void);

    explicit Sprite(const sf::Texture& texture);

    explicit Sprite(const sf::Texture& texture, const sf::IntRect& rectangle);

    virtual ~Sprite(void);

    void setTexture(const sf::Texture& texture, bool resetRect = false);

    void setTextureRect(const sf::IntRect& rectangle);

    void setColor(const sf::Color& color);

    const sf::Texture* getTexture(void) const;

    const sf::IntRect& getTextureRect(void) const;

    const sf::Color& getColor(void) const;

    sf::FloatRect getLocalBounds(void) const;

    sf::FloatRect getGlobalBounds(void) const;

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite m_sprite;
};


#endif // SPRITE_H
