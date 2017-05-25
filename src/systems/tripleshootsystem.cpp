/*  src/systems/tripleshootsystem.cpp TripleShootSystem - Yann BOUCHER (yann) 27/11/2016
**
**
**            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
**                    Version 2, December 2004
**
** Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
**
** Everyone is permitted to copy and distribute verbatim or modified
** copies of this license document, and changing it is allowed as long
** as the name is changed.
**
**            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
**   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
**
**  0. You just DO WHAT THE FUCK YOU WANT TO.
*/
#include "systems/tripleshootsystem.hpp"

#include "components/turret.hpp"

void TripleShootSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Turret>([this, &es, dt](entityx::Entity ent, Turret& turret)
    {
        for (const auto& event : m_events)
        {
            if (turret.player == event.player)
            {
                turret.tripleShoot = true;
                m_progress[ent] = sf::Time::Zero;
            }
        }
    });

    std::vector<entityx::Entity> tripleShootsToDelete;

    for (auto& pair : m_progress)
    {
        pair.second += sf::seconds(dt);

        if (pair.second >= m_tripleShootDuration)
        {
            es.component<Turret>(pair.first.id())->tripleShoot = false;
            tripleShootsToDelete.push_back(pair.first);
        }
    }

    for (auto tripleShoot : tripleShootsToDelete)
    {
        m_progress.erase(tripleShoot);
    }

    m_events.clear();
}

void TripleShootSystem::receive(const EnableTripleShoot &event)
{
    m_events.push_back(event);
}

void TripleShootSystem::receive(const entityx::EntityDestroyedEvent &event)
{
    m_progress.erase(event.entity);
}
