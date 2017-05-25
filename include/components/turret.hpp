/*  turret %{Cpp:License:ClassName} - Yann BOUCHER (yann) 06/11/2016
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
#ifndef TURRET_HPP
#define TURRET_HPP

#include <entityx/Entity.h>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include "player.hpp"

struct Turret : public entityx::Component<Turret>
{
        Turret(const sf::Vector2f& offset, Player inPlayer, sf::Time coolDown = sf::seconds(0.5))
            : fireOffset(offset), player(inPlayer), coolDownTime(coolDown)
        {}
        sf::Vector2f fireOffset { 0, 0 };

        bool tripleShoot { false };

        float rotationSpeed { 100 };

        Player player;

        sf::Time coolDownTime { sf::seconds(0.5) };
        sf::Time coolDownProgress { coolDownTime };
};

#endif // TURRET_HPP
