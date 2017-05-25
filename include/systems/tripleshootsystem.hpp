/*  include/systems/tripleshootsystem.hpp TripleShootSystem - Yann BOUCHER (yann) 27/11/2016
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
#ifndef TRIPLESHOOTSYSTEM_HPP
#define TRIPLESHOOTSYSTEM_HPP
#include <map>

#include <entityx/System.h>
#include <entityx/Event.h>

#include <SFML/System/Time.hpp>

#include "noncopyable.hpp"

#include "events.hpp"

#include "utils.hpp"

class TripleShootSystem :
        private Noncopyable,
        public entityx::System<TripleShootSystem>,
        public entityx::Receiver<TripleShootSystem>
{
    public:
        TripleShootSystem() = default;

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<EnableTripleShoot>(*this);
            event_manager.subscribe<entityx::EntityDestroyedEvent>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const EnableTripleShoot& event);
        void receive(const entityx::EntityDestroyedEvent& event);

    private:
        std::vector<EnableTripleShoot> m_events;

        sf::Time m_tripleShootDuration { sf::seconds(10) };

        std::map<entityx::Entity, sf::Time> m_progress;
};
#endif // TRIPLESHOOTSYSTEM_HPP
