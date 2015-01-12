#include "GameScreen.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "ScreenManager.h"
#include "Sprite.h"
#include "Utils.h"
#include "EventDispatcher.h"

GameScreen::GameScreen(Context context)
    : Screen(context)
    , m_worldView(context.m_window.getDefaultView())
    , m_back()
    , m_window(context.m_window)
    , m_world(std::make_shared<World>(context))
    , m_sceneTexture()
    , m_fontManager(context.m_fontManager)
    , m_textureManager(context.m_textureManager)
    , m_eventDispatcher(context.m_eventDispatcher)
    , m_screenManager(context.m_screenManager)
    , m_bloomEffect() {
    m_onMousePressed = std::bind(&GameScreen::onMousePressed, this, std::placeholders::_1);
    initialize();
}

void GameScreen::draw(void) {
    if (PostEffect::isSupported()) {
        m_sceneTexture.clear(sf::Color::Black);
        m_sceneTexture.setView(m_worldView);
        m_sceneTexture.draw(*m_world.get());
        m_sceneTexture.display();
        m_bloomEffect.apply(m_sceneTexture, m_window);
    } else {
        m_window.setView(m_worldView);
        m_window.draw(*m_world.get());
    }
    m_window.draw(m_back);
}

void GameScreen::enter(void) {
    m_world->initialize();
}

bool GameScreen::update(sf::Time dt) {
    m_world->update(dt);
    return true;
}

void GameScreen::exit(void) {
    m_world->clear();
}

void GameScreen::initialize(void) {
    using namespace std::placeholders;
    std::function<void(sf::Event&)> func = std::bind(&GameScreen::onMousePressed, this, _1);
    m_sceneTexture.create(m_window.getSize().x, m_window.getSize().y);
    m_back.setStyle(sf::Text::Style::Italic);
    m_back.setFont(m_fontManager.get(Fonts::ID::Main));
    m_back.setString("Back");
    m_back.setPosition(10, 5);
    m_eventDispatcher.addEventListener(sf::Event::EventType::MouseButtonPressed,
                                       m_onMousePressed);
}

void GameScreen::onMousePressed(sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        sf::FloatRect rect = m_back.getGlobalBounds();
        if (rect.contains(sf::Vector2f(event.mouseButton.x,
                                       event.mouseButton.y))) {
            m_screenManager.setScreen(Screens::ID::Menu);
        }
    }
}





