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

namespace Shape { enum { CIRCLE, SQUARE }; }

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

    ~ParticleSystem(void);

    void populate(int particles, sf::Time lifetime);

    void update(sf::Time dt);

    void setCanvasSize(sf::Vector2u size) { m_size = size; }

    void setParticleSize(sf::Vector2u size) { m_particleSize = size; }

//    void setDissolutionRate(sf::Uint8 rate) { m_dissolutionRate = rate; }

//    void setDissolve(void) { m_dissolve = !m_dissolve; }

    void setDistribution(void) { m_shape = (m_shape + 1) % 2; }

//    void setGravity(float x, float y) { m_gravity.x = x; m_gravity.y = y; }

//    void setGravity(sf::Vector2f gravity) { m_gravity = gravity; }

    void setParticleSpeed(float speed) { m_speed = speed; }

    void setPosition(float x, float y) { m_startPos.x = x; m_startPos.y = y; }

    void setPosition(sf::Vector2f position) { m_startPos = position; }

    void setColor(sf::Color color) { m_color = color; }

    void setShape(sf::Uint8 shape) { m_shape = shape; }

    void setTexture(sf::Texture* texture) { m_texture = texture; }

//    const int getDissolutionRate(void) const { return m_dissolutionRate; }

    const int getNumberOfParticles(void) const { return m_particles.size(); }

    const float getParticleSpeed(void) const { return m_speed; }

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

//    void reset(std::size_t index);

private:
//    bool m_dissolve;
    float m_speed;
    sf::Color m_color;
    sf::Texture* m_texture;
//    sf::Uint8 m_dissolutionRate;
    sf::Uint8 m_shape;
//    sf::Vector2f m_gravity;
    sf::Vector2f m_startPos;
    sf::Vector2u m_size;
    sf::Vector2u m_particleSize;
    sf::VertexArray m_vertices;
    std::deque<Ptr> m_particles;
};

#endif // PARTICLESYSTEM_H
