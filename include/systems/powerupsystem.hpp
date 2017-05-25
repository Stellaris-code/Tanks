/*  include/systems/powerupsystem.hpp PowerupSystem - Yann BOUCHER (yann) 26/11/2016
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
#ifndef POWERUPSYSTEM_HPP
#define POWERUPSYSTEM_HPP

#include <vector>

#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"


#include "events.hpp"

class PowerupSystem :
        private Noncopyable,
        public entityx::System<PowerupSystem>,
        public entityx::Receiver<PowerupSystem>
{
    public:
        PowerupSystem()
        {}

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<SpawnPowerup>(*this);
            event_manager.subscribe<Collision>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const SpawnPowerup& powerup);
        void receive(const Collision& collision);

    private:
        void spawnPowerup(entityx::EntityManager &es, Powerup::Type type, const sf::Vector2f& pos);

    private:
        std::vector<SpawnPowerup> m_spawnRequests;

        std::vector<Collision> m_pendingCollisions;
};

#endif // POWERUPSYSTEM_HPP
