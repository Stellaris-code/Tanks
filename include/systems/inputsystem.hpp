/*  include/systems/inputsystem.hpp InputSystem - Yann BOUCHER (yann) 05/11/2016
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
#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include <entityx/System.h>

#include "noncopyable.hpp"

namespace sf
{
class Window;
}

class InputSystem :
        private Noncopyable,
        public entityx::System<InputSystem>
{
    public:
        explicit InputSystem(sf::Window &win);

    public:
        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

    private:
        sf::Window& m_win;
};


#endif // INPUTSYSTEM_HPP
