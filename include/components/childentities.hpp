/*  childentities %{Cpp:License:ClassName} - Yann BOUCHER (yann) 06/11/2016
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
#ifndef CHILDENTITIES_HPP
#define CHILDENTITIES_HPP

#include <vector>

#include <entityx/Entity.h>

struct Child
{
        Child(entityx::Entity inEnt, bool pos = true, bool rot = true, bool scale = true)
            : ent(inEnt), inheritPos(pos), inheritRot(rot), inheritScale(scale)
        {}
        entityx::Entity ent;
        bool inheritPos { true };
        bool inheritRot { true };
        bool inheritScale { true };
};

struct ChildEntities : public entityx::Component<ChildEntities>
{
        explicit ChildEntities(const std::vector<Child>& vec)
            : entities(vec)
        {
        }
        std::vector<Child> entities;

        ~ChildEntities()
        {
            for (auto& child : entities)
            {
                child.ent.destroy();
            }
        }
};

#endif // CHILDENTITIES_HPP
