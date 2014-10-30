#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "DisplayObject.h"
#include "SFML/Config.hpp"
#include "SFML/Graphics/Text.hpp"

class TextField : public DisplayObject {
public:
    explicit TextField(void);

    explicit TextField(const sf::String& string, const sf::Font& font, unsigned int characterSize = 30);

    void setString(const sf::String& string);

    void setFont(const sf::Font& font);

    void setCharacterSize(unsigned int size);

    void setStyle(sf::Uint32 style);

    void setColor(const sf::Color& color);

    const sf::String& getString(void) const;

    const sf::Font* getFont(void) const;

    unsigned int getCharacterSize(void) const;

    sf::Uint32 getStyle(void) const;

    const sf::Color& getColor(void) const;

    sf::Vector2f findCharacterPos(std::size_t index) const;

    sf::FloatRect getLocalBounds(void) const;

    sf::FloatRect getGlobalBounds(void) const;

private:
    virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

private:
    sf::Text m_text;
};

#endif // TEXTFIELD_H
