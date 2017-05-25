/*  include/callbacktimer.hpp CallbackTimer - Yann BOUCHER (yann) 03/12/2016
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
#ifndef CALLBACKTIMER_HPP
#define CALLBACKTIMER_HPP

#include <algorithm>
#include <functional>
#include <vector>

#include <SFML/System/Time.hpp>

class CallbackTimer
{
    public:
        CallbackTimer(const sf::Time& duration, const std::function<void()>& callback = []{}, bool oneShot = false)
        {
            setDuration(duration);
            setCallback(callback);
            setOneShot(oneShot);
        }

    public:
        void setCallback(const std::function<void()>& callback)
        {
            m_callback = callback;
        }

        void setDuration(const sf::Time& duration)
        {
            m_duration = duration;
        }

        void setOneShot(bool val)
        {
            m_oneShot = val;
        }

        void reset()
        {
            m_progress = sf::Time::Zero;
        }

        bool done() const
        {
            return m_done;
        }

        sf::Time remainingTime() const
        {
            return m_duration - m_progress;
        }

        void update(const sf::Time& dt)
        {
            if (!done())
            {
                m_progress += dt;
                if (m_progress >= m_duration)
                {
                    if (m_callback)
                    {
                        m_callback();
                    }
                    reset();
                    if (m_oneShot)
                    {
                        m_done = true;
                    }
                }
            }
        }

    private:
        sf::Time m_duration { sf::Time::Zero };
        sf::Time m_progress { sf::Time::Zero };
        bool m_oneShot { false };
        bool m_done { false };

        std::function<void()> m_callback;
};

class CallbackTimerService
{
    protected:
        void addService(sf::Time duration, const std::function<void()>& function, bool oneShot = false)
        {
            m_callbacks.emplace_back(duration, function, oneShot);
        }

        void updateTimers(sf::Time dt)
        {
            removeDoneCallbacks();

            for (auto& callback : m_callbacks)
            {
                callback.update(dt);
            }
        }

    private:
        void removeDoneCallbacks()
        {
            m_callbacks.erase(std::remove_if(m_callbacks.begin(), m_callbacks.end(), [](const CallbackTimer& timer)
            {
                return timer.done();
            }), m_callbacks.end());
        }

    private:
        std::vector<CallbackTimer> m_callbacks;
};

#endif // CALLBACKTIMER_HPP
