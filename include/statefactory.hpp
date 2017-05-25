/*  statefactory %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef STATEFACTORY_HPP
#define STATEFACTORY_HPP

#include <memory>

#include "stateid.hpp"
#include "state.hpp"
#include "context.hpp"

#include "servergamestate.hpp"
#include "clientgamestate.hpp"

inline std::unique_ptr<State> makeState(StateID t_stateID, Context& t_context)
{
    switch (t_stateID)
    {
        //        case StateID::Menu:
        //            return std::unique_ptr<State>(std::make_unique<MenuState>(t_context));
        //        case StateID::Intro:
        //            return std::unique_ptr<State>(std::make_unique<IntroState>(t_context));
        //        case StateID::Pause:
        //            return std::unique_ptr<State>(std::make_unique<PauseState>(t_context));
        case StateID::ServerGame:
            return std::unique_ptr<State>(std::make_unique<ServerGameState>(t_context));
        case StateID::ClientGame:
            return std::unique_ptr<State>(std::make_unique<ClientGameState>(t_context));
    }
}


#endif // STATEFACTORY_HPP
