/*  noncopyable %{Cpp:License:ClassName} - Yann BOUCHER (yann) 03/11/2016
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
#ifndef NONCOPYABLE_HPP
#define NONCOPYABLE_HPP

class Noncopyable
{
    protected:
        constexpr Noncopyable() = default;
        ~Noncopyable() = default;
        Noncopyable( const Noncopyable& ) = delete;
        Noncopyable& operator=( const Noncopyable& ) = delete;
};

#endif // NONCOPYABLE_HPP