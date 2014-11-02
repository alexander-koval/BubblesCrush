#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <SFML/Window/Event.hpp>
#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/Text.hpp"
#include "ResourceManager.h"
#include "DisplayObject.h"
#include "Resources.h"
#include "Screen.h"

class MenuScreen : public Screen, public sf::NonCopyable {
public:
    MenuScreen(Context context);

    virtual void draw(void);

    virtual void enter(void);

    virtual bool update(sf::Time dt);

    virtual void exit(void);

private:
    void initialize(void);
    void onMousePressed(sf::Event& event);

private:
    sf::View m_worldView;
    sf::Text m_title;
    sf::RenderWindow& m_window;
    DisplayObject m_displayList;
    FontManager& m_fontManager;
    TextureManager& m_textureManager;
    EventDispatcher& m_eventDispatcher;
    ScreenManager& m_screenManager;
    std::function<void(sf::Event& event)> m_onMousePressed;
};

#endif // MENUSCREEN_H
