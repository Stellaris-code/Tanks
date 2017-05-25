/*  drawable %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <string>

#include <boost/optional.hpp>

#include <entityx/Entity.h>

#include <SFML/System/Vector2.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>

#include <SFML/Network/Packet.hpp>

#include "sfserialization.hpp"

struct Text
{
        sf::String text;
        unsigned int size { 12 };
        float outlinethickness { 0 };
        sf::Color outlinecolor { sf::Color::White };
        sf::Color fillcolor { sf::Color::White };
        unsigned int style { sf::Text::Style::Regular };
};

struct Drawable : public entityx::Component<Drawable>
{
        Drawable() = default;
        explicit Drawable(const std::string& id, const sf::Vector2f inOrigin = {0, 0})
            : texId(id), origin(inOrigin)
        {}

        std::string texId;
        sf::IntRect texRect { sf::IntRect{} };
        sf::Vector2f origin { 0, 0 }; // in normalized coordinates
        sf::Color color { sf::Color::White };
        int zorder { 0 };
        sf::Vector2f spriteSize { 0, 0 };

        bool visible { true };

        boost::optional<Text> text { boost::none };
};

inline sf::Packet& operator <<(sf::Packet& packet, const Text& text)
{
    return packet << text.text << text.size << text.outlinethickness << text.outlinecolor << text.fillcolor << text.style;
}

inline sf::Packet& operator >>(sf::Packet& packet, Text& text)
{
    return packet >> text.text >> text.size >> text.outlinethickness >> text.outlinecolor >> text.fillcolor >> text.style;
}

inline sf::Packet& operator <<(sf::Packet& packet, const Drawable& drawable)
{
    return packet << drawable.texId << drawable.texRect << drawable.origin <<
                     drawable.color << drawable.zorder << drawable.spriteSize <<
                     drawable.visible << drawable.text;
}

inline sf::Packet& operator >>(sf::Packet& packet, Drawable& drawable)
{
    return packet >> drawable.texId >> drawable.texRect >> drawable.origin >>
                     drawable.color >> drawable.zorder >> drawable.spriteSize >>
                     drawable.visible >> drawable.text;
}

#endif // DRAWABLE_HPP
