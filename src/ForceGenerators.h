#pragma once
#include <vector>
#include "Particle.h"

namespace phys2
{
    class ParticleRegistry
    {
        struct ParticleRegistration
        {
            Particle* particle;
        };
        std::vector<ParticleRegistration> m_Registry;

    public:
        void addParticle(Particle* particle);
        void removeParticle(Particle* particle);
    };

    class ForceGenerator
    {
    public:
        virtual void updateForce(Particle* particle, real_t delta) = 0;
    };
} // namespace phys2
