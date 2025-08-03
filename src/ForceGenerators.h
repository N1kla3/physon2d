#pragma once
#include <vector>
#include "Particle.h"

namespace phys2
{
    class ParticleRegistry
    {
        struct ParticleRegistration
        {
            Particle* particle;
            class ForceGenerator* generator;
        };
        std::vector<ParticleRegistration> m_Registry;

    public:
        void addParticle(Particle* particle, ForceGenerator* generator);
        void removeParticle(Particle* particle, ForceGenerator* generator);

        void updateAll(real_t deltaTime);
    };

    class ForceGenerator
    {
    public:
        virtual void updateForce(Particle* particle, real_t delta) = 0;
        virtual ~ForceGenerator() = default;
    };

    class AccumulatedForceGenerator : public ForceGenerator
    {
    private:
        vec2 m_Force;

    public:
        explicit AccumulatedForceGenerator(vec2 inForce);
        virtual void updateForce(Particle* particle, real_t delta);
    };

    class GravityGenerator : public ForceGenerator
    {
    private:
        vec2 m_Gravity = {0, 9.81};

    protected:
        virtual void updateForce(Particle* particle, real_t delta) override;
    };

    class DampingGenerator : public ForceGenerator
    {
    private:
        real_t m_K1;
        real_t m_K2;

    public:
        DampingGenerator(real_t kof1, real_t kof2);

    protected:
        virtual void updateForce(Particle* particle, real_t delta) override;
    };

    class SpringGenerator : public ForceGenerator
    {
    private:
        Particle* m_OtherParticle;
        real_t m_SpringRestLen;
        real_t m_SpringConstant;

    public:
        SpringGenerator(Particle* particle, real_t restLen, real_t constant);

    protected:
        virtual void updateForce(Particle* particle, real_t delta) override;
    };
} // namespace phys2
