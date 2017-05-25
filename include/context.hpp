/*  context %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <SFML/Network/IpAddress.hpp>

#include "resources.hpp"

namespace sf
{
class RenderWindow;
}

struct NetworkOptions
{
        sf::IpAddress address = sf::IpAddress::None;
        unsigned short serverport { 0 };
        unsigned short clientport { 0 };
        bool isServer() const
        {
            return address == sf::IpAddress::None;
        }
        unsigned short receivePort() const
        {
            return isServer() ? serverport : clientport;
        }
        unsigned short sendPort() const
        {
            return !isServer() ? serverport : clientport;
        }
};

struct Context
{
        Resources& res;
        sf::RenderWindow& win;
        const bool& isRenderPass;
        NetworkOptions& networkoptions;
};

#endif // CONTEXT_HPP
