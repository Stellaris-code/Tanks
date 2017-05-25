/*  include/systems/networkeventtranslator.hpp NetworkEventTranslator - Yann BOUCHER (yann) 13/11/2016
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
#ifndef NETWORKEVENTTRANSLATOR_HPP
#define NETWORKEVENTTRANSLATOR_HPP

#include <entityx/System.h>

#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/SocketSelector.hpp>

#include "noncopyable.hpp"

#include "events.hpp"

class NetworkEventTranslator :
        private Noncopyable,
        public entityx::System<NetworkEventTranslator>,
        public entityx::Receiver<NetworkEventTranslator>
{
    public:
        NetworkEventTranslator(bool isServer)
            : m_isServer(isServer)
        {}

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<RequestDraw>(*this);
            event_manager.subscribe<PlayerEventFire>(*this);
            event_manager.subscribe<PlayerEventMove>(*this);
            event_manager.subscribe<PlayerEventTurn>(*this);
            event_manager.subscribe<PlayerEventPointTo>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override
        {
            m_events = &events;
        }

        void receive(const RequestDraw& request);
        void receive(const PlayerEventFire&);
        void receive(const PlayerEventMove& move);
        void receive(const PlayerEventTurn& turn);
        void receive(const PlayerEventPointTo& pointTo);

    private:
        entityx::EventManager* m_events { nullptr };

        bool m_isServer { true };
};

#endif // NETWORKEVENTTRANSLATOR_HPP
