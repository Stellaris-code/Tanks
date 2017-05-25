/*  include/systems/turrethandlersystem.hpp TurretHandlerSystem - Yann BOUCHER (yann) 06/11/2016
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
#ifndef TURRETHANDLERSYSTEM_HPP
#define TURRETHANDLERSYSTEM_HPP

#include <vector>

#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "events.hpp"

class TurretHandlerSystem :
        private Noncopyable,
        public entityx::System<TurretHandlerSystem>,
        public entityx::Receiver<TurretHandlerSystem>
{
    public:
        TurretHandlerSystem() = default;

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<PlayerEventPointTo>(*this);
            event_manager.subscribe<PlayerEventFire>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const PlayerEventPointTo& pointTo);
        void receive(const PlayerEventFire& fire);

    private:
        void spawnBullet(entityx::EntityManager &es, const entityx::Entity::Id& instigator, const sf::Vector2f& pos, float angle);

    private:
        std::vector<PlayerEventPointTo> m_pointToEvents;

        std::vector<PlayerEventFire> m_fireEvents;

        float m_tripleShootSpread { 10 };
};

#endif // TURRETHANDLERSYSTEM_HPP
