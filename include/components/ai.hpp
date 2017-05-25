/*  ai %{Cpp:License:ClassName} - Yann BOUCHER (yann) 20/11/2016
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
#ifndef AI_HPP
#define AI_HPP

#include <SFML/System/Vector2.hpp>

#include <entityx/Entity.h>

#include "player.hpp"

struct Ai : public entityx::Component<Ai>
{
        explicit Ai(const sf::Vector2f& inTarget = {-1, -1}) : target(inTarget)
        {
            id = idAmount + Player::AI;
            ++idAmount;
        }

        ~Ai()
        {
            --idAmount;
        }

        size_t id { 0 };
        sf::Vector2f target { -1, -1 };
        bool reachedTarget { true };

        void changeTarget(const sf::Vector2f& newTarget)
        {
            if (reachedTarget)
            {
                target = newTarget;
                reachedTarget = false;
            }
        }

        static size_t idAmount;
};

#endif // AI_HPP
