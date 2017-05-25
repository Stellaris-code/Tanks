/*  src/gamestate.cpp GameState - Yann BOUCHER (yann) 05/11/2016
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
#include "gamestate.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <Thor/Resources/SfmlLoaders.hpp>

#include "systems/renderingsystem.hpp"
#include "systems/inputsystem.hpp"
#include "systems/inputtranslationsystem.hpp"
#include "systems/pawnmovementsystem.hpp"
#include "systems/turrethandlersystem.hpp"
#include "systems/projectilesystem.hpp"
#include "systems/collisionsystem.hpp"
#include "systems/tankcollisionhandler.hpp"
#include "systems/animationsystem.hpp"
#include "systems/gameplaysystem.hpp"
#include "systems/lifetimesystem.hpp"
#include "systems/networkmessagesendersystem.hpp"
#include "systems/networkmessagereceiversystem.hpp"

#include "components/drawable.hpp"
#include "components/pawn.hpp"
#include "components/childentities.hpp"
#include "components/tank.hpp"

#include "components/dependencies.hpp"

#include "events.hpp"

#include "utils.hpp"

GameState::GameState(Context &context)
    : m_context(context)
{
    events.subscribe<Quit>(*this);

    createResources();

    configureSystems();

    createEntities();
}

void GameState::update(const sf::Time &dt)
{
    systems.update_all(dt.asSeconds());
}

void GameState::receive(const Quit &)
{
    m_context.win.close();
}

void GameState::configureSystems()
{
    register_dependencies(systems);

    systems.add<RenderingSystem>(m_context.res, m_context.win, m_context.isRenderPass);
    systems.add<InputSystem>(m_context.win);
    systems.add<InputTranslationSystem>();

    systems.configure();
}

void GameState::createEntities()
{
    entityx::Entity bckg = entities.create();
    bckg.assign<Drawable>("background")->spriteSize = sf::Vector2f(m_context.win.getSize());

    if (m_context.networkoptions.isServer())
    {
        events.emit<SpawnTank>({sf::Vector2f{100, 100}, Player::One});
    }
    else
    {
        events.emit<SpawnTank>({sf::Vector2f{200, 200}, Player::Two});
    }
}

void GameState::createResources()
{
    m_context.res.textures.acquire("background", thor::Resources::fromFile<sf::Texture>("data/textures/light_sand_bckg.png")).setSmooth(true);
    m_context.res.textures.acquire("dirt", thor::Resources::fromFile<sf::Texture>("data/textures/dirt.png")).setRepeated(true);
    m_context.res.textures.acquire("medal", thor::Resources::fromFile<sf::Texture>("data/textures/medal.png")).setSmooth(true);
    m_context.res.textures.acquire("tank_green_full", thor::Resources::fromFile<sf::Texture>("data/textures/tankBase_green_full.png")).setSmooth(true);

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
}
