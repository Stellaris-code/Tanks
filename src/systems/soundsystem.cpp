/*  src/systems/soundsystem.cpp SoundSystem - Yann BOUCHER (yann) 17/12/2016
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
#include "systems/soundsystem.hpp"

#include <algorithm>

SoundSystem::SoundSystem(const Resources &resources)
    : m_res(resources)
{

}

void SoundSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
   // removeEndedSounds();
}

void SoundSystem::receive(const SpawnExplosion &expl)
{
    m_sounds.emplace_back(m_res.sounds["explosion"]);
    m_sounds.back().play();
}

void SoundSystem::removeEndedSounds()
{
    m_sounds.erase(std::remove_if(m_sounds.begin(), m_sounds.end(), [](const sf::Sound& snd)
    {
        return snd.getStatus() == sf::Sound::Stopped;
    }), m_sounds.end());
}
