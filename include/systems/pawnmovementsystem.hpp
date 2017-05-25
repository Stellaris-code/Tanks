/*  include/systems/pawnmovementsystem.hpp PawnMovementSystem - Yann BOUCHER (yann) 05/11/2016
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
#ifndef PAWNMOVEMENTSYSTEM_HPP
#define PAWNMOVEMENTSYSTEM_HPP

#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "events.hpp"

class PawnMovementSystem :
        private Noncopyable,
        public entityx::System<PawnMovementSystem>,
        public entityx::Receiver<PawnMovementSystem>
{
    public:
        PawnMovementSystem() = default;

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<PlayerEventMove>(*this);
            event_manager.subscribe<PlayerEventTurn>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const PlayerEventMove& move);
        void receive(const PlayerEventTurn& turn);

    private:
        std::vector<PlayerEventMove> m_moves;

        std::vector<PlayerEventTurn> m_turns;
};

#endif // PAWNMOVEMENTSYSTEM_HPP
