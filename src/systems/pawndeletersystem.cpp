/*  src/systems/pawndeletersystem.cpp PawnDeleterSystem - Yann BOUCHER (yann) 16/11/2016
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
#include "systems/pawndeletersystem.hpp"

#include <algorithm>

#include "components/pawn.hpp"

void PawnDeleterSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Pawn>([this](entityx::Entity ent, Pawn& pawn)
    {
        auto it = std::find(m_requests.begin(), m_requests.end(), pawn.controller);
        if (it != m_requests.end())
        {
            ent.destroy();
            m_requests.erase(it);
        }
    });

    for (auto player : m_requests)
    {
        throw_pawn_not_found_error(" player id : (" + std::to_string(player) + ")");
    }
}

void PawnDeleterSystem::receive(const PawnDeletionRequest &request)
{
    m_requests.emplace_back(request.player);
}
