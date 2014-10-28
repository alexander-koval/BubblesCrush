#ifndef BUBBLE_H
#define BUBBLE_H

#include "Entity.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Bubble : public Entity {
public:
    explicit Bubble(float radius, sf::Color color);

    float getMaxSpeed(void) const;

    float getRadius(void) const;

protected:
    virtual void updateCurrent(sf::Time dt);
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::CircleShape m_shape;
};


#endif // BUBBLE_H
