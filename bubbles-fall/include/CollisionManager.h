#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "SFML/System/NonCopyable.hpp"
#include "Bubble.h"
#include <memory>
#include <list>

namespace Direction {
enum class ID {
    Top,
    Bottom,
    Left,
    Right
};
}

class CollisionListener : sf::NonCopyable {
public:
    virtual void onCollideWithWall(Bubble* entity, Direction::ID dir) = 0;

    virtual void onCollideWithEntity(Bubble* entity1, Entity* entity2) = 0;
};

class CollisionManager : sf::NonCopyable {
public:
    CollisionManager(void);

    explicit CollisionManager(sf::FloatRect borders);

    void update(sf::Time dt);

    void add(Bubble* entity);

    void remove(Bubble* entity);

    void clear(void);

    void setBorders(sf::FloatRect borders);

    void setCollisionListener(CollisionListener* listener);

private:
    void collideWithWall(Bubble* entity, const sf::FloatRect &area);

    void collideWithBubble(Bubble* entity1, Bubble* entity2);

private:
    sf::FloatRect m_borders;
    CollisionListener* m_listener;
    std::list<Bubble*> m_physicList;
};

#endif // COLLISIONMANAGER_H
