/*  include/systems/renderingsystem.hpp RenderingSystem - Yann BOUCHER (yann) 05/11/2016
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
#ifndef RENDERINGSYSTEM_HPP
#define RENDERINGSYSTEM_HPP

#include <entityx/System.h>

#include "events.hpp"

#include "noncopyable.hpp"

#include "resources.hpp"

namespace sf
{
class RenderTarget;
}

class RenderingSystem :
        private Noncopyable,
        public entityx::System<RenderingSystem>
{
    public:
        RenderingSystem(const Resources& resources, sf::RenderTarget& target, const bool& isRenderPass);

    public:
        virtual void update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt) override;

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
};

#endif // RENDERINGSYSTEM_HPP
