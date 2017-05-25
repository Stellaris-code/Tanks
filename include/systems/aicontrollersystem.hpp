/*  include/systems/aicontrollersystem.hpp AiControllerSystem - Yann BOUCHER (yann) 20/11/2016
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
#ifndef AICONTROLLERSYSTEM_HPP
#define AICONTROLLERSYSTEM_HPP


#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "components/ai.hpp"
#include "components/transform.hpp"

#include "events.hpp"

class AiControllerSystem :
        private Noncopyable,
        public entityx::System<AiControllerSystem>,
        public entityx::Receiver<AiControllerSystem>
{
    public:
        AiControllerSystem(const sf::Vector2u& winSize)
            : m_winSize(sf::Vector2f(winSize))
        {}

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<CanFire>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const CanFire& fire);

    private:
        void handleMovement(entityx::EventManager &events, Ai& ai, Transform trans);

        bool turn(int id, entityx::EventManager &events, Transform trans, float angle);
        bool move(int id, entityx::EventManager &events, Transform trans, const sf::Vector2f& pos);

        bool turnTurret(int id, entityx::EventManager &events, const sf::Vector2f& pos);
        bool fire(int id, entityx::EventManager &events);

    private:
        float m_movementTolerance { 4.f };
        float m_precision { 30.f };

        std::map<int, bool> m_chooseNextPointTo {};
        std::map<int, bool> m_canFire {};

        std::map<int, sf::Vector2f> m_turretPointTo;

        sf::Vector2f m_winSize;
};

#endif // AICONTROLLERSYSTEM_HPP
