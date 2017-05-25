/*  src/systems/lifebarsystem.cpp LifebarSystem - Yann BOUCHER (yann) 20/11/2016
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
#include "systems/lifebarsystem.hpp"

#include "components/health.hpp"
#include "components/transform.hpp"

void LifebarSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Health, Transform>([this, &es](entityx::Entity ent, Health& health, Transform& transform)
    {
        if (m_lifebars.count(ent.id()) == 0)
        {
            m_lifebars.emplace(ent.id(), es);
        }

        m_lifebars.at(ent.id()).setPosition(transform.getPosition() + sf::Vector2f(0, -35));
        m_lifebars.at(ent.id()).setHealth(health.health / health.maxHealth * 100);

        m_lifebars.at(ent.id()).setVisible(health.showHealth);
    });
}

void LifebarSystem::receive(const entityx::EntityDestroyedEvent &event)
{
    auto it = m_lifebars.find(event.entity.id());
    if (it != m_lifebars.cend())
    {
        m_lifebars.erase(it);
    }
}
