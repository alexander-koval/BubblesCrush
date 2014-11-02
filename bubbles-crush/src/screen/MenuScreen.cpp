#include "SFML/Graphics/RenderWindow.hpp"
#include "ScreenManager.h"
#include "Sprite.h"
#include "Utils.h"
#include "MenuScreen.h"
#include "EventDispatcher.h"

MenuScreen::MenuScreen(Context context)
        : Screen(context)
        , m_worldView(context.m_window.getDefaultView())
        , m_title()
        , m_window(context.m_window)
        , m_displayList()
        , m_fontManager(context.m_fontManager)
        , m_textureManager(context.m_textureManager)
        , m_eventDispatcher(context.m_eventDispatcher)
        , m_screenManager(context.m_screenManager) {
    m_onMousePressed = [this] (sf::Event& event) {
        this->onMousePressed(event);
    };
    initialize();
}

void MenuScreen::draw(void) {
    m_window.setView(m_worldView);
    m_window.draw(m_displayList);
    m_window.draw(m_title);
}

void MenuScreen::enter(void) {
    m_eventDispatcher.addEventListener(sf::Event::EventType::MouseButtonPressed,
                                       m_onMousePressed);
}

bool MenuScreen::update(sf::Time dt) {
    m_displayList.update(dt);
    return true;
}

void MenuScreen::exit(void) {
    m_eventDispatcher.removeEventListener(sf::Event::EventType::MouseButtonPressed,
                                       m_onMousePressed);
}

void MenuScreen::initialize(void) {
    m_title.setFont(m_fontManager.get(Fonts::ID::Main));
    m_title.setStyle(sf::Text::Style::Bold);
    m_title.setCharacterSize(50);
    m_title.setString("PLAY");
    centerOrigin(m_title);
    m_title.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);
    sf::Texture& backgroundTexture = m_textureManager.get(Textures::ID::Background);
    std::unique_ptr<DisplayObject> backgroundSprite(new Sprite(backgroundTexture));
    m_displayList.addChild(std::move(backgroundSprite));

}

void MenuScreen::onMousePressed(sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::FloatRect rect = m_title.getGlobalBounds();
        if (rect.contains(sf::Vector2f(event.mouseButton.x,
                                       event.mouseButton.y))) {
            m_screenManager.setScreen(Screens::ID::Game);
        }
    }
}
