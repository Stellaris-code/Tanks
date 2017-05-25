/*  src/systems/powerupsystem.cpp PowerupSystem - Yann BOUCHER (yann) 26/11/2016
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
#include "systems/powerupsystem.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

#include "components/transform.hpp"
#include "components/drawable.hpp"
#include "components/hitbox.hpp"
#include "components/tank.hpp"
#include "components/pawn.hpp"

void PowerupSystem::receive(const SpawnPowerup &powerup)
{
    m_spawnRequests.push_back(powerup);
}

void PowerupSystem::receive(const Collision &collision)
{
    m_pendingCollisions.push_back(collision);
}

void PowerupSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    for (const auto& request : m_spawnRequests)
    {
        spawnPowerup(es, request.type, request.pos);
    }

    m_spawnRequests.clear();

    for (const auto& collision : m_pendingCollisions)
    {
        if (es.valid(collision.lhs) && es.valid(collision.rhs) && (
                    (es.has_component<Tank>(collision.lhs) && es.has_component<Powerup>(collision.rhs)) ||
                    (es.has_component<Powerup>(collision.lhs) && es.has_component<Tank>(collision.rhs))))
        {
            auto tankId = [&]()
            {
                if (es.has_component<Tank>(collision.lhs))
                {
                    return collision.lhs;
                }
                else
                {
                    return collision.rhs;
                }
            }();

            auto powerupId = [&]()
            {
                if (es.has_component<Powerup>(collision.lhs))
                {
                    return collision.lhs;
                }
                else
                {
                    return collision.rhs;
                }
            }();

            switch (es.component<Powerup>(powerupId)->type)
            {
                case Powerup::Type::Shield:
                    events.emit<CreateShield>({es.component<Pawn>(tankId)->controller});
                    break;

                case Powerup::Type::TripleShoot:
                    events.emit<EnableTripleShoot>({es.component<Pawn>(tankId)->controller});
                    break;
            }

            es.destroy(powerupId);

        }
    }

    m_pendingCollisions.clear();
}

void PowerupSystem::spawnPowerup(entityx::EntityManager &es, Powerup::Type type, const sf::Vector2f &pos)
{
    auto powerup = es.create();
    powerup.assign<Transform>()->setPosition(pos);

    std::string texId;
    switch (type)
    {
        case Powerup::Type::Shield:
            texId = "shield_powerup";
            break;

        case Powerup::Type::TripleShoot:
            texId = "tripleshoot_powerup";
            break;
    }

    powerup.assign<Drawable>(texId, sf::Vector2f{0.5, 0.5})->zorder = 1;
    powerup.assign<Powerup>(type);
    powerup.assign<Hitbox>()->hitbox = std::make_unique<sf::RectangleShape>(sf::Vector2f{34, 34});
    powerup.component<Hitbox>()->hitbox->setPosition({-34/2, -34/2});
    powerup.component<Hitbox>()->hitbox->setOrigin({34/2, 34/2});
    powerup.component<Hitbox>()->solid = false;
}
