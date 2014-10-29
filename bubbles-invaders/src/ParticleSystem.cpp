#include "ParticleSystem.h"
#include "Utils.h"
#include <cmath>

ParticleSystem::ParticleSystem(sf::Vector2u size)
    :
    //  m_dissolve(false),
      m_speed(100.0f),
      m_color(sf::Color(sf::Color::White)),
    //  m_dissolutionRate(4),
      m_shape(Shape::CIRCLE),
    //  m_gravity(sf::Vector2f(0.0f,0.0f)),
      m_size(size) {
      m_startPos = sf::Vector2f(static_cast<float>(size.x) / 2,
                                static_cast<float>(size.y) / 2);
}

ParticleSystem::~ParticleSystem(void) {
    m_particles.clear();
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(const Ptr& item : m_particles) {
        target.draw(*item.get(), states);
//        target.draw(&item->vertex, 1, sf::Points);
    }
}

void ParticleSystem::populate(int particles, sf::Time lifetime) {
    for(int i = 0; i < particles; i++) {
        Ptr particle = Ptr(new Particle());
//        particle->vertex.position.x = m_startPos.x;
//        particle->vertex.position.y = m_startPos.y;
        particle->position = m_startPos;
        particle->lifetime = lifetime;

        switch(m_shape) {
        case Shape::CIRCLE: {
            float angle = randomRange(0.f, 2 * M_PI);
            particle->velocity.x = randomRange(0.0f, cos(angle));
            particle->velocity.y = randomRange(0.0f, sin(angle));
            break;
        }
        case Shape::SQUARE: {
            particle->velocity.x = randomRange(-1.f, 1.f);
            particle->velocity.y = randomRange(-1.f, 1.f);

            break;
        }
        default: {
            particle->velocity.x = 0.5f;
            particle->velocity.y = 0.5f;
        }
        }

//        particle->vertex.color = m_color;
        particle->color = m_color;
        m_particles.push_back(std::move(particle));
    }
}

void ParticleSystem::update(sf::Time dt) {
    std::for_each(m_particles.begin(), m_particles.end(), [this, dt](Ptr& particle) {
//        particle->vertex.position.x += particle->velocity.x * dt.asSeconds() * m_speed;
//        particle->vertex.position.y += particle->velocity.y * dt.asSeconds() * m_speed;
        particle->position.x += particle->velocity.x * dt.asSeconds() * m_speed;
        particle->position.y += particle->velocity.y * dt.asSeconds() * m_speed;
        particle->lifetime -= dt;
        particle->update(dt);
    });

    while ((!m_particles.empty()) && (m_particles.front()->lifetime <= sf::Time::Zero)) {
        m_particles.pop_front();
    }


//  for(auto it = m_particles.begin(); it != m_particles.end(); it++) {
//      /* Apply Gravity */
//  //    (*it)->velocity.x += m_gravity.x * dt.asSeconds();
//  //    (*it)->velocity.y += m_gravity.y * dt.asSeconds();

//      /* Apply thrust */
//      (*it)->vertex.position.x += (*it)->velocity.x * dt.asSeconds() * m_speed;
//      (*it)->vertex.position.y += (*it)->velocity.y * dt.asSeconds() * m_speed;

//      /* If they are set to disolve, disolve */
//  //    if (m_dissolve) (*it)->vertex.color.a -= m_dissolutionRate;

//      if ((*it)->vertex.position.x > m_size.x ||
//              (*it)->vertex.position.x < 0 ||
//              (*it)->vertex.position.y > m_size.y ||
//              (*it)->vertex.position.y < 0 ||
//              (*it)->vertex.color.a < 10) {
//          it = m_particles.erase(it);
//          if (it == m_particles.end()) return;
//      }
//  }

//  return;
}
