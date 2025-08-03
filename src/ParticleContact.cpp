#include "ParticleContact.h"
#include <algorithm>

void phys2::ParticleContact::resolve(real_t duration)
{
    resolveVelocity(duration);
    resolveInpenetration(duration);
}

phys2::real_t phys2::ParticleContact::calculateSeparatingVelocity() const
{
    vec2 closing_vel = m_Particles[0]->getVelocity();

    if (m_Particles[1])
    {
        closing_vel -= m_Particles[1]->getVelocity();
    }

    return closing_vel.dot(m_ContactNormal);
}

void phys2::ParticleContact::resolveVelocity(real_t duration)
{
    real_t sep_vel = calculateSeparatingVelocity();

    if (sep_vel > 0)
    {
        return;
    }

    real_t new_sep_vel = -sep_vel * m_Restitution;

    vec2 acc_caused_vel = m_Particles[0]->getAcceleration();
    if (m_Particles[1])
    {
        acc_caused_vel -= m_Particles[1]->getAcceleration();
    }
    real_t acc_caused_sep_vel = acc_caused_vel.dot(m_ContactNormal) * duration;
    if (acc_caused_sep_vel < 0)
    {
        new_sep_vel += m_Restitution * acc_caused_sep_vel;
        new_sep_vel = std::max<float>(0, new_sep_vel);
    }

    real_t diff_velocity = new_sep_vel - sep_vel;

    real_t total_mass = getTotalInverseMass();

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

void phys2::ParticleContact::resolveInpenetration(real_t duration)
{
    if (m_Penetration <= 0)
    {
        return;
    }

    real_t total_mass = getTotalInverseMass();

    if (total_mass <= 0)
    {
        // infinite mass
        return;
    }

    vec2 move_per_mass = m_ContactNormal * (m_Penetration / total_mass);

    calculateInpenetrationParticle(m_Particles[0], move_per_mass);
    if (m_Particles[1])
    {
        calculateInpenetrationParticle(m_Particles[1], move_per_mass);
    }
}

phys2::real_t phys2::ParticleContact::getTotalInverseMass() const
{
    real_t total_inverse_mass = m_Particles[0]->getInverseMass();
    if (m_Particles[1])
    {
        total_inverse_mass += m_Particles[1]->getInverseMass();
    }
    return total_inverse_mass;
}

void phys2::ParticleContact::calculateInpenetrationParticle(Particle* particle, vec2 move_per_mass)
{
    particle->setPosition(particle->getPosition() + move_per_mass * particle->getInverseMass());
}
