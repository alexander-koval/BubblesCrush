#include "CollisionUtils.h"
#include "Utils.h"
#include "Bubble.h"
#include <cmath>

bool collideEntity(Bubble &entity1, Bubble &entity2) {
    sf::Vector2f delta = entity1.getPosition() - entity2.getPosition();
    float dist = length(delta);
    if (dist < entity1.getRadius() + entity2.getRadius()) {
        float angle = atan2(delta.y, delta.x);
        float sinf = sin(angle);
        float cosf = cos(angle);
        sf::Vector2f pos1(0.f, 0.f);
        sf::Vector2f pos2(rotate(delta.x, delta.y, sinf, cosf, true));
        sf::Vector2f vel1(rotate(entity1.getVelocity().x, entity1.getVelocity().y, sinf, cosf, true));
        sf::Vector2f vel2(rotate(entity2.getVelocity().x, entity2.getVelocity().y, sinf, cosf, true));

        float total = vel1.x - vel2.x;
//        vel1.x = (2 * vel2.x / 2);
        vel1.x = vel2.x;
        vel2.x = total + vel1.x;
        float absolute = abs(vel1.x) + abs(vel2.x);
        float overlap = (entity1.getRadius() + entity2.getRadius()) - abs(pos1.x - pos2.x);
        pos1.x += vel1.x / (absolute * overlap);
        pos2.x += vel2.x / (absolute * overlap);

        sf::Vector2f pos1F = rotate(pos1.x, pos1.y, sinf, cosf, false);
        sf::Vector2f pos2F = rotate(pos2.x, pos2.y, sinf, cosf, false);

//        entity2.setPosition(entity1.getPosition().x + pos2F.x,
//                            entity1.getPosition().y + pos2F.y);
        entity1.setPosition(entity1.getPosition().x + pos1F.x,
                            entity1.getPosition().y + pos1F.y);

        sf::Vector2f vel1F = rotate(vel1.x, vel1.y, sinf, cosf, false);
        sf::Vector2f vel2F = rotate(vel2.x, vel2.y, sinf, cosf, false);

        entity1.setVelocity(vel1F.x, vel1F.y);
        entity2.setVelocity(vel2F.x, vel2F.y);
    }
    return false;
}

bool collideWall(Bubble &entity, const sf::FloatRect &area) {
    bool result = false;
    sf::Vector2f position;
    sf::Vector2f velocity;
    position = entity.getPosition();
    velocity = entity.getVelocity();
    if (position.x + entity.getRadius() > area.width) {
        entity.setPosition(area.width - entity.getRadius(), position.y);
        entity.setVelocity(-velocity.x, velocity.y);
        result = true;
    } else if (position.x - entity.getRadius() < area.left) {
        entity.setPosition(entity.getRadius(), position.y);
        entity.setVelocity(-velocity.x, velocity.y);
        result = true;
    }
    position = entity.getPosition();
    velocity = entity.getVelocity();
    if (position.y + entity.getRadius() > area.height) {
        entity.setPosition(position.x, area.height - entity.getRadius());
        entity.setVelocity(velocity.x, -velocity.y);
        result = true;
    } else if (position.y - entity.getRadius() < area.top) {
        entity.setPosition(position.x, entity.getRadius());
        entity.setVelocity(velocity.x, -velocity.y);
        result = true;
    }
    return result;
}

bool isCollideWithWall(Bubble &entity, const sf::FloatRect &area) {
    sf::Vector2f position = entity.getPosition();
    return ((position.x + entity.getRadius() > area.width) ||
            (position.x - entity.getRadius() < area.left) ||
            (position.y + entity.getRadius() > area.height) ||
            (position.y - entity.getRadius() < area.top));
}

sf::Vector2f rotate(float x, float y, float sin, float cos, bool reverse) {
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
