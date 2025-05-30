#include "ContactsResolver.h"

phys2::ContactsResolver::ContactsResolver(uint32_t maxIterations)
    : m_MaxIterations(maxIterations)
    , m_Iterations(0)
{
}

void phys2::ContactsResolver::setIterations(uint32_t maxIterations)
{
    m_MaxIterations = maxIterations;
}

void phys2::ContactsResolver::resolveContacts(const std::vector<ParticleContact*>& contacts, real_t duration)
{
    m_Iterations = 0;

    while (m_Iterations < m_MaxIterations)
    {
        real_t max = 0;
        size_t max_index = contacts.size();

        for (size_t index = 0; index < contacts.size(); index++)
        {
            real_t velo = contacts[index]->calculateSeparatingVelocity();
            if (velo < max)
            {
                max = velo;
                max_index = index;
            }
        }

        contacts[max_index]->resolve(duration);
        m_Iterations++;
    }
}
