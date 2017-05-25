/*  src/systems/pawnmovementsystem.cpp PawnMovementSystem - Yann BOUCHER (yann) 05/11/2016
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
#include "systems/pawnmovementsystem.hpp"

#include <Thor/Vectors/VectorAlgebra2D.hpp>

#include "components/pawn.hpp"
#include "components/transform.hpp"
#include "components/childentities.hpp"
#include "components/ai.hpp"

void PawnMovementSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    for (const auto& move : m_moves)
    {
        es.each<Pawn, Transform>([this, dt, &es, move](entityx::Entity ent, Pawn& pawn, Transform& transform)
        {
            if (pawn.controller == move.player)
            {
                sf::Vector2f offset = {0.f, float(move.amount * dt * pawn.speed)};
                thor::rotate(offset, transform.getRotation());

                transform.move(offset);
                if (ent.has_component<ChildEntities>())
                {
                    for (auto& child : ent.component<ChildEntities>()->entities)
                    {
                        if (child.inheritPos && child.ent.valid() && child.ent.has_component<Transform>())
                        {
                            child.ent.component<Transform>()->move(offset);
                        }
                    }
                }
            }
        });
    }

    m_moves.clear();

    for (const auto& turn : m_turns)
    {
        es.each<Pawn, Transform>([this, dt, &es, turn](entityx::Entity ent, Pawn& pawn, Transform& transform)
        {
            if (pawn.controller == turn.player)
            {
                transform.rotate(turn.amount * dt * pawn.speed);
                if (ent.has_component<ChildEntities>())
                {
                    for (auto& child : ent.component<ChildEntities>()->entities)
                    {
                        if (child.inheritRot && child.ent.valid() && child.ent.has_component<Transform>())
                        {
                            child.ent.component<Transform>()->rotate(turn.amount * dt * pawn.speed);
                        }
                    }
                }
            }

        });
    }

    m_turns.clear();
}

void PawnMovementSystem::receive(const PlayerEventMove &move)
{
    m_moves.push_back(move);
}

void PawnMovementSystem::receive(const PlayerEventTurn &turn)
{
    m_turns.push_back(turn);
}
