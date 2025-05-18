
#include "Particle.h"
#include "ParticleContact.h"

void phys2::Particle::resetForce()
{
    m_ResultedForce = {0, 0};
}

void phys2::Particle::addForce(vec2 force)
{
    m_ResultedForce += force;
}

void phys2::Particle::addVelocity(vec2 velocity)
{
    m_Velocity += velocity;
}


void phys2::Particle::integrate(const float deltaTime)
{
    assert(deltaTime > 0.0);

    m_Position += m_Velocity * deltaTime;

    m_Acceleration += m_ResultedForce * m_InvertMass;

    m_Position += m_Acceleration * deltaTime * deltaTime * 0.5f;

    m_Velocity += m_Acceleration * deltaTime;

    m_Velocity *= std::powf(m_Damping, deltaTime);

    resetForce();
}

void phys2::Particle::setMass(real_t mass)
{
    assert(mass > 0.0);
    m_InvertMass = 1 / mass;
}

void phys2::Particle::setPosition(vec2 pos)
{
    m_Position = pos;
}

phys2::vec2 phys2::Particle::getVelocity() const
{
    return m_Velocity;
}

phys2::real_t phys2::Particle::getDamping() const
{
    return m_Damping;
}

phys2::real_t phys2::Particle::getMass() const
{
    return 1 / m_InvertMass;
}

phys2::real_t phys2::Particle::getInverseMass() const
{
    return m_InvertMass;
}

phys2::vec2 phys2::Particle::getPosition() const
{
    return m_Position;
}
