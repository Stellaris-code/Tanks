/*  include/gamestate.hpp GameState - Yann BOUCHER (yann) 05/11/2016
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
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <entityx/entityx.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include "state.hpp"
#include "stateid.hpp"

#include "events.hpp"

#include "context.hpp"

class GameState :
        public State,
        public entityx::EntityX,
        public entityx::Receiver<GameState>
{
    public:
        explicit GameState(Context& context);

    public:
        virtual void activate(StateID previous) override {};
        virtual void deactivate(StateID next) override {};

        virtual void update(const sf::Time& dt) override;

        virtual StateID type() const override { return StateID::ServerGame; }

        void receive(const Quit& quit);

    private:
        void configureSystems();
        void createEntities();
        void createResources();

    private:
        Context& m_context;
};

#endif // GAMESTATE_HPP
