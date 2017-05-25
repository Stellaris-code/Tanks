/*  src/systems/tanktrailsystem.cpp TankTrailSystem - Yann BOUCHER (yann) 23/11/2016
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
#include "systems/tanktrailsystem.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

#include "components/transform.hpp"
#include "components/tank.hpp"
#include "components/drawable.hpp"
#include "components/lifetime.hpp"

void TankTrailSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Tank, Transform>([this, &es](entityx::Entity ent, Tank& tank, Transform& trans)
    {
        if (m_traveledDistance.count(ent.id()) == 0 || m_lastPos.count(ent.id()) == 0)
        {
            m_traveledDistance[ent.id()] = 0;
            m_lastPos[ent.id()] = trans.getPosition();
        }
        else
        {

            m_traveledDistance[ent.id()] += thor::length(trans.getPosition() - m_lastPos[ent.id()]);
            m_lastPos[ent.id()] = trans.getPosition();

            if (m_traveledDistance[ent.id()] > m_trailDist)
            {
                m_traveledDistance[ent.id()] = 0;

                auto trail = es.create();
                trail.assign<Transform>(trans);
                trail.assign<Drawable>(Drawable{"trail", {0.5, 0}})->zorder = -1;
                trail.assign<Lifetime>(sf::seconds(30));
            }
        }
    });
}
