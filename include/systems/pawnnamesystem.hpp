/*  include/systems/pawnnamesystem.hpp PawnNameSystem - Yann BOUCHER (yann) 23/11/2016
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
#ifndef PAWNNAMESYSTEM_HPP
#define PAWNNAMESYSTEM_HPP

#include <map>

#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "components/drawable.hpp"

#include "events.hpp"

#include "utils.hpp"

class PawnNameSystem :
        private Noncopyable,
        public entityx::System<PawnNameSystem>,
        public entityx::Receiver<PawnNameSystem>
{
    public:
        PawnNameSystem() = default;

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<entityx::EntityDestroyedEvent>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const entityx::EntityDestroyedEvent& event);

    private:
        std::map<entityx::Entity::Id, entityx::Entity> m_texts;
};

#endif // PAWNNAMESYSTEM_HPP
