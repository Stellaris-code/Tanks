/*  include/statemachine.hpp StateMachine - Yann BOUCHER (yann) 05/11/2016
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
#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <stack>

#include "utils.hpp"

#include "stateid.hpp"
#include "statefactory.hpp"
#include "context.hpp"

#include "noncopyable.hpp"

DECLARE_EXCEPTION(statemachine, "State machine")

class StateMachine :
        private Noncopyable
{
    public:
        explicit StateMachine(Context& context);

    public:
        void changeState(StateID t_state);
        void pushState(StateID t_state);
        void popState();
        void clearStates();
        void resetTo(StateID t_state);

        const std::unique_ptr<State>& top() const
        { return m_states.top(); }
        std::unique_ptr<State>& top()
        { return m_states.top(); }

        bool empty() const
        { return m_states.empty(); }

        size_t size() const
        { return m_states.size(); }

    private:
        std::stack<std::unique_ptr<State>> m_states;
        Context& m_context;
};

#endif // STATEMACHINE_HPP
