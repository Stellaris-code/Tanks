/*  pawn %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef PAWN_HPP
#define PAWN_HPP

#include <entityx/Entity.h>

#include "player.hpp"

struct Pawn : public entityx::Component<Pawn>
{
        Pawn() = default;
        explicit Pawn(Player player) : controller(player)
        {}
        Player controller { Player::None };

        double speed { 150 };
};

#endif // PAWN_HPP
