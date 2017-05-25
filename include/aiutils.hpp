/*  aiutils %{Cpp:License:ClassName} - Yann BOUCHER (yann) 20/11/2016
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
#ifndef AIUTILS_HPP
#define AIUTILS_HPP

#include <random>

#include <SFML/System/Vector2.hpp>

#include <entityx/Entity.h>

#include <Thor/Vectors/VectorAlgebra2D.hpp>

#include "components/pawn.hpp"
#include "components/transform.hpp"

inline sf::Vector2f randomPointInRingAroundSource(const sf::Vector2f& source, float innerRadius, float outerRadius, const sf::Vector2f& bounds)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(innerRadius, outerRadius);
    std::uniform_real_distribution<float> angle(0, 360);

    sf::Vector2f point;

    do
    {
        point = dist(mt) * thor::rotatedVector({1, 0}, angle(mt)) + source;

    } while(point.x < 0 || point.y < 0 || point.x > bounds.x || point.y > bounds.y);

    return point;
}

inline entityx::Entity::Id getClosestPlayer(Player self, entityx::EntityManager& es, const sf::Vector2f& pos)
{
    entityx::Entity::Id id = entityx::Entity::INVALID;
    float dist { -1 };
    es.each<Pawn, Transform>([self, &id, &dist, pos](entityx::Entity ent, Pawn& pawn, Transform& transform)
    {
        if (pawn.controller != self && pawn.controller != Player::None)
        {
            auto pawnDist = thor::squaredLength(transform.getPosition() - pos);
            if (dist < 0 || pawnDist < dist)
            {
                dist = pawnDist;
                id = ent.id();
            }
        }
    });

    return id;
}

#endif // AIUTILS_HPP
