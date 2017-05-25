/*  utils %{Cpp:License:ClassName} - Yann BOUCHER (yann) 05/11/2016
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
#ifndef UTILS_HPP
#define UTILS_HPP

#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iomanip>

#define DECLARE_EXCEPTION(name, prettyname)\
    class name##_error : public std::runtime_error \
{ \
    using std::runtime_error::runtime_error; \
    }; \
    \
    [[noreturn]] inline void throw_##name##_error(const std::string& t_why) \
{ \
    throw name##_error(#prettyname " error : " + t_why); \
    }


template <typename T>
inline std::string to_string_with_precision(const T& a_value, const int n = 6)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(n) << a_value;
    return out.str();
}

template <typename T>
inline std::string to_string_pad_zeroes(const T& value, const int n = 5)
{
    std::ostringstream out;
    out << std::setfill('0') << std::setw(n) << value;
    return out.str();
}

inline std::string strtolower(std::string str)
{
    std::transform(str.cbegin(), str.cend(), str.begin(), ::tolower);
    return str;
}

inline std::string strtoupper(std::string str)
{
    std::transform(str.cbegin(), str.cend(), str.begin(), ::toupper);
    return str;
}

template <typename T, typename I = double>
inline T lerp(T a, T b, I t)
{
    return (I(1) - t) * a + t * b;
}

template <typename T>
int sgn(T val)
{
    return (T(0) < val) - (val < T(0));
}

template <typename T>
bool nearlyEqual(T x, T y, T epsilon)
{
    return std::abs(x - y) < epsilon;
}

#endif // UTILS_HPP
