
#include "Particle.h"

void phys2::Particle::resetForce()
{
    m_ResultedForce = {0, 0};
}

void phys2::Particle::addForce(vec2 force)
{
    m_ResultedForce += force;
}


void phys2::Particle::integrate(const float deltaTime)
{
    m_Position += m_Velocity * deltaTime;
    m_Position += m_Acceleration * deltaTime * deltaTime * 0.5f;

    m_Velocity += m_Acceleration * deltaTime;

    m_Velocity *= std::powf(m_Damping, deltaTime);
}
