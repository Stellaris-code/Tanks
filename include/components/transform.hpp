/*  transform %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <entityx/Entity.h>

#include <SFML/Graphics/Transformable.hpp>

#include "sfserialization.hpp"

struct Transform : public entityx::Component<Transform>, public sf::Transformable
{
};

inline sf::Packet& operator <<(sf::Packet& packet, const Transform& transform)
{
    return packet << transform.getPosition() << transform.getRotation() << transform.getScale();
}

inline sf::Packet& operator >>(sf::Packet& packet, Transform& transform)
{
    sf::Vector2f pos;
    float rot;
    sf::Vector2f scale;
    packet >> pos >> rot >> scale;
    transform.setPosition(pos);
    transform.setRotation(rot);
    transform.setScale(scale);

    return packet;
}

#endif // TRANSFORM_HPP
