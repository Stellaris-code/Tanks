/*  include/systems/scorepanelsystem.hpp ScorePanelSystem - Yann BOUCHER (yann) 15/12/2016
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
#ifndef SCOREPANELSYSTEM_HPP
#define SCOREPANELSYSTEM_HPP

#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "events.hpp"

#include "player.hpp"

#include "utils.hpp"

class ScorePanelSystem :
        private Noncopyable,
        public entityx::System<ScorePanelSystem>,
        public entityx::Receiver<ScorePanelSystem>
{
    public:
        ScorePanelSystem(Player player, const sf::Vector2u& winSize)
            : m_player(player), m_winSize(winSize)
        {}

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<PawnDestroyed>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const PawnDestroyed& pawnDestroyed);

    private:
        Player m_player;
        sf::Vector2u m_winSize;

        int m_score { 0 };
        sf::Time m_time { sf::Time::Zero };

        std::vector<PawnDestroyed> m_destroyedPawns;

        entityx::Entity m_scoreText;
        entityx::Entity m_timeText;
};

#endif // SCOREPANELSYSTEM_HPP
