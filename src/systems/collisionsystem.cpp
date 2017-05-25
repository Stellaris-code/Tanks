/*  src/systems/collisionsystem.cpp CollisionSystem - Yann BOUCHER (yann) 06/11/2016
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
#include "systems/collisionsystem.hpp"

#include <boost/geometry/algorithms/intersects.hpp>

#include "components/hitbox.hpp"
#include "components/transform.hpp"

#include "boostgeometryinterop.hpp"

#include <vector>
#include <boost/assign/std/vector.hpp>
#include <boost/geometry.hpp>
#include <boost/geometry/algorithms/area.hpp>
#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include "events.hpp"

void CollisionSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{

    es.each<Hitbox, Transform>([&es, &events](entityx::Entity ent, Hitbox& inHitbox, Transform& transform)
    {
        auto& hitbox = *inHitbox.hitbox;
        hitbox.setPosition(transform.getPosition());
        hitbox.setRotation(transform.getRotation());
        hitbox.setScale(transform.getScale());

        es.each<Hitbox, Transform>([ent, &events, &hitbox](entityx::Entity other, Hitbox& inOtherHitbox, Transform& otherTransform)
        {
            if (ent.id() != other.id())
            {
                auto& otherHitbox = *inOtherHitbox.hitbox;
                otherHitbox.setPosition(otherTransform.getPosition());
                otherHitbox.setRotation(otherTransform.getRotation());
                otherHitbox.setScale(otherTransform.getScale());

                using namespace boost::assign;
                typedef boost::geometry::model::d2::point_xy<float> point_xy;


                std::vector<point_xy> points;
                for (size_t i { 0 }; i < hitbox.getPointCount(); ++i)
                {
                    auto point = hitbox.getTransform().transformPoint(hitbox.getPoint(i));
                    points.push_back({point.x, point.y});
                }
                boost::geometry::model::polygon<point_xy> polygon;
                boost::geometry::assign_points(polygon, points);
                boost::geometry::correct(polygon);

                std::vector<point_xy> otherPoints;
                for (size_t i { 0 }; i < otherHitbox.getPointCount(); ++i)
                {
                    auto point = otherHitbox.getTransform().transformPoint(otherHitbox.getPoint(i));
                    otherPoints.push_back({point.x, point.y});
                }
                boost::geometry::model::polygon<point_xy> otherPolygon;
                boost::geometry::assign_points(otherPolygon, otherPoints);
                boost::geometry::correct(otherPolygon);

                if (boost::geometry::intersects(polygon, otherPolygon))
                {
                    events.emit<Collision>({ent.id(), other.id()});
                }
            }
        });
    });
}
