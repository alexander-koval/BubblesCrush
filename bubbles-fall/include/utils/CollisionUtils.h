#ifndef COLLISIONUTILS_H
#define COLLISIONUTILS_H

#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Vector2.hpp"

class Bubble;

bool isCollideWithBubble(Bubble& entity1, Bubble& entity2);

bool isCollideWithWall(Bubble& entity, const sf::FloatRect& area);

sf::Vector2f rotate(float x, float y, float sin, float cos, bool reverse);

#endif // COLLISIONUTILS_H
