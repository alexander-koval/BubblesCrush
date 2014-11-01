#ifndef UTILS_H
#define UTILS_H

#include "SFML/System/Vector2.hpp"
#include <string>
#include <sstream>

namespace sf {
class Text;
class Sprite;
class Shape;
}

void centerOrigin(sf::Shape& shape);

void centerOrigin(sf::Sprite& sprite);

void centerOrigin(sf::Text& text);

float rad2deg(float radian);

float deg2rad(float degree);

float randomRange(float min, float max);

int randomRange(int min, int max);

float length(sf::Vector2f vector);

sf::Vector2f unitVector(sf::Vector2f vector);

template <typename T>
std::string to_string(T value) {
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}



#endif // UTILS_H
