/*  src/statemachine.cpp StateMachine - Yann BOUCHER (yann) 05/11/2016
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
#include "statemachine.hpp"

StateMachine::StateMachine(Context &context)
    : m_context(context)
{

}

void StateMachine::changeState(StateID t_state)
{
    if (!m_states.empty())
    {
        popState();
    }

    pushState(t_state);
}

void StateMachine::pushState(StateID t_state)
{
    m_states.push(makeState(t_state, m_context));
}

void StateMachine::popState()
{
    if (m_states.empty())
    {
        throw_statemachine_error("Tried to pop empty state stack !");
    }

    m_states.pop();
}

void StateMachine::clearStates()
{
    while (!empty())
    {
        popState();
    }
}

void StateMachine::resetTo(StateID t_state)
{
    while (size() > 1)
    {
        popState();
    }
    changeState(t_state);
}
