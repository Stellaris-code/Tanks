/*  lifetime %{Cpp:License:ClassName} - Yann BOUCHER (yann) 09/11/2016
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
#ifndef LIFETIME_HPP
#define LIFETIME_HPP

#include <entityx/Entity.h>

#include <SFML/System/Time.hpp>

struct Lifetime : public entityx::Component<Lifetime>
{
        Lifetime() = default;
        explicit Lifetime(const sf::Time& time)
            : lifetime(time)
        {}
        sf::Time lifetime;

        sf::Time progress;
};

#endif // LIFETIME_HPP
