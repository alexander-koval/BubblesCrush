#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <memory>
#include <random>
#include <deque>
#include <iostream>
#include "SFML/System/Time.hpp"
#include "SFML/System/NonCopyable.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/VertexArray.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"

struct Particle : public sf::Drawable {
    void update(sf::Time dt) {
        sf::Vector2f half = sf::Vector2f(size.x / 2.f,
                                         size.y / 2.f);
        sf::Vector2f& pos = position;

        vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
        vertices[1].texCoords = sf::Vector2f(size.x, 0.f);
        vertices[2].texCoords = sf::Vector2f(0.f, size.y);
        vertices[3].texCoords = sf::Vector2f(size.x, size.y);

        vertices[0].color = color;
        vertices[1].color = color;
        vertices[2].color = color;
        vertices[3].color = color;

        vertices[0].position.x = pos.x - half.x;
        vertices[0].position.y = pos.y - half.y;
        vertices[1].position.x = pos.x + half.x;
        vertices[1].position.y = pos.y - half.y;
        vertices[2].position.x = pos.x - half.x;
        vertices[2].position.y = pos.y + half.y;
        vertices[3].position.x = pos.x + half.x;
        vertices[3].position.y = pos.y + half.y;
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.texture = texture;
        target.draw(vertices, 4, sf::TrianglesStrip, states);
    }

    sf::Color color;
    sf::Time lifetime;
    sf::Texture* texture;
    sf::Vector2u size;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vertex vertices[4];
};

typedef std::unique_ptr<Particle> Ptr;

class ParticleSystem : public sf::Drawable, public sf::NonCopyable {
public:
    ParticleSystem(sf::Vector2u size);

    virtual ~ParticleSystem(void);

    virtual void populate(int particles);

    virtual void update(sf::Time dt);

    virtual void reset(void);

    void setCanvasSize(sf::Vector2u size) { m_size = size; }

    void setParticleSize(sf::Vector2u size) { m_particleSize = size; }

    void setParticleSpeed(float speed) { m_speed = speed; }

    void setPosition(float x, float y) { m_startPos.x = x; m_startPos.y = y; }

    void setPosition(sf::Vector2f position) { m_startPos = position; }

    void setColor(sf::Color color) { m_color = color; }

    void setTexture(sf::Texture* texture) { m_texture = texture; }

    void setLifetime(sf::Time time) { m_lifetime = time; }

    const int getNumberOfParticles(void) const { return m_particles.size(); }

    const float getParticleSpeed(void) const { return m_speed; }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

protected:
    float m_speed;
    sf::Color m_color;
    sf::Texture* m_texture;
    sf::Time m_lifetime;
    sf::Vector2f m_startPos;
    sf::Vector2u m_size;
    sf::Vector2u m_particleSize;
    std::deque<Ptr> m_particles;
};

#endif // PARTICLESYSTEM_H
