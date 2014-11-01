#ifndef BUBBLE_H
#define BUBBLE_H

#include "Entity.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Bubble : public Entity {
public:
    explicit Bubble(void);

    explicit Bubble(float radius, sf::Color color);

    void setRadius(float radius);

    float getRadius(void) const;

    void setColor(const sf::Color& color);

    const sf::Color& getColor(void) const;

    sf::FloatRect getLocalBounds(void) const;

    sf::FloatRect getGlobalBounds(void) const;

protected:
    virtual void updateCurrent(sf::Time dt);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::CircleShape m_shape;
};


#endif // BUBBLE_H
