/*  src/systems/networkeventtranslator.cpp NetworkEventTranslator - Yann BOUCHER (yann) 13/11/2016
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
#include "systems/networkeventtranslator.hpp"

#include "networkpacket.hpp"

void NetworkEventTranslator::receive(const RequestDraw &request)
{
    if (m_events && m_isServer)
    {
        NetworkPacketData packet;
        packet.type = NetworkPacketType::RenderDrawable;
        packet.drawables = request.drawables;

        m_events->emit(SendNetworkPacket{packet});
    }
}

void NetworkEventTranslator::receive(const PlayerEventFire &)
{
    if (m_events && !m_isServer)
    {
        NetworkPacketData packet;
        packet.type = NetworkPacketType::PlayerFire;

        m_events->emit(SendNetworkPacket{packet});
    }
}

void NetworkEventTranslator::receive(const PlayerEventMove &move)
{
    if (m_events && !m_isServer)
    {
        NetworkPacketData packet;
        packet.type = NetworkPacketType::PlayerMove;
        packet.amount = move.amount;

        m_events->emit(SendNetworkPacket{packet});
    }
}

void NetworkEventTranslator::receive(const PlayerEventTurn &turn)
{
    if (m_events && !m_isServer)
    {
        NetworkPacketData packet;
        packet.type = NetworkPacketType::PlayerTurn;
        packet.amount = turn.amount;
        m_events->emit(SendNetworkPacket{packet});
    }
}

void NetworkEventTranslator::receive(const PlayerEventPointTo &pointTo)
{
    if (m_events && !m_isServer)
    {
        NetworkPacketData packet;
        packet.type = NetworkPacketType::PlayerPointTo;
        packet.point = pointTo.pos;

        m_events->emit(SendNetworkPacket{packet});
    }
}
