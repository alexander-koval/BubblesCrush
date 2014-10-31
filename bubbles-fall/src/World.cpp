#include "World.h"
#include "Sprite.h"
#include "Utils.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Mouse.hpp"
#include "CollisionUtils.h"
#include "EventDispatcher.h"
#include "ParticleSystems.h"
#include "BubblesConfig.h"

sf::FloatRect worldArea;

World::World(Screen::Context &context)
    : m_score()
    , m_worldView(context.m_window.getDefaultView())
    , m_scoreCount(0)
    , m_displayList()
    , m_window(context.m_window)
    , m_sceneTexture()
    , m_fontManager(context.m_fontManager)
    , m_textureManager(context.m_textureManager)
    , m_eventDispatcher(context.m_eventDispatcher)
    , m_collisionManager(sf::FloatRect(0, -Bubbles::MAX_RADIUS * 6, m_worldView.getSize().x,
                                       m_worldView.getSize().y + Bubbles::MAX_RADIUS * 2))
    , m_particleSystem(std::unique_ptr<ParticleSystem>(
                           new ParticleExplosion(m_window.getSize()))) {
    float radius = Bubbles::MAX_RADIUS;
    m_sceneTexture.create(m_window.getSize().x, m_window.getSize().y);
    worldArea = sf::FloatRect(0, -radius * 6, m_worldView.getSize().x,
                              m_worldView.getSize().y + Bubbles::MAX_RADIUS * 2);
    m_onMousePressed = [this] (sf::Event& event) {
        this->onMousePressed(event);
    };
    m_clock.restart();
    loadTextures();
    initialize();
    sf::Texture& texture = m_textureManager.get(Textures::ID::Particle);
    m_particleSystem->setParticleSize(texture.getSize());
    m_particleSystem->setTexture(&texture);
    m_collisionManager.setCollisionListener(this);
}

void World::update(sf::Time dt) {
    if (m_clock.getElapsedTime().asMilliseconds() > Bubbles::TIME) {
        m_clock.restart();
        this->addBubble();
    }

    m_collisionManager.update(dt);
    m_displayList.update(dt);
    m_particleSystem->update(dt);

    while (m_clearList.size() > 0) {
        m_displayList.removeChild(*m_clearList.front());
        m_clearList.pop_front();
    }
}

void World::draw(void) {
    if (PostEffect::isSupported()) {
        m_sceneTexture.clear(sf::Color::Transparent);
        m_sceneTexture.setView(m_worldView);
        m_sceneTexture.draw(m_displayList);
        m_sceneTexture.draw(*m_particleSystem);
        m_sceneTexture.draw(m_score);
        m_sceneTexture.display();
        m_bloomEffect.apply(m_sceneTexture, m_window);
    } else {
        m_window.setView(m_worldView);
        m_window.draw(m_displayList);
        m_window.draw(*m_particleSystem);
        m_window.draw(m_score);
    }
}

void World::loadTextures(void) {
    m_textureManager.load(Textures::ID::Particle, "Media/Textures/Particle.png");
}

void World::initialize(void) {
    m_score.setStyle(sf::Text::Style::Italic);
    m_score.setFont(m_fontManager.get(Fonts::ID::Main));
    m_score.setString("SCORE: 0");
    centerOrigin(m_score);
    m_score.setPosition(m_window.getSize().x / 2, m_score.getLocalBounds().height + 5);
    sf::Texture& backgroundTexture = m_textureManager.get(Textures::ID::Background);
    std::shared_ptr<Sprite> backgroundSprite(new Sprite(backgroundTexture));
    if (PostEffect::isSupported()) {
        backgroundSprite->setColor(sf::Color(40, 40, 40, 255));
    }
    m_displayList.addChild(backgroundSprite);
    m_eventDispatcher.addEventListener(sf::Event::EventType::MouseButtonPressed,
                                       m_onMousePressed);
}

void World::addBubble(void) {
    float radius = randomRange(Bubbles::MIN_RADIUS, Bubbles::MAX_RADIUS);
    uint8_t red = randomRange(0, 255);
    uint8_t green = randomRange(0, 255);
    uint8_t blue = randomRange(0, 200);
    uint8_t alpha = randomRange(100, 200);
    std::shared_ptr<Bubble> bubble(new Bubble(radius,
                                              sf::Color(red, green, blue, alpha)));

    int random = randomRange(0, static_cast<int>(m_worldView.getSize().x -
                                                 radius * 2));

    bubble->setPosition(random, -5 * radius);
    bubble->setVelocity(0, Bubbles::getSpeed(radius));
    m_collisionManager.add(bubble.get());
    m_displayList.addChild(bubble);
}

void World::onMousePressed(sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        DisplayObject& parent = m_displayList;
        for (size_t index = 0; index < parent.numChildren(); index++) {
            DisplayObject* child = parent.getChildAt(index);
            Bubble* bubble = dynamic_cast<Bubble*>(child);
            if (bubble) {
                sf::FloatRect rect = bubble->getGlobalBounds();
                if (rect.contains(sf::Vector2f(event.mouseButton.x,
                                               event.mouseButton.y))) {
                    m_collisionManager.remove(bubble);
                    m_clearList.push_back(bubble);
                    m_scoreCount += Bubbles::getScore(bubble->getRadius());
                    m_score.setString("SCORE: " + std::to_string(m_scoreCount));
                    m_particleSystem->setPosition(event.mouseButton.x,
                                                 event.mouseButton.y);
                    m_particleSystem->setColor(bubble->getColor());
                    m_particleSystem->populate(bubble->getRadius());
                }
            }
        }
    }
}

void World::onCollideWithWall(Bubble *entity, Direction::ID dir) {
    if (Direction::ID::Bottom == dir) {
        m_collisionManager.remove(entity);
        m_clearList.push_back(entity);
    }
}

void World::onCollideWithEntity(Bubble *entity1, Entity *entity2) {

}
