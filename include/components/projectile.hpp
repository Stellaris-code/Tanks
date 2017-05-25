/*  projectile %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <entityx/Entity.h>

struct Projectile : public entityx::Component<Projectile>
{
        Projectile() = default;
        Projectile(entityx::Entity::Id inInstigator, double inSpeed = 0, double inDamage = 40)
            : speed(inSpeed), instigator(inInstigator), damage(inDamage)
        {}
        double speed { 0 };
        double damage { 40 };
        entityx::Entity::Id instigator;
};

#endif // PROJECTILE_HPP
