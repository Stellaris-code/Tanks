/*  src/systems/networkinputhandler.cpp NetworkInputHandler - Yann BOUCHER (yann) 13/11/2016
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
#include "systems/networkinputhandler.hpp"


void NetworkInputHandler::receive(const NewConnection &co)
{
    if (m_clients.size() < 3) // no more than 3 clients !!!
    {
        m_clients[co.ip] = Player(Player::Two + m_clients.size());

        if (m_events)
        {
            m_events->emit<SpawnTank>({sf::Vector2f{200, 200}, m_clients[co.ip]});
        }
    }
    else
    {
        std::cerr << "Attemption to connect on full server ! (address : " << co.ip.toString() << ")\n";
    }
}

void NetworkInputHandler::receive(const ConnectionEnded &co)
{
    if (m_events && m_clients.count(co.ip) > 0)
    {
        m_events->emit<PawnDeletionRequest>({m_clients.at(co.ip)});
    }

    m_clients.erase(co.ip);
}

void NetworkInputHandler::receive(const NetworkPlayerEventFire &fire)
{
    if (m_events && m_clients.count(fire.ip) > 0)
    {
        m_events->emit<PlayerEventFire>({m_clients.at(fire.ip)});
    }
}

void NetworkInputHandler::receive(const NetworkPlayerEventMove &move)
{
    if (m_events && m_clients.count(move.ip) > 0)
    {
        m_events->emit<PlayerEventMove>({m_clients.at(move.ip), move.amount});
    }
}

void NetworkInputHandler::receive(const NetworkPlayerEventTurn &turn)
{
    if (m_events && m_clients.count(turn.ip) > 0)
    {
        m_events->emit<PlayerEventTurn>({m_clients.at(turn.ip), turn.amount});
    }
}

void NetworkInputHandler::receive(const NetworkPlayerEventPointTo &pointTo)
{
    if (m_events && m_clients.count(pointTo.ip) > 0)
    {
        m_events->emit<PlayerEventPointTo>({m_clients.at(pointTo.ip), pointTo.pos});
    }
}
