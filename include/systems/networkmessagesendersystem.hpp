/*  include/systems/networkmessagesystem.hpp NetworkMessageSystem - Yann BOUCHER (yann) 11/11/2016
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
#ifndef NETWORKMESSAGESYSTEM_HPP
#define NETWORKMESSAGESYSTEM_HPP


#include <entityx/System.h>
#include <entityx/Event.h>

#include <SFML/Network/UdpSocket.hpp>

#include <SFML/System/Time.hpp>

#include "noncopyable.hpp"

#include "networkpacket.hpp"

#include "player.hpp"

#include "context.hpp"

#include "events.hpp"

class NetworkMessageSenderSystem :
        private Noncopyable,
        public entityx::System<NetworkMessageSenderSystem>,
        public entityx::Receiver<NetworkMessageSenderSystem>
{
    public:
        NetworkMessageSenderSystem(const NetworkOptions& netoptions, sf::Time updateTime = sf::Time::Zero)
            : m_netoptions(netoptions), m_updateTime(updateTime)
        {
            m_socket.setBlocking(false);
        }

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<SendNetworkPacket>(*this);
            event_manager.subscribe<Quit>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const SendNetworkPacket& packet);

        void receive(const Quit&);

    private:
        void send();

    private:
        const NetworkOptions& m_netoptions;

        const sf::Time m_updateTime;
        sf::Time m_elapsedTime { sf::Time::Zero };

        bool m_firstRun { true };

        NetworkPacket m_packet;

        sf::UdpSocket m_socket;
};

#endif // NETWORKMESSAGESYSTEM_HPP
