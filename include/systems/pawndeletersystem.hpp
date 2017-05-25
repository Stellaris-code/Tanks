/*  include/systems/pawndeletersystem.hpp PawnDeleterSystem - Yann BOUCHER (yann) 16/11/2016
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
#ifndef PAWNDELETERSYSTEM_HPP
#define PAWNDELETERSYSTEM_HPP


#include <vector>

#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "events.hpp"

#include "utils.hpp"

DECLARE_EXCEPTION(pawn_not_found, "Tried to destroy unknown pawn !")

class PawnDeleterSystem :
        private Noncopyable,
        public entityx::System<PawnDeleterSystem>,
        public entityx::Receiver<PawnDeleterSystem>
{
    public:
        PawnDeleterSystem() = default;

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<PawnDeletionRequest>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const PawnDeletionRequest& request);

    private:
        std::vector<Player> m_requests;
};

#endif // PAWNDELETERSYSTEM_HPP
