/*  include/systems/animationsystem.hpp AnimationSystem - Yann BOUCHER (yann) 09/11/2016
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
#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP


#include <entityx/System.h>
#include <entityx/Event.h>

#include "noncopyable.hpp"

#include "events.hpp"

#include "utils.hpp"

DECLARE_EXCEPTION(no_zero_key, "No key at t0 !");

class AnimationSystem :
        private Noncopyable,
        public entityx::System<AnimationSystem>
{
    public:
        AnimationSystem()
        {}

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

    private:
};

#endif // ANIMATIONSYSTEM_HPP
