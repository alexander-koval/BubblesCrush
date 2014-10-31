#include "ParticleSystems.h"
#include "Utils.h"

ParticleExplosion::ParticleExplosion(sf::Vector2u size)
    : ParticleSystem(size) {

}


ParticleExplosion::~ParticleExplosion(void) {

}

void ParticleExplosion::populate(int particles) {
    for(int i = 0; i < particles; i++) {
        Ptr particle = Ptr(new Particle());
        particle->size = m_particleSize;
        particle->texture = m_texture;
        particle->position = m_startPos;
        particle->lifetime = m_lifetime;
        float angle = randomRange(0.f, 2 * M_PI);
        particle->velocity.x = randomRange(0.0f, cos(angle));
        particle->velocity.y = randomRange(0.0f, sin(angle));
        particle->color = m_color;
        m_particles.push_back(std::move(particle));
    }
}
