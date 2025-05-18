#pragma once
#include "Types.h"

namespace phys2
{
    class Particle
    {
    private:
        vec2 m_Position = {};
        real_t m_InvertMass = 1;

        vec2 m_Velocity = {};
        vec2 m_Acceleration = {};

        real_t m_Damping = 0;

        vec2 m_ResultedForce = {};

    public:
        void resetForce();
        void addForce(vec2 force);
        void addVelocity(vec2 velocity);
        void integrate(float deltaTime);

        void setMass(real_t mass);
        void setPosition(vec2 pos);

        vec2 getVelocity() const;
        real_t getDamping() const;
        real_t getMass() const;
        real_t getInverseMass() const;
        vec2 getPosition() const;
        bool hasFiniteMass() const;
    };
} // namespace phys2
