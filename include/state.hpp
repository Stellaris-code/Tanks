/*  state %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/System/Time.hpp>

#include "noncopyable.hpp"

#include "stateid.hpp"

class State :
        private Noncopyable
{
    public:
        virtual void activate(StateID previous) = 0;
        virtual void deactivate(StateID next) = 0;

        virtual void update(const sf::Time& dt) = 0;

        virtual StateID type() const = 0;
};

#endif // STATE_HPP
