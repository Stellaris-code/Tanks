/*  src/systems/inputtranslationsystem.cpp InputTranslationSystem - Yann BOUCHER (yann) 05/11/2016
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
#include "systems/inputtranslationsystem.hpp"

#include "player.hpp"

void InputTranslationSystem::receive(const KeyPressed &mess)
{
    if (events)
    {
        if (mess.code == sf::Keyboard::Space)
        {
            events->emit<PlayerEventFire>({Player::One});
        }
    }
}

void InputTranslationSystem::receive(const KeyHeld &mess)
{
    if (events)
    {
        if (mess.code == sf::Keyboard::Up)
        {
            events->emit<PlayerEventMove>({Player::One, 1});
        }
        else if (mess.code == sf::Keyboard::Down)
        {
            events->emit<PlayerEventMove>({Player::One, -1});
        }
        else if (mess.code == sf::Keyboard::Right)
        {
            events->emit<PlayerEventTurn>({Player::One, 1});
        }
        else if (mess.code == sf::Keyboard::Left)
        {
            events->emit<PlayerEventTurn>({Player::One, -1});
        }


        if (mess.code == sf::Keyboard::Z)
        {
            events->emit<PlayerEventMove>({Player::Two, 1});
        }
        else if (mess.code == sf::Keyboard::S)
        {
            events->emit<PlayerEventMove>({Player::Two, -1});
        }
        else if (mess.code == sf::Keyboard::Q)
        {
            events->emit<PlayerEventTurn>({Player::Two, 1});
        }
        else if (mess.code == sf::Keyboard::D)
        {
            events->emit<PlayerEventTurn>({Player::Two, -1});
        }
    }
}

void InputTranslationSystem::receive(const MousePos &mess)
{
    if (events)
    {
        events->emit<PlayerEventPointTo>({Player::One, sf::Vector2f(mess.pos)});
    }
}

void InputTranslationSystem::receive(const MouseClick &)
{
    if (events)
    {
        events->emit<PlayerEventFire>({Player::One});
    }
}
