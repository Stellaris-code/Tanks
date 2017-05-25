/*  src/systems/scorepanelsystem.cpp ScorePanelSystem - Yann BOUCHER (yann) 15/12/2016
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
#include "systems/scorepanelsystem.hpp"

#include "components/transform.hpp"
#include "components/drawable.hpp"
#include "components/pawn.hpp"

#include "utils.hpp"

void ScorePanelSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    if (!m_scoreText.valid())
    {
        m_scoreText = es.create();
        m_scoreText.assign<Transform>()->setPosition(m_winSize.x - 30, 30);
        auto drawable = m_scoreText.assign<Drawable>();
        drawable->origin = {1, 0};
        drawable->zorder = 30;
        drawable->text = Text{};
        drawable->text->outlinecolor = sf::Color::Black;
        drawable->text->outlinethickness = 1;
        drawable->text->size = 35;
        drawable->text->text = "Score : 0";
    }

    if (!m_timeText.valid())
    {
        m_timeText = es.create();
        m_timeText.assign<Transform>()->setPosition(m_winSize.x - 30, 70);
        auto drawable = m_timeText.assign<Drawable>();
        drawable->origin = {1, 0};
        drawable->zorder = 30;
        drawable->text = Text{};
        drawable->text->outlinecolor = sf::Color::Black;
        drawable->text->outlinethickness = 1;
        drawable->text->size = 35;
        drawable->text->text = "Time : 0:00";
    }

    for (auto event : m_destroyedPawns)
    {
        if (es.valid(event.instigator) && es.component<Pawn>(event.instigator)->controller == m_player)
        {
            m_score += 500;
            m_scoreText.component<Drawable>()->text->text = "Score : " + std::to_string(m_score);
        }
    }

    m_time += sf::seconds(dt);

    m_timeText.component<Drawable>()->text->text = "Time : " + std::to_string(int(m_time.asSeconds()) / 60) +
                                                   ":" + to_string_pad_zeroes(int(m_time.asSeconds()) % 60, 2);

    m_destroyedPawns.clear();
}

void ScorePanelSystem::receive(const PawnDestroyed &pawnDestroyed)
{
    m_destroyedPawns.push_back(pawnDestroyed);
}
