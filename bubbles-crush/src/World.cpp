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
    worldBorders = sf::FloatRect(0, -(Bubbles::MAX_RADIUS * 2), m_worldView.getSize().x,
                                 m_worldView.getSize().y + (Bubbles::MAX_RADIUS * 2));
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
        std::weak_ptr<Bubble> ptr = m_clearList.front();
        std::shared_ptr<Bubble> bubble_ptr = ptr.lock();
        if (bubble_ptr) {
            this->removeChild(bubble_ptr);
            m_spritePool.setSprite(bubble_ptr);
            m_clearList.pop_front();
        }
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
        DisplayObject::Ptr child_ptr = this->getChildAt(0);
        this->removeChild(child_ptr);
    }
    m_particleSystem->reset();
    m_eventDispatcher.removeEventListener(sf::Event::EventType::MouseButtonPressed,
                                       m_onMousePressed);
}

void World::loadTextures(void) {
    m_textureManager.load(Textures::ID::Particle, "Media/Textures/Particle.png");
}

void World::initialize(void) {
    using namespace std::placeholders;
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
//    m_eventDispatcher.addEventListener(sf::Event::EventType::MouseButtonPressed, &onMousePressed);
}

void World::addBubble(void) {
    float radius = randomRange(Bubbles::MIN_RADIUS, Bubbles::MAX_RADIUS);
    uint8_t red = randomRange(0, 255);
    uint8_t green = randomRange(0, 255);
    uint8_t blue = randomRange(0, 200);
    uint8_t alpha = randomRange(100, 200);
    int random = randomRange(static_cast<int>(radius),
                             static_cast<int>(m_worldView.getSize().x -
                                                 radius));

    std::shared_ptr<Bubble> bubble_ptr = m_spritePool.getSprite();
    bubble_ptr->setDead(false);
    bubble_ptr->setRadius(radius);
    bubble_ptr->setFillColor(sf::Color(red, green, blue, alpha));
    bubble_ptr->setPosition(random, worldBorders.top + bubble_ptr->getRadius());
    bubble_ptr->setVelocity(0, Bubbles::getSpeed(radius));
    m_collisionManager.add(&bubble_ptr->getPhysics());
    this->addChild(bubble_ptr);
}

void World::onMousePressed(sf::Event &event) {
    if (event.mouseButton.button == sf::Mouse::Left) {
        DisplayObject::Ptr parent = shared_from_this();

        for (size_t index = 0; index < parent->numChildren(); index++) {
            DisplayObject::Ptr child_ptr = parent->getChildAt(index);
            std::shared_ptr<Bubble> bubble_ptr = std::dynamic_pointer_cast<Bubble>(child_ptr);
            if (bubble_ptr) {
                sf::FloatRect rect = bubble_ptr->getGlobalBounds();
                if (rect.contains(sf::Vector2f(event.mouseButton.x,
                                               event.mouseButton.y))) {
                    m_collisionManager.remove(&bubble_ptr->getPhysics());
                    m_clearList.push_back(bubble_ptr);
                    m_scoreCount += Bubbles::getScore(bubble_ptr->getRadius());
                    m_score.setString("SCORE: " + to_string(m_scoreCount));
                    m_particleSystem->setPosition(event.mouseButton.x,
                                                 event.mouseButton.y);
                    m_particleSystem->setColor(bubble_ptr->getFillColor());
                    m_particleSystem->populate(bubble_ptr->getRadius());
                }
            }
        }
    }
}

void World::onCollideWithWall(Physical *entity, Direction::ID dir) {
    if (Direction::ID::Bottom == dir) {
        DisplayObject::Ptr ptr = entity->getGraphics();
        std::shared_ptr<Bubble> bubble_ptr = std::dynamic_pointer_cast<Bubble>(ptr);
        m_collisionManager.remove(entity);
        m_clearList.push_back(bubble_ptr);
    }
}

void World::onCollideWithEntity(Physical *entity1, Physical *entity2) {

}
