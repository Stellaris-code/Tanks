/*  networkpacket %{Cpp:License:ClassName} - Yann BOUCHER (yann) 12/11/2016
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
#ifndef NETWORKPACKET_HPP
#define NETWORKPACKET_HPP

#include <boost/optional.hpp>

#include <SFML/Network/Packet.hpp>

#include "components/drawable.hpp"
#include "components/transform.hpp"

#include "sfserialization.hpp"

enum NetworkPacketType : sf::Uint8
{
    Connect,
    Disconnect,
    RenderDrawable,
    PlayerFire,
    PlayerMove,
    PlayerTurn,
    PlayerPointTo
};

struct DrawableTransformable
{
    Drawable drawable;
    Transform transform;
};

inline sf::Packet& operator <<(sf::Packet& packet, const DrawableTransformable& drawable)
{
    return packet << drawable.drawable << drawable.transform;
}

inline sf::Packet& operator >>(sf::Packet& packet, DrawableTransformable& drawable)
{
    return packet >> drawable.drawable >> drawable.transform;
}

struct NetworkPacketData
{
    sf::Uint8 type;

    std::vector<DrawableTransformable> drawables;
    float amount;
    sf::Vector2f point;
    unsigned short port;
};

inline sf::Packet& operator <<(sf::Packet& packet, const NetworkPacketData& netpacket)
{
    return packet << netpacket.type << netpacket.drawables << netpacket.amount << netpacket.point << netpacket.port;
}

inline sf::Packet& operator >>(sf::Packet& packet, NetworkPacketData& netpacket)
{
    return packet >> netpacket.type >> netpacket.drawables >> netpacket.amount >> netpacket.point >> netpacket.port;
}

struct NetworkPacket
{
    std::vector<NetworkPacketData> packets;
};

inline sf::Packet& operator <<(sf::Packet& packet, const NetworkPacket& netpacket)
{
    return packet << netpacket.packets;
}

inline sf::Packet& operator >>(sf::Packet& packet, NetworkPacket& netpacket)
{
    return packet >> netpacket.packets;
}

#endif // NETWORKPACKET_HPP
