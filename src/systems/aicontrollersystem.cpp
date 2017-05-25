/*  src/systems/aicontrollersystem.cpp AiControllerSystem - Yann BOUCHER (yann) 20/11/2016
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
#include "systems/aicontrollersystem.hpp"

#include <random>

#include "aiutils.hpp"
#include "utils.hpp"
#include "events.hpp"

void AiControllerSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Ai, Transform>([this, &es, &events](entityx::Entity, Ai& ai, Transform& transform)
    {
        auto id = getClosestPlayer((Player)ai.id, es, transform.getPosition());
        if (id != entityx::Entity::INVALID)
        {
            auto target = es.get(id);
            ai.changeTarget(randomPointInRingAroundSource(target.component<Transform>()->getPosition(), 50, 200, m_winSize));

            handleMovement(events, ai, transform);

            if (turnTurret(ai.id, events, target.component<Transform>()->getPosition()))
            {
                fire(ai.id, events);
            }
        }
    });
}

void AiControllerSystem::receive(const CanFire &fire)
{
    if (fire.player >= Player::AI)
    {
        m_canFire[fire.player] = true;
    }
}

void AiControllerSystem::handleMovement(entityx::EventManager &events, Ai &ai, Transform trans)
{
    sf::Vector2f dir = ai.target - trans.getPosition();
    if (dir == sf::Vector2f())
    {
        dir = sf::Vector2f(1, 0);
    }

    thor::rotate(dir, 90.f);

    dir = thor::unitVector(dir);

    float angle = thor::polarAngle(dir) + 180;

    if (turn(ai.id, events, trans, angle))
    {
        if (move(ai.id, events, trans, ai.target))
        {
            ai.reachedTarget = true;
        }
    }
}

bool AiControllerSystem::turn(int id, entityx::EventManager &events, Transform trans, float angle)
{
    if (!nearlyEqual(trans.getRotation(), angle, m_movementTolerance))
    {
        double delta = angle - trans.getRotation();

        if (std::abs(delta) > std::abs(delta - 360))
        {
            delta = delta - 360;
        }
        else if (std::abs(delta) > std::abs(delta + 360))
        {
            delta = delta + 360;
        }

        double sign = sgn(delta);
        events.emit(PlayerEventTurn{(Player)id, sign});

        return false;
    }
    else
    {
        return true;
    }
}

bool AiControllerSystem::move(int id, entityx::EventManager &events, Transform trans, const sf::Vector2f &pos)
{
    if (!nearlyEqual(trans.getPosition().x, pos.x, m_movementTolerance) ||
            !nearlyEqual(trans.getPosition().y, pos.y, m_movementTolerance))
    {
        events.emit(PlayerEventMove{(Player)id, 1});

        return false;
    }
    else
    {
        return true;
    }
}

bool AiControllerSystem::turnTurret(int id, entityx::EventManager &events, const sf::Vector2f &pos)
{
    if (m_chooseNextPointTo[id])
    {
        m_chooseNextPointTo[id] = false;

        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<float> dist(-m_precision, m_precision);

        m_turretPointTo[id] = thor::rotatedVector(pos, dist(mt));
    }

    events.emit(PlayerEventPointTo{(Player)id, m_turretPointTo[id]});

    return true;
}

bool AiControllerSystem::fire(int id, entityx::EventManager &events)
{
    if (m_canFire[id])
    {
        events.emit(PlayerEventFire{(Player)id});

        m_chooseNextPointTo[id] = true;
        m_canFire[id] = false;

        return true;
    }

    return false;
}
