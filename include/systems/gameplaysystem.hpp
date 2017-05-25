/*  include/systems/gameplaysystem.hpp GameplaySystem - Yann BOUCHER (yann) 09/11/2016
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
#ifndef GAMEPLAYSYSTEM_HPP
#define GAMEPLAYSYSTEM_HPP


#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "player.hpp"

#include "callbacktimer.hpp"

#include "events.hpp"

class GameplaySystem :
        private Noncopyable,
        public entityx::System<GameplaySystem>,
        public entityx::Receiver<GameplaySystem>,
        public CallbackTimerService
{
    public:
        GameplaySystem(const sf::Vector2u& screenSize)
            : m_screenSize(screenSize)
        {
        }

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<SpawnTank>(*this);
            event_manager.subscribe<SpawnCrate>(*this);
            event_manager.subscribe<SpawnExplosion>(*this);
            event_manager.subscribe<SpawnRandomCrates>(*this);
            event_manager.subscribe<SpawnRandomPowerup>(*this);

            registerServices(event_manager);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const SpawnTank& tank);
        void receive(const SpawnCrate& crate);
        void receive(const SpawnExplosion& explosion);
        void receive(const SpawnRandomCrates& crates);
        void receive(const SpawnRandomPowerup& powerup);

    private:
        void registerServices(entityx::EventManager &events);

        void spawnTank(const sf::Vector2f& pos, Player player, entityx::EntityManager &es);
        void spawnCrate(const sf::Vector2f& pos, entityx::EntityManager &es);
        void spawnExplosion(const sf::Vector2f& pos, entityx::EntityManager &es);
        void spawnRandomPowerup(entityx::EventManager &events);

    private:

        struct GameplayConstants
        {
                size_t maxPowerups { 3 };
                size_t maxAi { 5 };
        } m_gameplayConstants;

        sf::Vector2u m_screenSize;

        std::vector<Collision> m_pendingCollisions;

        entityx::EntityManager* m_entityManager { nullptr };

        std::vector<SpawnTank> m_tankSpawns;
        std::vector<SpawnCrate> m_crateSpawns;
        std::vector<SpawnExplosion> m_explosionSpawns;
        std::vector<SpawnRandomPowerup> m_powerupSpawns;
};
#endif // GAMEPLAYSYSTEM_HPP
