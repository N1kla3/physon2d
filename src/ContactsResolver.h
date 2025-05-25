#pragma once
#include <cstdint>
#include <vector>
#include "ParticleContact.h"

namespace phys2
{
    class ContactsResolver
    {
    protected:
        uint32_t m_MaxIterations;
        uint32_t m_Iterations;

    public:
        explicit ContactsResolver(uint32_t maxIterations);

        void setIterations(uint32_t maxIterations);

        void resolveContacts(const std::vector<ParticleContact*>& contacts, real_t duration);
    };
} // namespace phys2
