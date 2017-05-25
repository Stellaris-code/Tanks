/*  include/systems/inputtranslationsystem.hpp InputTranslationSystem - Yann BOUCHER (yann) 05/11/2016
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
#ifndef INPUTTRANSLATIONSYSTEM_HPP
#define INPUTTRANSLATIONSYSTEM_HPP

#include <entityx/System.h>
#include <entityx/Event.h>

#include <SFML/System/Time.hpp>

#include "noncopyable.hpp"

#include "events.hpp"

namespace sf
{
class Window;
}

class InputTranslationSystem :
        private Noncopyable,
        public entityx::System<InputTranslationSystem>,
        public entityx::Receiver<InputTranslationSystem>
{
    public:
        InputTranslationSystem() = default;

    public:
        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override
        {

        }

        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<KeyPressed>(*this);
            event_manager.subscribe<KeyHeld>(*this);
            event_manager.subscribe<MousePos>(*this);
            event_manager.subscribe<MouseClick>(*this);

            events = &event_manager;
        }

        void receive(const KeyPressed& mess);
        void receive(const KeyHeld& mess);
        void receive(const MousePos &mess);
        void receive(const MouseClick& mess);

    private:
        entityx::EventManager* events { nullptr };
};

#endif // INPUTTRANSLATIONSYSTEM_HPP
