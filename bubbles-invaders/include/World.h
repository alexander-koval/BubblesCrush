#ifndef WORLD_H
#define WORLD_H

#include "SFML/System/NonCopyable.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Text.hpp"
#include "BloomEffect.h"
#include "DisplayObject.h"
#include "ResourceManager.h"
#include "ParticleSystem.h"
#include "Resources.h"
#include "Screen.h"
#include "Bubble.h"
#include <array>
#include <list>

namespace sf {
class Event;
}
class World : public sf::NonCopyable {
public:
    explicit World(Screen::Context& context);

    void update(sf::Time dt);

    void draw(void);

private:
    void loadTextures(void);
    void initialize(void);
    void addBubble(void);
    void onMousePressed(sf::Event& event);
    void onCollideWithWall(Bubble* entity, const sf::FloatRect &area);
    void onCollideWithBubble(Bubble* entity1, Bubble* entity2);
private:


private:
    sf::Text m_score;
    sf::Clock m_clock;
    sf::View m_worldView;
    sf::Uint64 m_scoreCount;
    BloomEffect m_bloomEffect;
    DisplayObject m_displayList;
    sf::RenderWindow& m_window;
    sf::RenderTexture m_sceneTexture;
    FontManager& m_fontManager;
    TextureManager& m_textureManager;
    EventDispatcher& m_eventDispatcher;
    std::unique_ptr<ParticleSystem> m_particleSystem;
    std::list<std::shared_ptr<Bubble>> m_physicList;
    std::function<void(sf::Event& event)> m_onMousePressed;
};

#endif // WORLD_H
