#include "Application.h"
#include "SFML/System/Sleep.hpp"
#include "GameScreen.h"
#include "MenuScreen.h"
#include "Utils.h"

unsigned int Application::s_FPS = 60;
const sf::Time Application::s_timePerFrame = sf::seconds(1.0f / s_FPS);

Application::Application()
    : m_window(sf::VideoMode(768, 1024),
               "Bubbles Crush",
               sf::Style::Close)
    , m_screenManager(Screen::Context(m_window,
                                      m_screenManager,
                                      m_eventDispatcher,
                                      m_textureManager,
                                      m_fontManager)) {
    m_window.setKeyRepeatEnabled(false);
    m_window.setVerticalSyncEnabled(true);
    m_window.setFramerateLimit(s_FPS);
    m_fontManager.load(Fonts::ID::Main, "Media/Sansation.ttf");
    m_textureManager.load(Textures::ID::Background, "Media/Textures/bg.png");
    m_stats.setFont(m_fontManager.get(Fonts::ID::Main));
    m_stats.setPosition(650, 5.0f);
    m_stats.setColor(sf::Color(255, 0, 0, 255));
    m_stats.setCharacterSize(20u);
    m_stats.setStyle(sf::Text::Style::Bold);
    m_statsTime = sf::Time::Zero;
    m_statsFPS = 0;
    registerScreens();
}

void Application::run(void) {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    m_screenManager.setScreen(Screens::ID::Menu);
    while (m_window.isOpen()) {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > s_timePerFrame) {
            timeSinceLastUpdate -= s_timePerFrame;
            processInput();
            update(s_timePerFrame);
            if (m_screenManager.isEmpty()) {
                m_window.close();
            }
        }
#ifdef DEBUG_MODE
        updateStatistics(dt);
#endif
        render();
    }
}

void Application::processInput(void) {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_window.close();
        }
        if (event.type == sf::Event::TouchBegan) {
            std::cout << "TOCH" << std::endl;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            m_eventDispatcher.dispatchEvent(event);
        }
    }
}

void Application::update(sf::Time dt) {
    m_screenManager.update(dt);
}

void Application::render(void) {
    m_window.clear();
    m_screenManager.draw();
    m_window.setView(m_window.getDefaultView());
    m_window.draw(m_stats);
    m_window.display();
}

void Application::updateStatistics(sf::Time dt) {
    m_statsTime += dt;
    m_statsFPS += 1;
    if (m_statsTime >= sf::seconds(1.0f)) {
        m_stats.setString("FPS: " + to_string(m_statsFPS));

        m_statsTime -= sf::seconds(1.0f);
        m_statsFPS = 0;
    }
}

void Application::registerScreens(void) {
    m_screenManager.addScreen<MenuScreen>(Screens::ID::Menu);
    m_screenManager.addScreen<GameScreen>(Screens::ID::Game);
}
