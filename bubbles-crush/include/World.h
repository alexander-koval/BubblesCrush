#ifndef WORLD_H
#define WORLD_H

#include "SFML/System/NonCopyable.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SpritePool.h"
#include "BloomEffect.h"
#include "DisplayObject.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "ParticleSystem.h"
#include "Resources.h"
#include "Screen.h"
#include "Bubble.h"
#include <array>
#include <deque>
#include <functional>

namespace sf {
class Event;
}
class World : public DisplayObject, public CollisionListener {
public:
    explicit World(Screen::Context& context);

    virtual void updateCurrent(sf::Time dt);

    virtual void updateChildren(sf::Time dt);

    virtual void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;

    void initialize(void);

    void clear(void);

private:
    void loadTextures(void);
    void addBubble(void);
    void onMousePressed(sf::Event& event);
    virtual void onCollideWithWall(Physical* entity, Direction::ID dir);
    virtual void onCollideWithEntity(Physical* entity1, Physical* entity2);

private:
    sf::Text m_score;
    sf::Clock m_clock;
    sf::View m_worldView;
    sf::Uint64 m_scoreCount;
    sf::RenderWindow& m_window;
    FontManager& m_fontManager;
    TextureManager& m_textureManager;
    EventDispatcher& m_eventDispatcher;
    CollisionManager m_collisionManager;
    SpritePool<Bubble> m_spritePool;
    std::unique_ptr<ParticleSystem> m_particleSystem;
    std::deque<std::weak_ptr<Bubble>> m_clearList;
    std::function<void(sf::Event& event)> m_onMousePressed;
};

#endif // WORLD_H
