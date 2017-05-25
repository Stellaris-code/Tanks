/*  include/drawables/lifebar.hpp Lifebar - Yann BOUCHER (yann) 20/11/2016
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
#ifndef LIFEBAR_HPP
#define LIFEBAR_HPP

#include <entityx/Entity.h>

#include "components/drawable.hpp"

class Lifebar
{
    public:
        Lifebar(entityx::EntityManager& ents);
        ~Lifebar();

    public:
        void setColor(const sf::Color& color);
        void setPosition(const sf::Vector2f& pos);
        void setSize(const sf::Vector2f& size);

        void setHealth(float percent);

        void setVisible(bool visible);

    private:
        entityx::Entity m_border;
        entityx::Entity m_bar;
};

#endif // LIFEBAR_HPP
