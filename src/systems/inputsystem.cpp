/*  src/systems/inputsystem.cpp InputSystem - Yann BOUCHER (yann) 05/11/2016
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
#include "systems/inputsystem.hpp"

#include <SFML/Window/Window.hpp>
#include <SFML/Window/Event.hpp>

#include "events.hpp"

InputSystem::InputSystem(sf::Window &win)
    : m_win(win)
{

}

void InputSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    sf::Event event;
    while(m_win.pollEvent(event) && m_win.hasFocus())
    {
        if(event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                events.emit<Quit>();
            }

            events.emit<KeyPressed>({event.key.code});
        }
        else if(event.type == sf::Event::Closed)
        {
            events.emit<Quit>();
        }
        else if(event.type == sf::Event::Resized)
        {
            events.emit<Resize>({sf::Vector2u{event.size.width, event.size.height}});
        }
        else if(event.type == sf::Event::MouseButtonPressed)
        {
            events.emit<MouseClick>({event.mouseButton.button, sf::Vector2i{event.mouseButton.x, event.mouseButton.y}});
        }
        else if(event.type == sf::Event::MouseButtonReleased)
        {
            events.emit<MouseRelease>({event.mouseButton.button, sf::Vector2i{event.mouseButton.x, event.mouseButton.y}});
        }
        else if(event.type == sf::Event::MouseMoved)
        {
            events.emit<MouseMove>({sf::Vector2i{event.mouseMove.x, event.mouseMove.y}});
        }
    }

    for (int32_t i { sf::Keyboard::A }; i < sf::Keyboard::KeyCount; ++i)
    {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(i)) && m_win.hasFocus())
        {
            events.emit<KeyHeld>({static_cast<sf::Keyboard::Key>(i)});
        }
    }

    events.emit<MousePos>({sf::Mouse::getPosition(m_win)});
}
