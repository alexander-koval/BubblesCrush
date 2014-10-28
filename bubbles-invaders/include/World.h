#ifndef WORLD_H
#define WORLD_H

#include "SFML/System/NonCopyable.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics/View.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "DisplayObject.h"
#include "ResourceManager.h"
#include "Resources.h"
#include "Screen.h"
#include "Bubble.h"
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
    void buildScene(void);
    void addBubble(void);
    void onMousePressed(sf::Event& event);
    void onCollideWithWall(Bubble* entity, const sf::FloatRect &area);
    void onCollideWithBubble(Bubble* entity1, Bubble* entity2);
private:


private:
    sf::Clock m_clock;
    sf::View m_worldView;
    DisplayObject m_displayList;
    sf::RenderWindow& m_target;
    FontManager& m_fontManager;
    TextureManager& m_textureManager;
    EventDispatcher& m_eventDispatcher;
    std::list<std::shared_ptr<Bubble>> m_physicList;
    std::function<void(sf::Event& event)> m_onMousePressed;
};

#endif // WORLD_H
