#include "World.h"
#include "Sprite.h"
#include "Bubble.h"
#include "Utils.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Mouse.hpp"
#include "CollisionUtils.h"
#include "EventDispatcher.h"
#include <iostream>
#include <algorithm>

sf::FloatRect worldArea;
static const size_t MAX_RADIUS = 40;

World::World(Screen::Context &context)
    : m_worldView(context.m_window.getDefaultView())
    , m_displayList()
    , m_window(context.m_window)
    , m_sceneTexture()
    , m_fontManager(context.m_fontManager)
    , m_textureManager(context.m_textureManager)
    , m_eventDispatcher(context.m_eventDispatcher)
    , m_particleSystem(m_window.getSize()) {
    float radius = static_cast<float>(MAX_RADIUS);
    m_sceneTexture.create(m_window.getSize().x, m_window.getSize().y);
    worldArea = sf::FloatRect(0, -radius * 2, m_worldView.getSize().x,
                              m_worldView.getSize().y + MAX_RADIUS * 2);
    m_onMousePressed = [this] (sf::Event& event) {
        this->onMousePressed(event);
    };
    m_clock.restart();
    loadTextures();
    buildScene();
}

void World::update(sf::Time dt) {
    if (m_clock.getElapsedTime().asMilliseconds() > 500) {
        m_clock.restart();
        this->addBubble();
    }

    m_displayList.update(dt);
    m_particleSystem.update(dt);
    std::list<std::shared_ptr<Bubble>>::iterator it1 = m_physicList.begin();
    std::list<std::shared_ptr<Bubble>>::iterator it2 = m_physicList.begin();
    while (it1 != m_physicList.end()) {
        std::shared_ptr<Bubble> ptr = *it1;
        Bubble* bubble1 = ptr.get();
        if (isCollideWithWall(*bubble1, worldArea)) {
            this->onCollideWithWall(bubble1, worldArea);
            if (bubble1->isDead()) {
                m_displayList.removeChild(ptr);
            }
        }
        it2 = ++it1;
        while (it2 != m_physicList.end()) {
            std::shared_ptr<Bubble> ptr = *it2;
            Bubble* bubble2 = ptr.get();
            if (isCollideWithBubble(*bubble1, *bubble2)) {
                this->onCollideWithBubble(bubble1, bubble2);
            }
            it2++;
        }
    }

    m_physicList.remove_if([](std::shared_ptr<Bubble> bubble) -> bool {
        return bubble->isDead();
    });
}

void World::draw(void) {
    if (PostEffect::isSupported()) {
        m_sceneTexture.clear(sf::Color::Transparent);
        m_sceneTexture.setView(m_worldView);
        m_sceneTexture.draw(m_displayList);
        m_sceneTexture.draw(m_particleSystem);
        m_sceneTexture.display();
        m_bloomEffect.apply(m_sceneTexture, m_window);
    } else {
        m_window.setView(m_worldView);
        m_window.draw(m_displayList);
        m_window.draw(m_particleSystem);
    }
}

void World::loadTextures(void) {
    m_textureManager.load(Textures::ID::Background, "Media/Textures/bg.png");
    m_textureManager.load(Textures::ID::Particle, "Media/Textures/Particle.png");
}

void World::buildScene(void) {
    sf::Texture& backgroundTexture = m_textureManager.get(Textures::ID::Background);
    std::unique_ptr<DisplayObject> backgroundSprite(new Sprite(backgroundTexture));
    m_displayList.addChild(std::move(backgroundSprite));

    m_eventDispatcher.addEventListener(sf::Event::EventType::MouseButtonPressed,
                                       m_onMousePressed);
}

