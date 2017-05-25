/*  include/systems/networkinputhandler.hpp NetworkInputHandler - Yann BOUCHER (yann) 13/11/2016
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
#ifndef NETWORKINPUTHANDLER_HPP
#define NETWORKINPUTHANDLER_HPP

#include <map>

#include <entityx/System.h>

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/SocketSelector.hpp>

#include "noncopyable.hpp"

#include "events.hpp"

class NetworkInputHandler :
        private Noncopyable,
        public entityx::System<NetworkInputHandler>,
        public entityx::Receiver<NetworkInputHandler>
{
    public:
        NetworkInputHandler() = default;

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<NewConnection>(*this);
            event_manager.subscribe<ConnectionEnded>(*this);
            event_manager.subscribe<NetworkPlayerEventFire>(*this);
            event_manager.subscribe<NetworkPlayerEventMove>(*this);
            event_manager.subscribe<NetworkPlayerEventTurn>(*this);
            event_manager.subscribe<NetworkPlayerEventPointTo>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override
        {
            m_events = &events;
        }

        void receive(const NewConnection& co);
        void receive(const ConnectionEnded& co);
        void receive(const NetworkPlayerEventFire&fire);
        void receive(const NetworkPlayerEventMove& move);
        void receive(const NetworkPlayerEventTurn& turn);
        void receive(const NetworkPlayerEventPointTo& pointTo);

    private:
        entityx::EventManager* m_events { nullptr };

        std::map<sf::IpAddress, Player> m_clients;
};

#endif // NETWORKINPUTHANDLER_HPP
