#ifndef ENTITY_H
#define ENTITY_H

#include "Physical.h"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Transformable.hpp"

class Entity : public Physical {
public:
    explicit Entity(void);

    virtual ~Entity(void);

    virtual void setPosition(float x, float y);

    virtual void setPosition(const sf::Vector2f& position);

    virtual const sf::Vector2f& getPosition(void) const;

    virtual void setVelocity(sf::Vector2f& velocity);

    virtual void setVelocity(float vx, float vy);

    virtual const sf::Vector2f& getVelocity(void) const;

    virtual void setRadius(float radius);

    virtual float getRadius(void) const;

    virtual bool isDead(void) const;

    virtual void setDead(bool value);

    virtual void setGraphics(DisplayObject* displayObject);

    virtual DisplayObject* getGraphics(void);

    void move(float offsetX, float offsetY);

    void move(const sf::Vector2f& offset);

    virtual void updateCurrent(sf::Time dt);

protected:

private:
    sf::Vector2f m_velocity;
    sf::Vector2f m_position;
    DisplayObject* m_displayObject;
    float m_radius;
    bool m_isDead;
};

#endif // ENTITY_H
