/*  include/systems/networkmessagereceiversystem.hpp NetworkMessageReceiverSystem - Yann BOUCHER (yann) 12/11/2016
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
#ifndef NETWORKMESSAGERECEIVERSYSTEM_HPP
#define NETWORKMESSAGERECEIVERSYSTEM_HPP

#include <entityx/System.h>

#include <SFML/Network/UdpSocket.hpp>

#include "context.hpp"

#include "noncopyable.hpp"

#include "utils.hpp"

DECLARE_EXCEPTION(cannot_listen_to_port, "Cannot listen to port !");

class NetworkMessageReceiverSystem :
        private Noncopyable,
        public entityx::System<NetworkMessageReceiverSystem>
{
    public:
        NetworkMessageReceiverSystem(const NetworkOptions& netoptions)
        {
            m_socket.setBlocking(false);
            if (m_socket.bind(netoptions.receivePort()) != sf::Socket::Done)
            {
                throw_cannot_listen_to_port_error(" (port : " + std::to_string(netoptions.receivePort()) + ")");
            }
        }

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

    private:
        sf::UdpSocket m_socket;
};

#endif // NETWORKMESSAGERECEIVERSYSTEM_HPP
