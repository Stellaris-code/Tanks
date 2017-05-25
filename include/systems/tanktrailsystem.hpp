/*  include/systems/tanktrailsystem.hpp TankTrailSystem - Yann BOUCHER (yann) 23/11/2016
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
#ifndef TANKTRAILSYSTEM_HPP
#define TANKTRAILSYSTEM_HPP

#include <map>

#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "events.hpp"

#include "utils.hpp"

class TankTrailSystem :
        private Noncopyable,
        public entityx::System<TankTrailSystem>
{
    public:
        TankTrailSystem() = default;

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

    private:
        std::map<entityx::Entity::Id, float> m_traveledDistance;
        std::map<entityx::Entity::Id, sf::Vector2f> m_lastPos;

        const float m_trailDist { 15 };
};

#endif // TANKTRAILSYSTEM_HPP
