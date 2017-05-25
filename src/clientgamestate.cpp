/*  src/clientgamestate.cpp ClientGameState - Yann BOUCHER (yann) 13/11/2016
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
#include "clientgamestate.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <Thor/Resources/SfmlLoaders.hpp>

#include "systems/messagerenderingsystem.hpp"
#include "systems/inputsystem.hpp"
#include "systems/inputtranslationsystem.hpp"
#include "systems/scorepanelsystem.hpp"
#include "systems/networkmessagesendersystem.hpp"
#include "systems/networkmessagereceiversystem.hpp"
#include "systems/networkeventtranslator.hpp"

#include "components/drawable.hpp"
#include "components/pawn.hpp"
#include "components/childentities.hpp"
#include "components/tank.hpp"

#include "components/dependencies.hpp"

#include "events.hpp"

#include "utils.hpp"

ClientGameState::ClientGameState(Context &context)
    : m_context(context)
{
    events.subscribe<Quit>(*this);

    createResources();

    configureSystems();

    createEntities();
}

void ClientGameState::update(const sf::Time &dt)
{
    systems.update_all(dt.asSeconds());
}

void ClientGameState::receive(const Quit &)
{
    m_context.win.close();
}

void ClientGameState::configureSystems()
{
    register_dependencies(systems);

    systems.add<MessageRenderingSystem>(m_context.res, m_context.win, m_context.isRenderPass);
    systems.add<InputSystem>(m_context.win);
    systems.add<InputTranslationSystem>();
    systems.add<ScorePanelSystem>(Player::Two, m_context.win.getSize());

    systems.add<NetworkMessageReceiverSystem>(m_context.networkoptions);
    systems.add<NetworkMessageSenderSystem>(m_context.networkoptions, sf::milliseconds(0));
    systems.add<NetworkEventTranslator>(m_context.networkoptions.isServer());

    systems.configure();
}

void ClientGameState::createEntities()
{
}

void ClientGameState::createResources()
{
    m_context.res.fonts.acquire("cousine-bold", thor::Resources::fromFile<sf::Font>("data/fonts/Cousine-Bold-Zero.otf"));

    m_context.res.textures.acquire("background", thor::Resources::fromFile<sf::Texture>("data/textures/light_sand_bckg.png")).setSmooth(true);
    m_context.res.textures.acquire("dirt", thor::Resources::fromFile<sf::Texture>("data/textures/dirt.png")).setRepeated(true);
    m_context.res.textures.acquire("medal", thor::Resources::fromFile<sf::Texture>("data/textures/medal.png")).setSmooth(true);

    for (std::string color : {"blue", "black", "beige", "green", "red"})
    {
        m_context.res.textures.acquire("tank_base_" + color, thor::Resources::fromFile<sf::Texture>("data/textures/tankBase_" + color + ".png")).setSmooth(true);
        m_context.res.textures.acquire("turret_" + color, thor::Resources::fromFile<sf::Texture>("data/textures/tankTurret_" + color + ".png")).setSmooth(true);
    }

    for (size_t i { 0 }; i <= 118; ++i)
    {
        std::string num = to_string_pad_zeroes(i, 4);
        m_context.res.textures.acquire("explosion_" + num, thor::Resources::fromFile<sf::Texture>("data/textures/explosions/explosion" + num + ".png")).setSmooth(true);
    }

    m_context.res.textures.acquire("bullet", thor::Resources::fromFile<sf::Texture>("data/textures/bullet.png")).setSmooth(true);
    m_context.res.textures.acquire("lifebar_border", thor::Resources::fromFile<sf::Texture>("data/textures/lifebar_border.png")).setSmooth(true);
    m_context.res.textures.acquire("trail", thor::Resources::fromFile<sf::Texture>("data/textures/trail.png")).setSmooth(true);
    m_context.res.textures.acquire("blank", thor::Resources::fromFile<sf::Texture>("data/textures/blank.png")).setSmooth(true);

    for (size_t i { 1 }; i <= 4; ++i)
    {
        m_context.res.textures.acquire("flame_" + std::to_string(i), thor::Resources::fromFile<sf::Texture>("data/textures/flame" + std::to_string(i) + ".png")).setSmooth(true);
    }

    m_context.res.textures.acquire("crate", thor::Resources::fromFile<sf::Texture>("data/textures/crate.png")).setSmooth(true);
    m_context.res.textures.acquire("shield_powerup", thor::Resources::fromFile<sf::Texture>("data/textures/shield_powerup.png")).setSmooth(true);
    m_context.res.textures.acquire("tripleshoot_powerup", thor::Resources::fromFile<sf::Texture>("data/textures/tripleshoot_powerup.png")).setSmooth(true);
    m_context.res.textures.acquire("shield", thor::Resources::fromFile<sf::Texture>("data/textures/shield.png")).setSmooth(true);
}
