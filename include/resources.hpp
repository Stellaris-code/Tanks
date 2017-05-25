/*  resources %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>

#include <Thor/Resources/ResourceHolder.hpp>

#include <SFML/Audio/SoundBuffer.hpp>

namespace sf
{
class Texture;
class Font;
class SoundBuffer;
}

struct Resources
{
        thor::ResourceHolder<sf::Texture, std::string> textures;
        thor::ResourceHolder<sf::Font, std::string> fonts;
        thor::ResourceHolder<sf::SoundBuffer, std::string> sounds;
};

#endif // RESOURCES_HPP
