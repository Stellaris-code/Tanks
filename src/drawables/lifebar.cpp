/*  src/drawables/lifebar.cpp Lifebar - Yann BOUCHER (yann) 20/11/2016
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
#include "drawables/lifebar.hpp"

#include "components/transform.hpp"
#include "components/drawable.hpp"

Lifebar::Lifebar(entityx::EntityManager &ents)
{
    {
        m_border = ents.create();
        m_border.assign<Transform>()->setPosition({100, 100});
        auto drawable = m_border.assign<Drawable>("lifebar_border");
        drawable->zorder = 20;
        drawable->origin = {0.5f, 0};
    }

    {
        m_bar = ents.create();
        m_bar.assign<Transform>()->setPosition({100, 100});
        auto drawable = m_bar.assign<Drawable>("");
        drawable->zorder = 19;
    }

    setSize({50, 10});
    setColor(sf::Color::Red);
}

Lifebar::~Lifebar()
{
    m_border.destroy();
    m_bar.destroy();
}

void Lifebar::setColor(const sf::Color &color)
{
    m_border.component<Drawable>()->color = color;
    m_bar.component<Drawable>()->color = color;
}

void Lifebar::setPosition(const sf::Vector2f &pos)
{
    m_border.component<Transform>()->setPosition(pos);
    m_bar.component<Transform>()->setPosition(pos + sf::Vector2f(1, 1) - sf::Vector2f(m_border.component<Drawable>()->spriteSize.x * 0.5f,
                                                                                      0));
}

void Lifebar::setSize(const sf::Vector2f &size)
{
    m_border.component<Drawable>()->spriteSize = size;
    m_bar.component<Drawable>()->spriteSize = size - sf::Vector2f(2, 2);
}

void Lifebar::setHealth(float percent)
{
    m_bar.component<Drawable>()->spriteSize = {m_border.component<Drawable>()->spriteSize.x * percent/100 - 2,
                                              m_border.component<Drawable>()->spriteSize.y - 2};
}

void Lifebar::setVisible(bool visible)
{
    m_border.component<Drawable>()->visible = visible;
    m_bar.component<Drawable>()->visible = visible;
}
