/*  include/systems/projectilecollisionhandler.hpp ProjectileCollisionHandler - Yann BOUCHER (yann) 23/11/2016
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
#ifndef PROJECTILECOLLISIONHANDLER_HPP
#define PROJECTILECOLLISIONHANDLER_HPP

#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "events.hpp"

class ProjectileCollisionHandler :
        private Noncopyable,
        public entityx::System<ProjectileCollisionHandler>,
        public entityx::Receiver<ProjectileCollisionHandler>
{
    public:
        ProjectileCollisionHandler() = default;

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<Collision>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const Collision& collision);

    private:
        std::vector<Collision> m_pendingCollisions;
};


#endif // PROJECTILECOLLISIONHANDLER_HPP
