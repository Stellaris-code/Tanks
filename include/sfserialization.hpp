/*  sfserialization %{Cpp:License:ClassName} - Yann BOUCHER (yann) 11/11/2016
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
#ifndef SFSERIALIZATION_HPP
#define SFSERIALIZATION_HPP

#include <boost/optional.hpp>

#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <SFML/Network/Packet.hpp>

inline sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& vec)
{
    return packet << vec.x << vec.y;
}

inline sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& vec)
{
    return packet >> vec.x >> vec.y;
}


inline sf::Packet& operator <<(sf::Packet& packet, const sf::Color& color)
{
    return packet << color.r << color.g << color.b << color.a;
}

inline sf::Packet& operator >>(sf::Packet& packet, sf::Color& color)
{
    return packet >> color.r >> color.g >> color.b >> color.a;
}


inline sf::Packet& operator <<(sf::Packet& packet, const sf::IntRect& rect)
{
    return packet << rect.width << rect.height << rect.left << rect.top;
}

inline sf::Packet& operator >>(sf::Packet& packet, sf::IntRect& rect)
{
    return packet >> rect.width >> rect.height >> rect.left >> rect.top;
}


template<class T>
sf::Packet& operator <<(sf::Packet& Packet, const std::vector<T>& A)
{
    Packet << sf::Uint64(A.size());
    for (int i=0;i<A.size();i++)
    {
        Packet << A[i];
    }
    return Packet;
}

template<class T>
sf::Packet& operator >>(sf::Packet& Packet, std::vector<T>& A)
{
    sf::Uint64 size;
    Packet >> size;
    A.reserve(size);
    for (int i=0;i<size;i++)
    {
        T temp;
        Packet >> temp;
        A.push_back(temp);
    }
    return Packet;
}

template <typename T>
inline sf::Packet& operator <<(sf::Packet& packet, const boost::optional<T>& opt)
{
    bool initialized = opt.is_initialized();
    packet << initialized;
    if (initialized)
    {
        packet << opt.value();
    }
    return packet;
}

template <typename T>
inline sf::Packet& operator >>(sf::Packet& packet, boost::optional<T>& opt)
{
    bool initialized { false };
    packet >> initialized;
    if (initialized)
    {
        T val;
        packet >> val;
        opt = val;
    }
    else
    {
        opt = boost::none;
    }
    return packet;
}

#endif // SFSERIALIZATION_HPP
