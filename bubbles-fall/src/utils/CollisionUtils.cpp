#include "CollisionUtils.h"
#include "Utils.h"
#include "Bubble.h"
#include <cmath>

bool isCollideWithBubble(Bubble& entity1, Bubble& entity2) {
    sf::Vector2f delta = entity1.getPosition() - entity2.getPosition();
    float dist = length(delta);
    return (dist < entity1.getRadius() + entity2.getRadius());
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
