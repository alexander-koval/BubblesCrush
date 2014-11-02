#ifndef PARTICLESYSTEMS_H
#define PARTICLESYSTEMS_H

#include "ParticleSystem.h"

class ParticleExplosion : public ParticleSystem {
public:
    ParticleExplosion(sf::Vector2u size);

    virtual ~ParticleExplosion(void);

    virtual void populate(int particles);
};

#endif // PARTICLESYSTEMS_H
