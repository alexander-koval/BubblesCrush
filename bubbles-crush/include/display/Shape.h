#ifndef SHAPE_H
#define SHAPE_H

#include "DisplayObject.h"
#include "SFML/Graphics/Shape.hpp"

namespace sf {
class Color;
class Shape;
}

class Shape : public DisplayObject {
public:
    typedef std::unique_ptr<sf::Shape> Ptr;

    explicit Shape(void);

    explicit Shape(Ptr shape);

    void setShape(std::unique_ptr<sf::Shape> shape);

    void setTexture(const sf::Texture* texture, bool resetRect = false);

    void setTextureRect(const sf::IntRect& rect);

    void setFillColor(const sf::Color& color);

    void setOutlineThickness(float thickness);

    const sf::Shape* getShape(void) const;

    const sf::Texture* getTexture(void) const;

    const sf::IntRect& getTextureRect(void) const;

    const sf::Color& getFillColor(void) const;

    const sf::Color& getOutlineColor(void) const;

    float getOutlineThickness(void) const;

    virtual unsigned int getPointCount(void) const;

    virtual sf::Vector2f getPoint(unsigned int index) const;

    virtual sf::FloatRect getLocalBounds(void) const;

    virtual sf::FloatRect getGlobalBounds(void) const;

protected:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
    std::unique_ptr<sf::Shape> m_shape;

private:
};

#endif // SHAPE_H
