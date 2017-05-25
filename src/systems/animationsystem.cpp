/*  src/systems/animationsystem.cpp AnimationSystem - Yann BOUCHER (yann) 09/11/2016
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
#include "systems/animationsystem.hpp"

#include <Thor/Graphics/ColorGradient.hpp>

#include "components/animation.hpp"
#include "components/drawable.hpp"
#include "components/transform.hpp"

void AnimationSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Animation, Drawable, Transform>([dt](entityx::Entity, Animation& anim, Drawable& drawable, Transform& transform)
    {
        anim.progress += sf::seconds(dt);
        while (anim.progress >= anim.keys[anim.idx].first)
        {
            if (anim.idx < anim.keys.size())
            {
                if (!anim.keys[anim.idx].second.texId.empty())
                {
                    drawable.texId = anim.keys[anim.idx].second.texId;
                }

                if (anim.keys[anim.idx].second.callback)
                {
                    anim.keys[anim.idx].second.callback();
                }
            }

            anim.progress -= anim.keys[anim.idx].first;
            ++anim.idx;

            if (anim.idx >= anim.keys.size())
            {
                if (anim.loop)
                {
                    anim.progress -= anim.keys.back().first;
                    if (anim.progress.asMicroseconds() < 0)
                    {
                        anim.progress = sf::Time::Zero;
                    }
                    anim.idx = 0;
                }
                else
                {
                    return;
                }
            }
        }

        if (anim.idx == 0)
        {
            throw_no_zero_key_error("");
        }

        transform.setScale(lerp(anim.keys[anim.idx - 1].second.transform.getScale(),
                           anim.keys[anim.idx    ].second.transform.getScale(),
                anim.progress / anim.keys[anim.idx].first));

        transform.setPosition(lerp(anim.keys[anim.idx - 1].second.transform.getPosition(),
                              anim.keys[anim.idx    ].second.transform.getPosition(),
                anim.progress / anim.keys[anim.idx].first));

        transform.setRotation(lerp(anim.keys[anim.idx - 1].second.transform.getRotation(),
                              anim.keys[anim.idx    ].second.transform.getRotation(),
                anim.progress / anim.keys[anim.idx].first));

        drawable.color = thor::blendColors(anim.keys[anim.idx - 1].second.color,
                anim.keys[anim.idx].second.color,
                anim.progress / anim.keys[anim.idx].first);
    });
}
