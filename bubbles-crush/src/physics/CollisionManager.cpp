#include "CollisionManager.h"
#include "Physical.h"
#include "Utils.h"

CollisionManager::CollisionManager(void)
    : sf::NonCopyable()
    , m_borders()
    , m_listener(nullptr) {

}

CollisionManager::CollisionManager(sf::FloatRect borders)
    : sf::NonCopyable()
    , m_borders(borders)
    , m_listener(nullptr) {

}

void CollisionManager::update(sf::Time dt) {
    std::list<Physical*>::iterator it2;
    std::list<Physical*>::iterator it1 = m_physicList.begin();
    while (it1 != m_physicList.end()) {
        Physical* entity1 = *it1;
        if (isCollideWithWall(*entity1, m_borders)) {
            this->collideWithWall(entity1, m_borders);
        }
        it2 = ++it1;
        while (it2 != m_physicList.end()) {
            Physical* entity2 = *it2;
            if (isCollideWithBubble(*entity1, *entity2)) {
                this->collideWithBubble(entity1, entity2);
                if (m_listener) m_listener->onCollideWithEntity(entity1, entity2);
            }
            it2++;
        }
    }
    m_physicList.remove_if([](Physical* bubble) -> bool {
        return bubble->isDead();
    });
}

void CollisionManager::add(Physical* entity) {
    m_physicList.push_back(entity);
}

void CollisionManager::remove(Physical* entity) {
    entity->setDead(true);
}

void CollisionManager::clear(void) {
    m_physicList.clear();
}

void CollisionManager::collideWithWall(Physical *entity, const sf::FloatRect &area) {
    sf::Vector2f position = entity->getPosition();
    sf::Vector2f velocity = entity->getVelocity();
    if (position.x + entity->getRadius() > area.width) {
        velocity.x = -velocity.x;
        position.x = area.width - entity->getRadius();
        if (m_listener) m_listener->onCollideWithWall(entity, Direction::ID::Right);
    } else if (position.x - entity->getRadius() < area.left) {
        velocity.x = -velocity.x;
        position.x = entity->getRadius();
        if (m_listener) m_listener->onCollideWithWall(entity, Direction::ID::Left);
    }
    if (position.y + entity->getRadius() > area.height) {
        velocity.y = -velocity.y;
        position.y = area.height - entity->getRadius();
        if (m_listener) m_listener->onCollideWithWall(entity, Direction::ID::Bottom);
    } else if (position.y - entity->getRadius() < area.top) {
        velocity.y = -velocity.y;
        position.y = entity->getRadius();
        if (m_listener) m_listener->onCollideWithWall(entity, Direction::ID::Top);
    }
    entity->setPosition(position);
    entity->setVelocity(velocity);
}

void CollisionManager::collideWithBubble(Physical *entity1, Physical *entity2) {
    sf::Vector2f delta = entity2->getPosition() - entity1->getPosition();
    float dist = getLength(delta);
    if (dist < entity1->getRadius() + entity2->getRadius()) {
        float angle = atan2(delta.y, delta.x);
        float sinf = sin(angle);
        float cosf = cos(angle);
        sf::Vector2f pos1(0.f, 0.f);
        sf::Vector2f pos2(rotate(delta.x, delta.y, sinf, cosf, true));
        sf::Vector2f vel1(rotate(entity1->getVelocity().x,
                                 entity1->getVelocity().y, sinf, cosf, true));
        sf::Vector2f vel2(rotate(entity2->getVelocity().x,
                                 entity2->getVelocity().y, sinf, cosf, true));

        float total = vel1.x - vel2.x;
        vel1.x = vel2.x;
        vel2.x = (total + vel1.x) * 0.5;
        float absolute = fabs(vel1.x) + fabs(vel2.x);
        float overlap = (entity1->getRadius() + entity2->getRadius()) -
                fabs(pos1.x - pos2.x);
        pos1.x += vel1.x / absolute * overlap;
        pos2.x += vel2.x / absolute * overlap;

        sf::Vector2f pos1F = rotate(pos1.x, pos1.y, sinf, cosf, false);
        sf::Vector2f pos2F = rotate(pos2.x, pos2.y, sinf, cosf, false);

        entity2->setPosition(entity1->getPosition().x + pos2F.x,
                             entity1->getPosition().y + pos2F.y);

        entity1->setPosition(entity1->getPosition().x + pos1F.x,
                             entity1->getPosition().y + pos1F.y);

        vel2.x *= 2;
        sf::Vector2f vel1F = rotate(vel1.x, vel1.y, sinf, cosf, false);
        sf::Vector2f vel2F = rotate(vel2.x, vel2.y, sinf, cosf, false);

        entity1->setVelocity(vel1F.x, vel1F.y);
        entity2->setVelocity(vel2F.x, vel2F.y);
    }
}

bool CollisionManager::isCollideWithBubble(Physical& entity1, Physical& entity2) {
    sf::Vector2f delta = entity1.getPosition() - entity2.getPosition();
    float dist = getLength(delta);
    return (dist < entity1.getRadius() + entity2.getRadius());
}

bool CollisionManager::isCollideWithWall(Physical &entity, const sf::FloatRect &area) {
    sf::Vector2f position = entity.getPosition();
    return ((position.x + entity.getRadius() > area.width) ||
            (position.x - entity.getRadius() < area.left) ||
            (position.y + entity.getRadius() > area.height) ||
            (position.y - entity.getRadius() < area.top));
}

sf::Vector2f CollisionManager::rotate(float x, float y, float sin, float cos, bool reverse) {
    sf::Vector2f result(0.f, 0.f);
    if (reverse) {
        result.x = x * cos + y * sin;
        result.y = y * cos - x * sin;
    } else {
        result.x = x * cos - y * sin;
        result.y = y * cos + x * sin;
    }
    return result;
}


void CollisionManager::setBorders(sf::FloatRect borders) {
    m_borders = borders;
}

void CollisionManager::setCollisionListener(CollisionListener *listener) {
    m_listener = listener;
}

