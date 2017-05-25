/*  src/systemsmessagerenderingsystem.cpp MessageRenderingSystem - Yann BOUCHER (yann) 13/11/2016
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
#include "systems/messagerenderingsystem.hpp"

#include <algorithm>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "components/drawable.hpp"
#include "components/transform.hpp"
#include "components/hitbox.hpp"

#include "events.hpp"

MessageRenderingSystem::MessageRenderingSystem(const Resources &resources, sf::RenderTarget &target, const bool& isRenderPass)
    : m_res(resources), m_renderTarget(target), m_isRenderPass(isRenderPass)
{

}

void MessageRenderingSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta)
{
    if (m_isRenderPass)
    {

        sf::Sprite sprite;

        std::vector<InternalDrawable> drawables;

        for (const auto& request : m_requests)
        {
            drawables.push_back(request);
        }

        // sort by z-order
        std::sort(drawables.begin(), drawables.end(), [](const InternalDrawable& lhs, const InternalDrawable& rhs)
        {
            return lhs.drawable.zorder < rhs.drawable.zorder;
        });

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

        m_requests.clear();

    }
}

void MessageRenderingSystem::receive(const RequestDraw &request)
{
    m_requests.clear();
    for (const auto& pair : request.drawables)
    {
        m_requests.push_back({pair.drawable, pair.transform.getTransform()});
    }
}

