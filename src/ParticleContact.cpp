#include "ParticleContact.h"
#include "glm/geometric.hpp"

void phys2::ParticleContact::resolve(real_t duration)
{
    resolveVelocity(duration);
}

phys2::real_t phys2::ParticleContact::calculateSeparatingVelocity() const
{
    vec2 closing_vel = m_Particles[0]->getVelocity();

    if (m_Particles[1])
    {
        closing_vel -= m_Particles[1]->getVelocity();
    }

    return glm::dot(closing_vel, m_ContactNormal);
}

void phys2::ParticleContact::resolveVelocity(real_t duration)
{
    real_t sep_vel = calculateSeparatingVelocity();

    if (sep_vel > 0)
    {
        return;
    }

    real_t new_sep_vel = -sep_vel * m_Restitution;

    real_t diff_velocity = new_sep_vel - sep_vel;

    real_t total_mass = m_Particles[0]->getInverseMass();
    if (m_Particles[1])
    {
        total_mass += m_Particles[1]->getInverseMass();
    }

    if (total_mass <= 0)
    {
        // infinite mass
        return;
    }

    real_t impulse = diff_velocity / total_mass;

    vec2 impulse_per_mass = m_ContactNormal * impulse;

    m_Particles[0]->addVelocity(impulse_per_mass * m_Particles[0]->getInverseMass());

    if (m_Particles[1])
    {
        m_Particles[1]->addVelocity(impulse_per_mass * -m_Particles[1]->getInverseMass());
    }
}
