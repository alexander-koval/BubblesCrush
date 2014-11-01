#include "World.h"
#include "Sprite.h"
#include "Utils.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Mouse.hpp"
#include "EventDispatcher.h"
#include "ParticleSystems.h"
#include "BubblesConfig.h"

sf::FloatRect worldBorders;

World::World(Screen::Context &context)
    : DisplayObject()
    , m_score()
    , m_worldView(context.m_window.getDefaultView())
    , m_scoreCount(0)
    , m_window(context.m_window)
    , m_fontManager(context.m_fontManager)
    , m_textureManager(context.m_textureManager)
    , m_eventDispatcher(context.m_eventDispatcher)
    , m_collisionManager()
    , m_spritePool(40, 40)
    , m_particleSystem(std::unique_ptr<ParticleSystem>(
                           new ParticleExplosion(m_window.getSize()))) {
    m_onMousePressed = [this] (sf::Event& event) {
        this->onMousePressed(event);
    };
    m_clock.restart();
    loadTextures();
    worldBorders = sf::FloatRect(0, -(Bubbles::MAX_RADIUS * 4), m_worldView.getSize().x,
                                 m_worldView.getSize().y + (Bubbles::MAX_RADIUS));
    m_collisionManager.setBorders(worldBorders);
    sf::Texture& texture = m_textureManager.get(Textures::ID::Particle);
    m_particleSystem->setParticleSize(texture.getSize());
    m_particleSystem->setTexture(&texture);
    m_collisionManager.setCollisionListener(this);
}

void World::updateCurrent(sf::Time dt) {
    if (m_clock.getElapsedTime().asMilliseconds() > Bubbles::TIME) {
        m_clock.restart();
        this->addBubble();
    }
}

void World::updateChildren(sf::Time dt) {
    m_collisionManager.update(dt);
    DisplayObject::updateChildren(dt);
    m_particleSystem->update(dt);
    while (m_clearList.size() > 0) {
        Bubble* child = m_clearList.front();
        std::unique_ptr<DisplayObject> bubble = this->removeChild(*child);
        m_spritePool.setSprite(std::move(bubble));
        m_clearList.pop_front();
    }
}

void World::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const {
    DisplayObject::drawChildren(target, states);
    target.draw(*m_particleSystem);
    target.draw(m_score);
}

void World::clear(void) {
    m_clearList.clear();
    m_collisionManager.clear();
    while (this->numChildren() > 0) {
        DisplayObject* child = this->getChildAt(0);
        this->removeChild(*child);
    }
    m_particleSystem->reset();
    m_eventDispatcher.removeEventListener(sf::Event::EventType::MouseButtonPressed,
                                       m_onMousePressed);
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
    std::unique_ptr<Sprite> backgroundSprite(new Sprite(backgroundTexture));
    if (PostEffect::isSupported()) {
        backgroundSprite->setColor(sf::Color(40, 40, 40, 255));
    }
    this->addChild(std::move(backgroundSprite));
    m_eventDispatcher.addEventListener(sf::Event::EventType::MouseButtonPressed,
                                       m_onMousePressed);
}

void World::addBubble(void) {
    float radius = randomRange(Bubbles::MIN_RADIUS, Bubbles::MAX_RADIUS);
    uint8_t red = randomRange(0, 255);
    uint8_t green = randomRange(0, 255);
    uint8_t blue = randomRange(0, 200);
    uint8_t alpha = randomRange(100, 200);
    int random = randomRange(0, static_cast<int>(m_worldView.getSize().x -
                                                 radius * 2));

    std::unique_ptr<DisplayObject> ptr = m_spritePool.getSprite();
    Bubble* bubble = static_cast<Bubble*>(ptr.get());
    bubble->setDead(false);
    bubble->setRadius(radius);
    bubble->setColor(sf::Color(red, green, blue, alpha));
    bubble->setPosition(random, worldBorders.top + bubble->getRadius());
    bubble->setVelocity(0, Bubbles::getSpeed(radius));
    m_collisionManager.add(bubble);
    this->addChild(std::move(ptr));
}

void World::onMousePressed(sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        DisplayObject& parent = *this;
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
                    m_score.setString("SCORE: " + to_string(m_scoreCount));
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
