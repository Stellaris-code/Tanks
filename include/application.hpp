/*  include/application.hpp Application - Yann BOUCHER (yann) 03/11/2016
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
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <string>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "statemachine.hpp"
#include "context.hpp"

#include "noncopyable.hpp"

class Application :
        private Noncopyable
{
    public:
        Application(int argc, char* argv[]);

    public:
        void run();

    private:

        void render();

        void updateStats(const sf::Time& dt);

        bool parseCommandLine(int argc, char *argv[]);

    private:
        sf::RenderWindow m_window;
        Resources m_resources;
        bool m_isRenderPass { false };

        NetworkOptions m_networkoptions;

        Context m_contextObject { m_resources, m_window, m_isRenderPass, m_networkoptions };

        StateMachine m_statemachine { m_contextObject };

        sf::Time m_timePerFrame { sf::seconds(1/60.f) };

        sf::Text m_statisticsText {};
        sf::Time m_statisticsUpdateTime {};
        std::size_t m_statisticsNumFrames { 0 };
};

#endif // APPLICATION_HPP
