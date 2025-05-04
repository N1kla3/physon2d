#pragma once
#include "Types.h"

namespace phys2
{
    class Particle
    {
    private:
        vec2 m_Position = {};
        real_t m_InvertMass = 0;

        vec2 m_Velocity = {};
        vec2 m_Acceleration = {};

        real_t m_Damping = 0;

        vec2 m_ResultedForce = {};

    public:
        void resetForce();
        void addForce(vec2 force);
        void integrate(float deltaTime);
    };
} // namespace phys2
