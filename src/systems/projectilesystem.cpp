/*  src/systems/projectilesystem.cpp ProjectileSystem - Yann BOUCHER (yann) 06/11/2016
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
#include "systems/projectilesystem.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

#include "components/projectile.hpp"
#include "components/transform.hpp"

void ProjectileSystem::update(entityx::EntityManager &es, entityx::EventManager & events, entityx::TimeDelta dt)
{
    es.each<Projectile, Transform>([this, &events, dt](entityx::Entity ent, Projectile& proj, Transform& transform)
    {
        if (transform.getPosition().x < 0 || transform.getPosition().y < 0 ||
                transform.getPosition().x > m_winSize.x || transform.getPosition().y > m_winSize.y)
        {
            events.emit<ProjectileOutsideBounds>({ent.id()});
            ent.destroy();
        }
        else
        {
            sf::Vector2f offset = {0.f, float(dt * proj.speed)};
            thor::rotate(offset, transform.getRotation());

            transform.move(offset);
        }
    });
}
