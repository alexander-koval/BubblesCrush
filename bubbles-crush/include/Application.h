#ifndef APPLICATION_H
#define APPLICATION_H

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "ResourceManager.h"
#include "EventDispatcher.h"
#include "ScreenManager.h"
#include "Resources.h"

class Application {
public:
    Application();

    void run(void);

private:
    void processInput(void);
    void update(sf::Time dt);
    void render(void);
    void updateStats(sf::Time dt);
    void updateStatistics(sf::Time dt);
    void registerScreens(void);

private:
    static unsigned int s_FPS;
    static const sf::Time s_timePerFrame;
    EventDispatcher m_eventDispatcher;
    sf::RenderWindow m_window;
    FontManager m_fontManager;
    TextureManager m_textureManager;
    ScreenManager m_screenManager;
    sf::Time m_statsTime;
    sf::Text m_stats;
    size_t m_statsFPS;
};

#endif // APPLICATION_H
