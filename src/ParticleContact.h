#pragma once

#include "Particle.h"
#include "array"

namespace phys2
{
    class ParticleContact
    {
        std::array<Particle*, 2> m_Particles;
        real_t m_Restitution;
        vec2 m_ContactNormal;

        real_t m_Penetration;

    protected:
        void resolve(real_t duration);
        real_t calculateSeparatingVelocity() const;

    private:
        void resolveVelocity(real_t duration);
        void resolveInpenetration(real_t duration);

        real_t getTotalInverseMass() const;

        void calculateInpenetrationParticle(Particle* particle, vec2 move_per_mass);
        void calculateVelocityParticle(Particle* particle, vec2 impulse_per_mass);
    };
} // namespace phys2
