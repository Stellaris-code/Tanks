/*  src/application.cpp Application - Yann BOUCHER (yann) 03/11/2016
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
#include "application.hpp"

#include <boost/program_options.hpp>

#include <Thor/Resources/SfmlLoaders.hpp>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

Application::Application(int argc, char *argv[])
{
    if (parseCommandLine(argc, argv))
    {
        m_window.create({1200, 1000}, "Tanks", sf::Style::Close | sf::Style::Titlebar, sf::ContextSettings(0, 0, 4));

        m_window.setFramerateLimit(60);

        m_resources.fonts.acquire("cousine-reg", thor::Resources::fromFile<sf::Font>("data/fonts/Cousine-Regular.ttf"));

        m_statemachine.pushState(m_networkoptions.isServer() ? StateID::ServerGame : StateID::ClientGame);

        m_statisticsText.setFont(m_resources.fonts["cousine-reg"]);
        m_statisticsText.setFillColor(sf::Color::Black);
        m_statisticsText.setPosition(m_window.getSize().x - 5.f - m_statisticsText.getLocalBounds().width, 5.f);
        m_statisticsText.setCharacterSize(10);

        assert(!m_statemachine.empty());
    }
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (m_window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        m_isRenderPass = false;

        while (timeSinceLastUpdate > m_timePerFrame)
        {
            timeSinceLastUpdate -= m_timePerFrame;

            m_statemachine.top()->update(m_timePerFrame);

            if (m_statemachine.empty())
            {
                m_window.close();
                return;
            }
        }
        updateStats(elapsedTime);

        render();
    }
}

void Application::render()
{
    m_isRenderPass = true;
    m_statemachine.top()->update(sf::Time::Zero);
    m_window.draw(m_statisticsText);
    m_window.display();
}

void Application::updateStats(const sf::Time &dt)
{
    m_statisticsUpdateTime += dt;

    m_statisticsNumFrames += 1;
    if (m_statisticsUpdateTime >= sf::seconds(1.0f))
    {
        m_statisticsText.setString(
                    "Frames / Second = " + std::to_string(m_statisticsNumFrames)
                    + "\nTime / Update = " + std::to_string(
                        static_cast<std::size_t>
                        (m_statisticsUpdateTime.asMicroseconds()) / m_statisticsNumFrames)
                    + "us");
        m_statisticsText.setPosition(m_window.getSize().x - 5.f - m_statisticsText.getLocalBounds().width, 5.f);
        m_statisticsUpdateTime -= sf::seconds(1.0f);
        m_statisticsNumFrames = 0;
    }

    m_window.draw(m_statisticsText);
}

bool Application::parseCommandLine(int argc, char *argv[])
{
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("ip,i", po::value<std::string>()->default_value(""), "server address, or empty to create server")
            ("server-port,s", po::value<unsigned short>()->default_value(54000), "server port")
            ("client-port,c", po::value<unsigned short>()->default_value(54001), "client port")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return false;
    }

    if (vm.count("ip"))
    {
        m_networkoptions.address = sf::IpAddress(vm["ip"].as<std::string>());
    }

    if (vm.count("server-port"))
    {
        m_networkoptions.serverport = vm["server-port"].as<unsigned short>();
    }

    if (vm.count("client-port"))
    {
        m_networkoptions.clientport = vm["client-port"].as<unsigned short>();
    }

    return true;
}
