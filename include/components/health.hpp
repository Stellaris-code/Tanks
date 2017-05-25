/*  health %{Cpp:License:ClassName} - Yann BOUCHER (yann) 20/11/2016
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
#ifndef HEALTH_HPP
#define HEALTH_HPP

#include <entityx/Entity.h>

struct Health : public entityx::Component<Health>
{
        Health() = default;
        explicit Health(double val)
            : maxHealth(val), health(maxHealth)
        {}

        double maxHealth { 100 };
        double health { maxHealth };

        bool showHealth { false };

        bool hasShield { false };

        entityx::Entity::Id lastDamageInstigator { entityx::Entity::INVALID };

        void setHealth(double val)
        {
            if (val > maxHealth)
            {
                val = maxHealth;
            }
            if (val < 0)
            {
                val = 0;
            }

            health = val;
        }

        void setMaxHealth(double val)
        {
            if (val < 0)
            {
                val = 0;
            }

            maxHealth = val;

            if (health > maxHealth)
            {
                health = maxHealth;
            }
        }

        void takeDamage(double val, entityx::Entity::Id instigator = entityx::Entity::INVALID)
        {
            lastDamageInstigator = instigator;
            setHealth(health - (hasShield ? val / 3.f : val));
        }

        bool dead() const
        {
            return health <= 0;
        }
};

#endif // HEALTH_HPP
