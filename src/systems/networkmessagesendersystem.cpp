/*  src/systems/networkmessagesystem.cpp NetworkMessageSystem - Yann BOUCHER (yann) 11/11/2016
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

#include "systems/networkmessagesendersystem.hpp"

#include <SFML/Network/Packet.hpp>

void NetworkMessageSenderSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    if (m_firstRun)
    {
        NetworkPacketData packetdata;
        packetdata.type = NetworkPacketType::Connect;

        NetworkPacket packet;
        packet.packets.emplace_back(packetdata);

        sf::Packet sfpacket;
        sfpacket << packet;

        m_socket.send(sfpacket, m_netoptions.address, m_netoptions.sendPort());

        m_firstRun = false;
    }

    m_elapsedTime += sf::seconds(dt);

    if (true || m_elapsedTime > m_updateTime)
    {
        send();
        m_elapsedTime = sf::Time::Zero;
    }
}

void NetworkMessageSenderSystem::receive(const SendNetworkPacket& packet)
{
    m_packet.packets.emplace_back(packet.packet);
}

void NetworkMessageSenderSystem::receive(const Quit &)
{
    NetworkPacketData packetdata;
    packetdata.type = NetworkPacketType::Disconnect;

    NetworkPacket packet;
    packet.packets.emplace_back(packetdata);

    sf::Packet sfpacket;
    sfpacket << packet;

    m_socket.send(sfpacket, m_netoptions.address, m_netoptions.sendPort());
}

void NetworkMessageSenderSystem::send()
{
    sf::Packet sfpacket;
    sfpacket << m_packet;

    m_socket.send(sfpacket, m_netoptions.address, m_netoptions.sendPort());

    m_packet.packets.clear();
}
