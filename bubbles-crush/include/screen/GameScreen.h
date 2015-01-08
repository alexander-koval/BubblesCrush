#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/View.hpp"
#include "ResourceManager.h"
#include "DisplayObject.h"
#include "BloomEffect.h"
#include "Resources.h"
#include "Screen.h"
#include "World.h"

class GameScreen : public Screen, public sf::NonCopyable {
public:
    GameScreen(Context context);

    virtual void draw(void);

    virtual void enter(void);

    virtual bool update(sf::Time dt);

    virtual void exit(void);

private:
    void initialize(void);
    void onMousePressed(sf::Event& event);

private:
    sf::View m_worldView;
    sf::Text m_back;
    sf::RenderWindow& m_window;
    std::shared_ptr<World> m_world;
    sf::RenderTexture m_sceneTexture;
    FontManager& m_fontManager;
    TextureManager& m_textureManager;
    EventDispatcher& m_eventDispatcher;
    ScreenManager& m_screenManager;
    BloomEffect m_bloomEffect;
    std::function<void(sf::Event& event)> m_onMousePressed;
};

#endif // GAMESCREEN_H
