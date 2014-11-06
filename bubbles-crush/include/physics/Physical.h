#ifndef PHYSICAL_H
#define PHYSICAL_H

#include "SFML/System/Time.hpp"
#include "SFML/System/Vector2.hpp"

class DisplayObject;
class Physical {
public:
    Physical(void);

    ~Physical(void);

    void setPosition(float x, float y);

    void setPosition(const sf::Vector2f& position);

    const sf::Vector2f& getPosition(void) const;

    void setVelocity(sf::Vector2f& velocity);

    void setVelocity(float vx, float vy);

    const sf::Vector2f& getVelocity(void) const;

    void setRadius(float radius);

    float getRadius(void) const;

    bool isDead(void) const;

    void setDead(bool value);

    void setGraphics(DisplayObject* displayObject);

    DisplayObject* getGraphics(void);

    void move(float offsetX, float offsetY);

    void move(const sf::Vector2f& offset);

    void update(sf::Time dt);

private:
    sf::Vector2f m_velocity;
    sf::Vector2f m_position;
    DisplayObject* m_displayObject;
    float m_radius;
    bool m_isDead;
};

#endif // PHYSICAL_H
