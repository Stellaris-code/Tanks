/*  include/systems/shieldsystem.hpp ShieldSystem - Yann BOUCHER (yann) 27/11/2016
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
#ifndef SHIELDSYSTEM_HPP
#define SHIELDSYSTEM_HPP

#include <map>

#include <entityx/System.h>
#include <entityx/Event.h>

#include <SFML/System/Time.hpp>

#include "noncopyable.hpp"

#include "events.hpp"

#include "utils.hpp"

class ShieldSystem :
        private Noncopyable,
        public entityx::System<ShieldSystem>,
        public entityx::Receiver<ShieldSystem>
{
    public:
        ShieldSystem() = default;

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<CreateShield>(*this);
            event_manager.subscribe<entityx::EntityDestroyedEvent>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const CreateShield& event);
        void receive(const entityx::EntityDestroyedEvent& event);

    private:
        void createShield(entityx::EntityManager &es, entityx::Entity pawn);

    private:
        std::vector<CreateShield> m_events;

        sf::Time m_shieldDuration { sf::seconds(10) };

        std::map<entityx::Entity, sf::Time> m_shieldsProgress;
};

#endif // SHIELDSYSTEM_HPP
