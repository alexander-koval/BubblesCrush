#ifndef PHYSICAL_H
#define PHYSICAL_H

#include "SFML/System/Vector2.hpp"

class DisplayObject;
class Physical {
public:
    virtual ~Physical(void) {}

    virtual void setPosition(float x, float y) = 0;

    virtual void setPosition(const sf::Vector2f& position) = 0;

    virtual const sf::Vector2f& getPosition(void) const = 0;

    virtual void setVelocity(sf::Vector2f& velocity) = 0;

    virtual void setVelocity(float vx, float vy) = 0;

    virtual const sf::Vector2f& getVelocity(void) const = 0;

    virtual void setRadius(float radius) = 0;

    virtual float getRadius(void) const = 0;

    virtual bool isDead(void) const = 0;

    virtual void setDead(bool value) = 0;

    virtual void setGraphics(DisplayObject* displayObject) = 0;

    virtual DisplayObject* getGraphics(void) = 0;
};

#endif // PHYSICAL_H