void World::addBubble(void) {
    int radius = randomRange(20, MAX_RADIUS);
    uint8_t red = randomRange(0, 255);
    uint8_t green = randomRange(0, 255);
    uint8_t blue = randomRange(0, 200);
    uint8_t alpha = randomRange(100, 200);
    std::shared_ptr<Bubble> bubble(new Bubble(radius,
                                              sf::Color(red, green, blue, alpha)));
//    std::shared_ptr<Bubble> bubble(new Bubble(radius,
//                                              sf::Color(255, 255, 0, 255)));

    int random = randomRange(0, static_cast<int>(m_worldView.getSize().x - radius * 2));

    bubble->setPosition(random, -radius);
    bubble->setVelocity(0, 4000 / radius);
    m_physicList.push_back(bubble);
    m_displayList.addChild(bubble);
}

void World::onMousePressed(sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        auto find = std::find_if(m_physicList.begin(), m_physicList.end(),
                                 [&] (std::shared_ptr<Bubble>& bubble) {
                sf::FloatRect rect = bubble->getGlobalBounds();
                if (rect.contains(sf::Vector2f(event.mouseButton.x,
                                               event.mouseButton.y))) {
                    m_displayList.removeChild(bubble);
                    bubble->setDead(true);
                    m_particleSystem.setPosition(event.mouseButton.x,
                                                 event.mouseButton.y);
                    m_particleSystem.setColor(bubble->getColor());
                    m_particleSystem.populate(bubble->getRadius(), sf::seconds(2.0f));
                    return true;
                }
                return false;
            });
        if (find != m_physicList.end()) {
            m_physicList.erase(find);
        }
    }
}

void World::onCollideWithWall(Bubble* entity, const sf::FloatRect& area) {
    sf::Vector2f position = entity->getPosition();
    sf::Vector2f velocity = entity->getVelocity();
    if (position.x + entity->getRadius() > area.width) {
        velocity.x = -velocity.x;
        position.x = area.width - entity->getRadius();
    } else if (position.x - entity->getRadius() < area.left) {
        velocity.x = -velocity.x;
        position.x = entity->getRadius();
    }
    if (position.y + entity->getRadius() > area.height) {
//        velocity.y = -velocity.y;
//        position.y = area.height - entity.getRadius();
        entity->setDead(true);
    } else if (position.y - entity->getRadius() < area.top) {
        velocity.y = -velocity.y;
        position.y = entity->getRadius();
    }
    entity->setPosition(position);
    entity->setVelocity(velocity);
}

void World::onCollideWithBubble(Bubble* entity1, Bubble* entity2) {
    sf::Vector2f delta = entity1->getPosition() - entity2->getPosition();
    float dist = length(delta);
    if (dist < entity1->getRadius() + entity2->getRadius()) {
        float angle = atan2(delta.y, delta.x);
        float sinf = sin(angle);
        float cosf = cos(angle);
        sf::Vector2f pos1(0.f, 0.f);
        sf::Vector2f pos2(rotate(delta.x, delta.y, sinf, cosf, true));
        sf::Vector2f vel1(rotate(entity1->getVelocity().x,
                                 entity1->getVelocity().y, sinf, cosf, true));
        sf::Vector2f vel2(rotate(entity2->getVelocity().x,
                                 entity2->getVelocity().y, sinf, cosf, true));

        float total = vel1.x - vel2.x;
        vel1.x = vel2.x;
        vel2.x = total + vel1.x;
        float absolute = fabs(vel1.x) + fabs(vel2.x);
        float overlap = (entity1->getRadius() + entity2->getRadius()) - fabs(pos1.x - pos2.x);
        pos1.x += vel1.x / absolute * overlap;

        sf::Vector2f pos1F = rotate(pos1.x, pos1.y, sinf, cosf, false);

        entity1->setPosition(entity1->getPosition().x + pos1F.x,
                            entity1->getPosition().y + pos1F.y);

        sf::Vector2f vel1F = rotate(vel1.x, vel1.y, sinf, cosf, false);
        sf::Vector2f vel2F = rotate(vel2.x, vel2.y, sinf, cosf, false);

        entity1->setVelocity(vel1F.x, vel1F.y);
        entity2->setVelocity(vel2F.x, vel2F.y);
    }
}
