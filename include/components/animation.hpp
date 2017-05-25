/*  animation %{Cpp:License:ClassName} - Yann BOUCHER (yann) 09/11/2016
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
#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <utility>
#include <functional>
#include <vector>

#include <entityx/Entity.h>

#include <SFML/System/Time.hpp>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Color.hpp>

struct AnimationKey
{
        sf::Transformable transform;
        std::string texId = "";
        sf::Color color = sf::Color::White;
        std::function<void()> callback;
};

struct Animation : public entityx::Component<Animation>
{
        Animation() = default;
        explicit Animation(const std::vector<std::pair<sf::Time, AnimationKey>>& inKeys, bool inLoop = false,
                           const sf::Time& inProgress = sf::Time::Zero)
            : keys(inKeys), loop(inLoop), progress(inProgress)
        {}

        std::vector<std::pair<sf::Time, AnimationKey>> keys;
        bool loop { false };
        sf::Time progress = sf::Time::Zero;
        size_t idx { 0 };
};

#endif // ANIMATION_HPP
