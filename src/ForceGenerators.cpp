#include "ForceGenerators.h"
#include "glm/geometric.hpp"

phys2::AccumulatedForceGenerator::AccumulatedForceGenerator(vec2 inForce)
    : m_Force(inForce)
{
}

void phys2::AccumulatedForceGenerator::updateForce(Particle* particle, real_t delta)
{
    assert(particle);

    particle->addForce(m_Force);
}

void phys2::GravityGenerator::updateForce(Particle* particle, real_t delta)
{
    assert(particle);

    particle->addForce(m_Gravity * particle->getMass());
}

phys2::DampingGenerator::DampingGenerator(real_t kof1, real_t kof2)
    : m_K1(kof1)
    , m_K2(kof2)
{
}

void phys2::DampingGenerator::updateForce(Particle* particle, real_t delta)
{
    assert(particle);

    vec2 current_velocity = particle->getVelocity();

    real_t drag_value = glm::length(current_velocity);
    // calculate real drag
    drag_value = m_K1 * drag_value + m_K2 * drag_value * drag_value;

    current_velocity = glm::normalize(current_velocity);

    // drag in opposite direction
    vec2 resulted_force = current_velocity * -drag_value;

    particle->addForce(resulted_force);
}

phys2::SpringGenerator::SpringGenerator(Particle* particle, real_t restLen, real_t constant)
    : m_OtherParticle(particle)
    , m_SpringRestLen(1.0)
    , m_SpringConstant(1.0)
{
}

void phys2::SpringGenerator::updateForce(Particle* particle, real_t delta)
{
    assert(particle);

    vec2 pos_a = particle->getVelocity();
    vec2 pos_b = m_OtherParticle->getVelocity();
    vec2 sub = pos_a - pos_b;

    real_t magnitude = glm::length(sub);
    vec2 normal = glm::normalize(sub);

    vec2 force = -m_SpringConstant * (magnitude - m_SpringRestLen) * normal;

    particle->addForce(force);
}
