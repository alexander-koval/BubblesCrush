#ifndef ENTITY_H
#define ENTITY_H

#include "DisplayObject.h"

class Entity : public DisplayObject {
public:
    explicit Entity(void);

    void setVelocity(sf::Vector2f velocity);

    void setVelocity(float vx, float vy);

    sf::Vector2f getVelocity(void) const;

    virtual bool isDead(void) const;

    virtual void setDead(bool value);

protected:
    virtual void updateCurrent(sf::Time dt);

private:
    sf::Vector2f m_velocity;
    bool m_isDead;
};

#endif // ENTITY_H
