#ifndef ENTITY_H
#define ENTITY_H

#include "DisplayObject.h"
#include "Physical.h"

class Entity : public DisplayObject, public Physical {
public:
    explicit Entity(void);

    void setVelocity(sf::Vector2f velocity);

    void setVelocity(float vx, float vy);

    sf::Vector2f getVelocity(void) const;

    virtual void collide(Physical &target1, Physical &target2) {}

protected:
    virtual void updateCurrent(sf::Time dt);

private:
    sf::Vector2f m_velocity;
};

#endif // ENTITY_H
