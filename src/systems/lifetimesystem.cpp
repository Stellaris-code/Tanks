/*  src/systems/lifetimesystem.cpp LifetimeSystem - Yann BOUCHER (yann) 09/11/2016
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
#include "systems/lifetimesystem.hpp"

#include "components/lifetime.hpp"

void LifetimeSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Lifetime>([dt](entityx::Entity ent, Lifetime& lifetime)
    {
        lifetime.progress += sf::seconds(dt);

        if (lifetime.progress > lifetime.lifetime)
        {
            ent.destroy();
        }
    });
}
