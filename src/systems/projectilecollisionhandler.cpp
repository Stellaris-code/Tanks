/*  src/systems/projectilecollisionhandler.cpp ProjectileCollisionHandler - Yann BOUCHER (yann) 23/11/2016
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
#include "systems/projectilecollisionhandler.hpp"

#include "components/projectile.hpp"
#include "components/transform.hpp"
#include "components/health.hpp"
#include "components/hitbox.hpp"

void ProjectileCollisionHandler::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    for (const auto& collision : m_pendingCollisions)
    {
        if (es.valid(collision.lhs) && es.valid(collision.rhs) &&
                (es.has_component<Projectile>(collision.lhs) || es.has_component<Projectile>(collision.rhs)))
        {
            auto projectileId = [&]()
            {
                if (es.has_component<Projectile>(collision.lhs))
                {
                    return collision.lhs;
                }
                else
                {
                    return collision.rhs;
                }
            }();

            auto otherId = [&]()
            {
                if (es.has_component<Projectile>(collision.lhs))
                {
                    return collision.rhs;
                }
                else
                {
                    return collision.lhs;
                }
            }();

            if (es.component<Projectile>(projectileId)->instigator != otherId &&
                    (!es.has_component<Projectile>(otherId) || es.component<Projectile>(projectileId)->instigator !=
                     es.component<Projectile>(otherId)->instigator))
            {
                if (es.component<Hitbox>(otherId)->solid)
                {
                    if (es.component<Hitbox>(otherId)->explosionOnHit)
                    {
                        events.emit<SpawnExplosion>({es.component<Transform>(projectileId)->getPosition()});
                    }

                    if (es.has_component<Health>(otherId))
                    {
                        es.component<Health>(otherId)->takeDamage(es.component<Projectile>(projectileId)->damage,
                                                                  es.component<Projectile>(projectileId)->instigator);
                    }
                    else if (es.has_component<Projectile>(otherId)) // destroy the other too if it is a projectile
                    {
                        es.destroy(otherId);
                    }

                    es.destroy(projectileId);
                }
            }
        }
    }

    m_pendingCollisions.clear();
}

void ProjectileCollisionHandler::receive(const Collision &collision)
{
    m_pendingCollisions.push_back(collision);
}
