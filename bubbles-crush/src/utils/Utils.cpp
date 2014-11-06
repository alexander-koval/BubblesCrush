#include "Utils.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Text.hpp"
#include <cfloat>
#include <cassert>

std::default_random_engine eng((std::random_device())());

void centerOrigin(sf::Shape& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void centerOrigin(sf::Sprite& sprite) {
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

void centerOrigin(sf::Text& text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(std::floor(bounds.width / 2.f), std::floor(bounds.height / 2.f));
}

float rad2deg(float radian) {
    return 180.f / M_PI * radian;
}

float deg2rad(float degree) {
    return M_PI / 180.f * degree;
}

float randomRange(float min, float max) {
    std::uniform_real_distribution<> distr(min, max);
    return distr(eng);
}

int randomRange(int min, int max) {
    std::uniform_int_distribution<> distr(min, max);
    return distr(eng);
}

bool isZero(sf::Vector2f vector) {
    return (abs(vector.x) < FLT_EPSILON && abs(vector.y) < FLT_EPSILON);
}

float getLength(sf::Vector2f vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float setLength(float length, sf::Vector2f vector) {
    if (!isZero(vector)) {
        float angle = getRadians(vector);
        vector.x = length * std::cos(angle);
        vector.y = length * std::sin(angle);
    }
    return length;
}

sf::Vector2f unitVector(sf::Vector2f vector) {
    assert(vector != sf::Vector2f(0.f, 0.f));
    return vector / getLength(vector);
}

float getRadians(sf::Vector2f vector) {
    if (isZero(vector)) return 0.f;
    return std::atan2(vector.x, vector.y);
}


