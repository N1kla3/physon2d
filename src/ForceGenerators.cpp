#include "ForceGenerators.h"
#include <algorithm>
#include <cassert>

void phys2::ParticleRegistry::addParticle(Particle* particle, ForceGenerator* generator)
{
    m_Registry.emplace_back(particle, generator);
}

void phys2::ParticleRegistry::removeParticle(Particle* particle, ForceGenerator* generator)
{
    [[maybe_unused]] auto res = std::remove_if(m_Registry.begin(),
                                               m_Registry.end(),
                                               [particle, generator](const ParticleRegistration& reg)
                                               { return reg.particle == particle && reg.generator == generator; });
}

void phys2::ParticleRegistry::updateAll(real_t deltaTime)
{
    for (const auto& [particle, generator]: m_Registry)
    {
        generator->updateForce(particle, deltaTime);
    }
}

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

    real_t drag_value = current_velocity.len();
    // calculate real drag
    drag_value = m_K1 * drag_value + m_K2 * drag_value * drag_value;

    current_velocity.normalize();

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

    real_t magnitude = sub.len();
    vec2 normal = sub.getNormalized();

    vec2 force = -m_SpringConstant * (magnitude - m_SpringRestLen) * normal;

    particle->addForce(force);
}
