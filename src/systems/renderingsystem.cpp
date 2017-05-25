/*  src/systems/renderingsystem.cpp RenderingSystem - Yann BOUCHER (yann) 05/11/2016
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
#include "systems/renderingsystem.hpp"

#include <algorithm>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "components/drawable.hpp"
#include "components/transform.hpp"
#include "components/hitbox.hpp"

#include "events.hpp"

RenderingSystem::RenderingSystem(const Resources &resources, sf::RenderTarget &target, const bool& isRenderPass)
    : m_res(resources), m_renderTarget(target), m_isRenderPass(isRenderPass)
{

}

void RenderingSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta)
{
    if (m_isRenderPass)
    {
        m_renderTarget.clear(sf::Color::Black);

        sf::Sprite sprite;

        std::vector<InternalDrawable> drawables;
        std::vector<DrawableTransformable> packetDrawables;

        es.each<Drawable, Transform>([&drawables, &packetDrawables, &events, this]
                                     (entityx::Entity, Drawable& drawable, Transform& trans)
        {
            if (drawable.visible)
            {
                packetDrawables.emplace_back(DrawableTransformable{drawable, trans});
                drawables.emplace_back(InternalDrawable{drawable, trans.getTransform()});
            }
        });

        // sort by z-order
        std::sort(drawables.begin(), drawables.end(), [](const InternalDrawable& lhs, const InternalDrawable& rhs)
        {
            return lhs.drawable.zorder < rhs.drawable.zorder;
        });

        events.emit(RequestDraw{packetDrawables});

        for (const auto& drawable : drawables)
        {
            if (drawable.drawable.text == boost::none) // is texture
            {
                if (!drawable.drawable.texId.empty())
                {
                    sprite.setTexture(m_res.textures[drawable.drawable.texId], true); // reset rect each time
                }
                else
                {
                    sprite.setTexture(m_res.textures["blank"], true); // reset rect each time
                }
                if (drawable.drawable.texRect != sf::IntRect())
                {
                    sprite.setTextureRect(drawable.drawable.texRect);
                }
                sprite.setColor(drawable.drawable.color);
                sprite.setOrigin(drawable.drawable.origin.x * sprite.getLocalBounds().width,
                                 drawable.drawable.origin.y * sprite.getLocalBounds().height);

                if (drawable.drawable.spriteSize != sf::Vector2f{0, 0})
                {
                    sprite.setScale(drawable.drawable.spriteSize.x / sprite.getLocalBounds().width,
                                    drawable.drawable.spriteSize.y / sprite.getLocalBounds().height);
                }
                else
                {
                    sprite.setScale(1, 1);
                }

                m_renderTarget.draw(sprite, drawable.transform);
            }
            else // is text
            {
                sf::Text text;
                text.setFont(m_res.fonts["cousine-bold"]);
                text.setCharacterSize(drawable.drawable.text->size);
                text.setOutlineThickness(drawable.drawable.text->outlinethickness);
                text.setOutlineColor(drawable.drawable.text->outlinecolor);
                text.setFillColor(drawable.drawable.text->fillcolor);
                text.setStyle(drawable.drawable.text->style);
                text.setString(drawable.drawable.text->text);
                text.setOrigin(drawable.drawable.origin.x * text.getLocalBounds().width,
                               drawable.drawable.origin.y * text.getLocalBounds().height);

                m_renderTarget.draw(text, drawable.transform);
            }
        }

    }
}
