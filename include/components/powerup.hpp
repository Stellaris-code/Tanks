/*  powerup %{Cpp:License:ClassName} - Yann BOUCHER (yann) 26/11/2016
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
#ifndef POWERUP_HPP
#define POWERUP_HPP

#include <functional>

#include <entityx/Entity.h>

#include "player.hpp"

struct Powerup : public entityx::Component<Powerup>
{
        enum class Type
        {
            Shield,
            TripleShoot,
            MAX
        };

        Powerup() = default;
        explicit Powerup(Type inType)
            : type(inType)
        {}

        Type type;
};

#endif // POWERUP_HPP
