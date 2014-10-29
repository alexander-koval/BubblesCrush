#include "Utils.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Text.hpp"
#include <random>
#include <cassert>
#include <cmath>
#include <ctime>

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
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(min, max);
    return distr(gen);
}

int randomRange(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

float length(sf::Vector2f vector) {
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

sf::Vector2f unitVector(sf::Vector2f vector) {
    assert(vector != sf::Vector2f(0.f, 0.f));
    return vector / length(vector);
}

