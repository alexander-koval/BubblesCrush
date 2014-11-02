#include "ParticleSystem.h"
#include "Utils.h"

ParticleSystem::ParticleSystem(sf::Vector2u size)
    : m_speed(100.0f)
    , m_color(sf::Color(sf::Color::White))
    , m_texture(nullptr)
    , m_lifetime(sf::seconds(1.f))
    , m_size(size)
    , m_particleSize(1.f, 1.f)  {
      m_startPos = sf::Vector2f(static_cast<float>(size.x) / 2,
                                static_cast<float>(size.y) / 2);
}

ParticleSystem::~ParticleSystem(void) {
    m_particles.clear();
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const Ptr& item : m_particles) {
        target.draw(*item.get(), states);
    }
}

void ParticleSystem::populate(int particles) {
    for(int i = 0; i < particles; i++) {
        Ptr particle = Ptr(new Particle());
        particle->size = m_particleSize;
        particle->texture = m_texture;
        particle->position = m_startPos;
        particle->lifetime = m_lifetime;

        particle->color = m_color;
        m_particles.push_back(std::move(particle));
    }
}

void ParticleSystem::update(sf::Time dt) {
    std::for_each(m_particles.begin(), m_particles.end(), [this, dt](Ptr& particle) {
        particle->position.x += particle->velocity.x * dt.asSeconds() * m_speed;
        particle->position.y += particle->velocity.y * dt.asSeconds() * m_speed;
        particle->lifetime -= dt;
        float ratio = particle->lifetime.asSeconds() / m_lifetime.asSeconds();
        particle->color.a = static_cast<std::uint8_t>(255 * std::max(ratio, 0.f));
        particle->update(dt);
    });

    while ((!m_particles.empty()) && (m_particles.front()->lifetime <= sf::Time::Zero)) {
        m_particles.pop_front();
    }
}

void ParticleSystem::reset(void) {
    m_particles.clear();
}
