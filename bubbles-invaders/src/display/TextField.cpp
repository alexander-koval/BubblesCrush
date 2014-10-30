#include "TextField.h"
#include "SFML/Graphics/RenderTarget.hpp"

TextField::TextField(void)
    : DisplayObject()
    , m_text() {

}

TextField::TextField(const sf::String &string, const sf::Font &font, unsigned int characterSize)
    : DisplayObject()
    , m_text(string, font, characterSize) {

}

void TextField::setString(const sf::String &string) {
    m_text.setString(string);
}

void TextField::setFont(const sf::Font &font) {
    m_text.setFont(font);
}

void TextField::setCharacterSize(unsigned int size) {
    m_text.setCharacterSize(size);
}

void TextField::setStyle(sf::Uint32 style) {
    m_text.setStyle(style);
}

void TextField::setColor(const sf::Color &color) {
    m_text.setColor(color);
}

const sf::String& TextField::getString(void) const {
    return m_text.getString();
}

const sf::Font* TextField::getFont(void) const {
    return m_text.getFont();
}

unsigned int TextField::getCharacterSize(void) const {
    return m_text.getCharacterSize();
}

sf::Uint32 TextField::getStyle(void) const {
    return m_text.getStyle();
}

const sf::Color& TextField::getColor(void) const {
    return m_text.getColor();
}

sf::Vector2f TextField::findCharacterPos(std::size_t index) const {
    return m_text.findCharacterPos(index);
}

sf::FloatRect TextField::getLocalBounds(void) const {
    return m_text.getLocalBounds();
}

sf::FloatRect TextField::getGlobalBounds(void) const {
    return getTransform().transformRect(m_text.getGlobalBounds());
}

void TextField::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_text, states);
}


