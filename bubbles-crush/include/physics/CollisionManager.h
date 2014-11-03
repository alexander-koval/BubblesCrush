#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "SFML/System/NonCopyable.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/Rect.hpp"
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

class Physical;
class CollisionListener : sf::NonCopyable {
public:
    virtual void onCollideWithWall(Physical* entity, Direction::ID dir) = 0;

    virtual void onCollideWithEntity(Physical* entity1, Physical* entity2) = 0;
};

class CollisionManager : sf::NonCopyable {
public:
    CollisionManager(void);

    explicit CollisionManager(sf::FloatRect borders);

    void update(sf::Time dt);

    void add(Physical* entity);

    void remove(Physical* entity);

    void clear(void);

    void setBorders(sf::FloatRect borders);

    void setCollisionListener(CollisionListener* listener);

    bool isCollideWithBubble(Physical& entity1, Physical& entity2);

    bool isCollideWithWall(Physical& entity, const sf::FloatRect& area);

private:
    void collideWithWall(Physical* entity, const sf::FloatRect &area);

    void collideWithBubble(Physical* entity1, Physical* entity2);

    sf::Vector2f rotate(float x, float y, float sin, float cos, bool reverse);

private:
    sf::FloatRect m_borders;
    CollisionListener* m_listener;
    std::list<Physical*> m_physicList;
};

#endif // COLLISIONMANAGER_H
