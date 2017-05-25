/*  src/systems/networkmessagereceiversystem.cpp NetworkMessageReceiverSystem - Yann BOUCHER (yann) 12/11/2016
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
#include "systems/networkmessagereceiversystem.hpp"

#include <SFML/Network/Packet.hpp>

#include "lambdavisitor.hpp"

#include "events.hpp"

void NetworkMessageReceiverSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    sf::IpAddress address;
    unsigned short port;
    sf::Packet sfpacket;
    auto status = m_socket.receive(sfpacket, address, port);
    if (status == sf::Socket::Done)
    {
        NetworkPacket netpacket;

        sfpacket >> netpacket;

        bool disconnect { false };

        for (auto packet : netpacket.packets)
        {
            switch (packet.type)
            {
                case NetworkPacketType::Connect:
                    events.emit<NewConnection>({address});
                    break;

                case NetworkPacketType::Disconnect:
                    events.emit<ConnectionEnded>({address});
                    break;

                case NetworkPacketType::PlayerFire:
                    events.emit<NetworkPlayerEventFire>({address});
                    break;

                case NetworkPacketType::PlayerMove:
                    events.emit<NetworkPlayerEventMove>({address, packet.amount});
                    break;

                case NetworkPacketType::PlayerTurn:
                    events.emit<NetworkPlayerEventTurn>({address, packet.amount});
                    break;

                case NetworkPacketType::PlayerPointTo:
                    events.emit<NetworkPlayerEventPointTo>({address, packet.point});
                    break;

                case NetworkPacketType::RenderDrawable:
                    events.emit<RequestDraw>({packet.drawables});
                    break;
            }
        }
    }
}
