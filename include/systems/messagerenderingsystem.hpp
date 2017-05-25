/*  include/systems/messagerenderingsystem.hpp MessageRenderingSystem - Yann BOUCHER (yann) 13/11/2016
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
#ifndef MESSAGERENDERINGSYSTEM_HPP
#define MESSAGERENDERINGSYSTEM_HPP

#include <entityx/System.h>
#include <entityx/Event.h>

#include "events.hpp"

#include "noncopyable.hpp"

#include "resources.hpp"

namespace sf
{
class RenderTarget;
}

class MessageRenderingSystem :
        private Noncopyable,
        public entityx::System<MessageRenderingSystem>,
        public entityx::Receiver<MessageRenderingSystem>
{
    public:
        MessageRenderingSystem(const Resources& resources, sf::RenderTarget& target, const bool& isRenderPass);

    public:
        virtual void configure(entityx::EventManager &event_manager) override
        {
            event_manager.subscribe<RequestDraw>(*this);
        }

        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

        void receive(const RequestDraw& request);

    private:
        struct InternalDrawable
        {
                Drawable drawable;
                sf::Transform transform;
        };

    private:
        const Resources& m_res;
        sf::RenderTarget& m_renderTarget;
        const bool& m_isRenderPass;

        std::vector<InternalDrawable> m_requests;
};

#endif // MESSAGERENDERINGSYSTEM_HPP
