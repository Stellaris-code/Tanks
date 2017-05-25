/*  hitbox %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef HITBOX_HPP
#define HITBOX_HPP

#include <memory>

#include <SFML/Graphics/Shape.hpp>

#include <entityx/Entity.h>

struct Hitbox : public entityx::Component<Hitbox>
{
        Hitbox() = default;
        Hitbox(const Hitbox& other)
        {
            hitbox = nullptr; // no copy should exist !
            explosionOnHit = other.explosionOnHit;
        }

        std::unique_ptr<sf::Shape> hitbox { nullptr };

        bool solid { true };
        bool explosionOnHit { true };
};

#endif // HITBOX_HPP
