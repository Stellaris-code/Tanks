/*  events %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "entityx/Entity.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <SFML/System/Vector2.hpp>

#include <SFML/Network/IpAddress.hpp>

#include "components/drawable.hpp"
#include "components/transform.hpp"
#include "components/powerup.hpp"

#include "networkpacket.hpp"

#include "player.hpp"


///////////// Window events

struct Quit
{
};

struct Resize
{
        sf::Vector2u size;
};

struct MouseClick
{
        sf::Mouse::Button button;
        sf::Vector2i pos;
};

struct MouseRelease
{
        sf::Mouse::Button button;
        sf::Vector2i pos;
};

struct MouseMove
{
        sf::Vector2i pos;
};

struct MousePos
{
        sf::Vector2i pos;
};

struct KeyPressed
{
        sf::Keyboard::Key code;
};

struct KeyReleased
{
        sf::Keyboard::Key code;
};

struct KeyHeld
{
        sf::Keyboard::Key code;
};



///////////////// Gameplay events

struct ProjectileOutsideBounds
{
        entityx::Entity::Id id;
};

struct Collision
{
        entityx::Entity::Id lhs;
        entityx::Entity::Id rhs;
};

struct PawnDestroyed
{
        Player pawn;
        entityx::Entity::Id instigator;
};

struct SpawnTank
{
        sf::Vector2f pos;
        Player player;
};

struct SpawnCrate
{
        sf::Vector2f pos;
};

struct SpawnRandomCrates
{

};

struct SpawnRandomPowerup
{

};

struct SpawnExplosion
{
        sf::Vector2f pos;
};

struct SpawnPowerup
{
        sf::Vector2f pos;
        Powerup::Type type;
};

struct CreateShield
{
        Player player;
};

struct EnableTripleShoot
{
        Player player;
};

struct CanFire
{
        Player player;
};

struct PlayerEventFire
{
        Player player;
};

struct PlayerEventMove
{
        Player player;
        double amount { 0 };
};

struct PlayerEventTurn
{
        Player player;
        double amount { 0 };
};

struct PlayerEventPointTo
{
        Player player;
        sf::Vector2f pos;
};

struct PawnDeletionRequest
{
        Player player;
};

struct NetworkPlayerEventFire
{
        sf::IpAddress ip;
};

struct NetworkPlayerEventMove
{
        sf::IpAddress ip;
        double amount { 0 };
};

struct NetworkPlayerEventTurn
{
        sf::IpAddress ip;
        double amount { 0 };
};

struct NetworkPlayerEventPointTo
{
        sf::IpAddress ip;
        sf::Vector2f pos;
};

struct SendNetworkPacket
{
        NetworkPacketData packet;
};

struct RequestDraw
{
        std::vector<DrawableTransformable> drawables;
};

struct NewConnection
{
        sf::IpAddress ip;
};

struct ConnectionEnded
{
        sf::IpAddress ip;
};


#endif // EVENTS_HPP
