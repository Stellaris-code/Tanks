/*  include/systems/soundsystem.hpp SoundSystem - Yann BOUCHER (yann) 17/12/2016
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
#ifndef SOUNDSYSTEM_HPP
#define SOUNDSYSTEM_HPP

#include <entityx/System.h>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "events.hpp"

#include "noncopyable.hpp"

#include "resources.hpp"

class SoundSystem :
        private Noncopyable,
        public entityx::System<SoundSystem>,
        public entityx::Receiver<SoundSystem>
{
    public:
        SoundSystem(const Resources& resources);

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<SpawnExplosion>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const SpawnExplosion& expl);

    private:
        void removeEndedSounds();

    private:
        const Resources& m_res;

        std::vector<sf::Sound> m_sounds;
};
#endif // SOUNDSYSTEM_HPP
