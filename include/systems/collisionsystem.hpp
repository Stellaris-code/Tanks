/*  include/systems/collisionsystem.hpp CollisionSystem - Yann BOUCHER (yann) 06/11/2016
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
#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP


#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "components/transform.hpp"

#include "events.hpp"

class CollisionSystem :
        private Noncopyable,
        public entityx::System<CollisionSystem>
{
    public:
        CollisionSystem() = default;

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;
};

#endif // COLLISIONSYSTEM_HPP
