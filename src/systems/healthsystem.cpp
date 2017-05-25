/*  src/systems/healthsystem.cpp HealthSystem - Yann BOUCHER (yann) 20/11/2016
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
#include "systems/healthsystem.hpp"

#include "components/health.hpp"
#include "components/pawn.hpp"

#include "events.hpp"

void HealthSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Health>([&events](entityx::Entity ent, Health& health)
    {
        if (health.dead())
        {
            if (ent.has_component<Transform>())
            {
                events.emit<SpawnExplosion>({ent.component<Transform>()->getPosition()});
            }

            if (ent.has_component<Pawn>())
            {
                events.emit<PawnDestroyed>({ent.component<Pawn>()->controller, health.lastDamageInstigator});
            }

            ent.destroy();
        }
    });
}
