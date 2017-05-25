/*  boostgeometryinterop %{Cpp:License:ClassName} - Yann BOUCHER (yann) 26/11/2016
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
#ifndef BOOSTGEOMETRYINTEROP_HPP
#define BOOSTGEOMETRYINTEROP_HPP

#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>
#include <SFML/Graphics.hpp>
#include <boost/geometry/geometries/register/ring.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry.hpp>

BOOST_GEOMETRY_REGISTER_POINT_2D(sf::Vector2f, float, cs::cartesian, x, y)

class ShapeIterator : public boost::iterator_facade<ShapeIterator,
        sf::Vector2f const, boost::random_access_traversal_tag, sf::Vector2f> {
public:
    ShapeIterator(const sf::Shape* shape = nullptr, unsigned int index = 0):
        m_shape(shape), m_index(index)
    {

    }

private:
    friend class boost::iterator_core_access;

    void increment() {
        ++m_index;
    }

    void decrement() {
        --m_index;
    }

    sf::Vector2f dereference() const {
        return m_shape->getTransform().transformPoint(m_shape->getPoint(m_index));
    }

    bool equal(const ShapeIterator &other) const {
        return m_index == other.m_index;
    }

    void advance(int n) {
        m_index += n;
    }

    int distance_to(const ShapeIterator& other) const {
        return (other.m_index - static_cast<int>(m_index));
    }

    const sf::Shape* m_shape;
    unsigned int m_index;
};

inline auto points_of(const sf::Shape& shape)
{
    return boost::make_iterator_range(ShapeIterator(&shape), ShapeIterator(&shape, shape.getPointCount()));
}

using ShapePoints = decltype(points_of(sf::CircleShape()));

//register as ring

namespace boost {
namespace geometry {
namespace traits {
template<> struct tag<ShapePoints> { typedef ring_tag type; };
template<> struct closure<ShapePoints> { static const closure_selector value = open; };
}
}
}

#endif // BOOSTGEOMETRYINTEROP_HPP
