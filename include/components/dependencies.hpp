/*  dependencies %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef DEPENDENCIES_HPP
#define DEPENDENCIES_HPP

#include <entityx/System.h>
#include <entityx/deps/Dependencies.h>

#include "transform.hpp"
#include "projectile.hpp"
#include "pawn.hpp"
#include "tank.hpp"
#include "turret.hpp"
#include "hitbox.hpp"
#include "drawable.hpp"
#include "bullet.hpp"
#include "animation.hpp"
#include "ai.hpp"
#include "health.hpp"

void inline register_dependencies(entityx::SystemManager& manager)
{
    manager.add<entityx::deps::Dependency<Drawable, Transform>>();
    manager.add<entityx::deps::Dependency<Projectile, Transform>>();
    manager.add<entityx::deps::Dependency<Hitbox, Transform>>();
    manager.add<entityx::deps::Dependency<Pawn, Transform>>();
    manager.add<entityx::deps::Dependency<Tank, Pawn, Hitbox, Drawable, Health>>();
    manager.add<entityx::deps::Dependency<Ai, Pawn>>();
    manager.add<entityx::deps::Dependency<Bullet, Projectile, Hitbox, Drawable>>();
    manager.add<entityx::deps::Dependency<Turret, Drawable>>();
    manager.add<entityx::deps::Dependency<Animation, Drawable>>();
}

#endif // DEPENDENCIES_HPP
