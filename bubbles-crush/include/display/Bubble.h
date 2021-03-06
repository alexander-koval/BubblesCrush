#ifndef BUBBLE_H
#define BUBBLE_H

#include "Shape.h"
#include "Physical.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/CircleShape.hpp"

class Bubble : public Shape {
public:
    explicit Bubble(void);

    explicit Bubble(float radius, const sf::Color& color);

    virtual void initialize(void);

    virtual void setVelocity(sf::Vector2f& velocity);

    virtual void setVelocity(float vx, float vy);

    virtual const sf::Vector2f& getVelocity(void) const;

    virtual void setRadius(float radius);

    virtual float getRadius(void) const;

    virtual bool isDead(void) const;

    virtual void setDead(bool value);

    void sync(void) {
        m_entity.setPosition(this->getPosition());
    }

    Physical& getPhysics(void);

protected:
    virtual void updateCurrent(sf::Time dt);
//    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    Physical m_entity;
    sf::CircleShape* m_circleShape;
};


#endif // BUBBLE_H
