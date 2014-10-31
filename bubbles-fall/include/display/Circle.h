#ifndef CIRCLE_H
#define CIRCLE_H

#include "SFML/Graphics/Shape.hpp"

class Circle : public sf::Shape {
public:
    explicit Circle(float radius = 0, unsigned int pointCount = 30)
};

#endif // CIRCLE_H
