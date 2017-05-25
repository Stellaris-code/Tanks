/*  include/systems/lifebarsystem.hpp LifebarSystem - Yann BOUCHER (yann) 20/11/2016
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
#ifndef LIFEBARSYSTEM_HPP
#define LIFEBARSYSTEM_HPP

#include <map>

#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "player.hpp"

#include "drawables/lifebar.hpp"

class LifebarSystem :
        private Noncopyable,
        public entityx::System<LifebarSystem>,
        public entityx::Receiver<LifebarSystem>
{
    public:
        LifebarSystem() = default;
    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<entityx::EntityDestroyedEvent>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const entityx::EntityDestroyedEvent& event);

    private:
        std::map<entityx::Entity::Id, Lifebar> m_lifebars;
};

#endif // LIFEBARSYSTEM_HPP
