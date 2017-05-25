/*  src/systems/pawnnamesystem.cpp PawnNameSystem - Yann BOUCHER (yann) 23/11/2016
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
#include "systems/pawnnamesystem.hpp"

#include "components/pawn.hpp"
#include "components/transform.hpp"

void PawnNameSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Pawn, Transform>([this, &es](entityx::Entity ent, Pawn& pawn, Transform& trans)
    {
        auto it = m_texts.find(ent.id());
        if (it == m_texts.cend())
        {
            auto text = es.create();
            text.assign<Transform>()->setPosition(trans.getPosition() + sf::Vector2f(0, -60));
            auto drawable = text.assign<Drawable>();
            drawable->origin = {0.5, 0};
            drawable->zorder = 30;
            drawable->text = Text{};
            if (pawn.controller >= Player::AI)
            {
                drawable->text->text = "AI";
            }
            else if (pawn.controller == Player::One)
            {
                drawable->text->text = "Player 1";
            }
            else if (pawn.controller == Player::Two)
            {
                drawable->text->text = "Player 2";
            }
            else if (pawn.controller == Player::Three)
            {
                drawable->text->text = "Player 3";
            }
            else if (pawn.controller == Player::Four)
            {
                drawable->text->text = "Player 4";
            }
            drawable->text->outlinethickness = 1;
            drawable->text->outlinecolor = sf::Color::Black;

            m_texts[ent.id()] = text;
        }
        else
        {
            auto text = it->second;
            text.component<Transform>()->setPosition(trans.getPosition() + sf::Vector2f(0, -60));
        }
    });
}

void PawnNameSystem::receive(const entityx::EntityDestroyedEvent &event)
{
    if (m_texts.count(event.entity.id()) != 0)
    {
        m_texts[event.entity.id()].destroy();
        m_texts.erase(event.entity.id());
    }
}
