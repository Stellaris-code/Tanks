/*  src/systems/shieldsystem.cpp ShieldSystem - Yann BOUCHER (yann) 27/11/2016
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
#include "systems/shieldsystem.hpp"

#include "components/pawn.hpp"
#include "components/health.hpp"
#include "components/transform.hpp"
#include "components/drawable.hpp"
#include "components/childentities.hpp"

void ShieldSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Pawn, Health>([this, &es, dt](entityx::Entity ent, Pawn& pawn, Health& health)
    {
        for (const auto& event : m_events)
        {
            if (pawn.controller == event.player)
            {
                health.hasShield = true;
                createShield(es, ent);
            }
        }
    });

    std::vector<entityx::Entity> shieldsToDelete;

    for (auto& pair : m_shieldsProgress)
    {
        pair.second += sf::seconds(dt);

        if (pair.second >= m_shieldDuration)
        {
            es.destroy(pair.first.id());
            shieldsToDelete.push_back(pair.first);
        }
    }

    for (auto shield : shieldsToDelete)
    {
        m_shieldsProgress.erase(shield);
    }

    m_events.clear();
}

void ShieldSystem::receive(const CreateShield &event)
{
    m_events.push_back(event);
}

void ShieldSystem::receive(const entityx::EntityDestroyedEvent &event)
{
    m_shieldsProgress.erase(event.entity);
}

void ShieldSystem::createShield(entityx::EntityManager &es, entityx::Entity pawn)
{
    auto shield = es.create();
    shield.assign<Transform>()->setPosition(pawn.component<Transform>()->getPosition());
    shield.component<Transform>()->setRotation(pawn.component<Transform>()->getRotation() + 180);
    shield.component<Transform>()->setScale(pawn.component<Transform>()->getScale());

    sf::Color color = sf::Color::White;

    if (pawn.component<Pawn>()->controller == Player::One)
    {
        color = sf::Color::Blue;
    }
    else if (pawn.component<Pawn>()->controller == Player::Two)
    {
        color = sf::Color::Red;
    }
    else if (pawn.component<Pawn>()->controller == Player::Three)
    {
        color = sf::Color::Green;
    }
    else if (pawn.component<Pawn>()->controller == Player::Four)
    {
        color = sf::Color::Black;
    }

    shield.assign<Drawable>("shield", sf::Vector2f{0.5, 0.5})->color = color;
    shield.component<Drawable>()->zorder = 5;

    m_shieldsProgress[shield] = sf::Time::Zero;

    pawn.component<ChildEntities>()->entities.push_back(shield);
}
