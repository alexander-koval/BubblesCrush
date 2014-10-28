#include "World.h"
#include "Sprite.h"
#include "Bubble.h"
#include "Utils.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "CollisionUtils.h"
#include <iostream>
#include <algorithm>

sf::FloatRect worldArea;
static const size_t MAX_RADIUS = 40;

World::World(Screen::Context &context)
    : m_worldView(context.m_window.getDefaultView())
    , m_displayList()
    , m_target(context.m_window)
    , m_fontManager(context.m_fontManager)
    , m_textureManager(context.m_textureManager) {
    float radius = static_cast<float>(MAX_RADIUS);
    worldArea = sf::FloatRect(0, -radius * 2, m_worldView.getSize().x,
                              m_worldView.getSize().y + MAX_RADIUS * 2);
    m_clock.restart();
    loadTextures();
    buildScene();
}

void World::update(sf::Time dt) {
    if (m_clock.getElapsedTime().asMilliseconds() > 1000) {
        m_clock.restart();
        this->addBubble();
    }
    std::list<Bubble*>::iterator it1 = m_physicList.begin();
    std::list<Bubble*>::iterator it2 = m_physicList.begin();
    const sf::Vector2f& size = m_worldView.getSize();
    Bubble* bubble1 = nullptr;
    Bubble* bubble2 = nullptr;
    while (it1 != m_physicList.end()) {
        bubble1 = *it1;
        if (isCollideWithWall(*bubble1, worldArea)) {
            if (this->onCollideWithWall(*bubble1, worldArea)) {
                std::list<Bubble*>::iterator temp = it1;
                it1++;
                m_physicList.erase(temp);
                continue;
            }
        }
        it1++;
        it2 = it1;
        while (it2 != m_physicList.end()) {
            bubble2 = *it2;
            bubble1->collideWithBubble(bubble2);
            it2++;
        }
    }

    m_displayList.update(dt);
}

void World::draw(void) {
    m_target.setView(m_worldView);
    m_target.draw(m_displayList);
}

void World::loadTextures(void) {
    m_textureManager.load(Textures::ID::Background, "Media/Textures/bg.png");
}

void World::buildScene(void) {
    sf::Texture& backgroundTexture = m_textureManager.get(Textures::ID::Background);

    std::unique_ptr<DisplayObject> backgroundSprite(new Sprite(backgroundTexture));

    m_displayList.addChild(std::move(backgroundSprite));
}

void World::addBubble(void) {
    int radius = randomRange(10, MAX_RADIUS);
    uint8_t red = randomRange(0, 255);
    uint8_t green = randomRange(0, 255);
    uint8_t blue = randomRange(0, 255);
    uint8_t alpha = randomRange(100, 200);
    std::unique_ptr<Bubble> bubble(new Bubble(radius,
                                              sf::Color(red, green, blue, alpha)));
    int random = randomRange(0, m_worldView.getSize().x - radius * 2);

    bubble->setPosition(random, -radius);
    bubble->setVelocity(0, 3000 / radius);
    m_physicList.push_back(bubble.get());
    m_displayList.addChild(std::move(bubble));
}

bool World::onCollideWithWall(Bubble& entity, const sf::FloatRect& area) {
    sf::Vector2f position = entity.getPosition();
    sf::Vector2f velocity = entity.getVelocity();
    if (position.x + entity.getRadius() > area.width) {
        velocity.x = -velocity.x;
        position.x = area.width - entity.getRadius();
    } else if (position.x - entity.getRadius() < area.left) {
        velocity.x = -velocity.x;
        position.x = entity.getRadius();
    }
    if (position.y + entity.getRadius() > area.height) {
//        velocity.y = -velocity.y;
//        position.y = area.height - entity.getRadius();
        m_displayList.removeChild(entity);
        return true;
    } else if (position.y - entity.getRadius() < area.top) {
        velocity.y = -velocity.y;
        position.y = entity.getRadius();
    }
    entity.setPosition(position);
    entity.setVelocity(velocity);
    return false;
}
