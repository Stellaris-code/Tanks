/*  src/systems/tankcollisionhandler.cpp TankCollisionHandler - Yann BOUCHER (yann) 06/11/2016
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
#include "systems/tankcollisionhandler.hpp"

#include "components/tank.hpp"
#include "components/projectile.hpp"
#include "components/transform.hpp"
#include "components/drawable.hpp"
#include "components/animation.hpp"
#include "components/lifetime.hpp"
#include "components/health.hpp"

#include "utils.hpp"

void TankCollisionHandler::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    for (const auto& collision : m_pendingCollisions)
    {
        if (es.valid(collision.lhs) && es.valid(collision.rhs))
        {
            if ((es.get(collision.lhs).has_component<Tank>() && es.get(collision.rhs).has_component<Projectile>()) ||
                    (es.get(collision.lhs).has_component<Projectile>() && es.get(collision.rhs).has_component<Tank>()))
            {
                auto tankId = [&]()
                {
                    if (es.get(collision.lhs).has_component<Tank>())
                    {
                        return collision.lhs;
                    }
                    else
                    {
                        return collision.rhs;
                    }
                }();
                auto projectileId = [&]()
                {
                    if (es.get(collision.lhs).has_component<Projectile>())
                    {
                        return collision.lhs;
                    }
                    else
                    {
                        return collision.rhs;
                    }
                }();

                if (es.get(projectileId).component<Projectile>()->instigator != tankId)
                {
                    es.get(tankId).component<Health>()->takeDamage(es.get(projectileId).component<Projectile>()->damage,
                                                                   es.get(projectileId).component<Projectile>()->instigator);

                    events.emit<SpawnExplosion>({es.get(tankId).component<Transform>()->getPosition()});

                    es.get(projectileId).destroy();
                }
            }
        }
    }

    m_pendingCollisions.clear();
}

void TankCollisionHandler::receive(const Collision &collision)
{
    m_pendingCollisions.push_back(collision);
}

