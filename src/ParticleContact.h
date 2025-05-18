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

    protected:
        void resolve(real_t duration);
        real_t calculateSeparatingVelocity() const;

    private:
        void resolveVelocity(real_t duration);
    };
} // namespace phys2
