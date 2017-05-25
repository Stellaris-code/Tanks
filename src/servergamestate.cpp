/*  src/servergamestate.cpp ServerGameState - Yann BOUCHER (yann) 13/11/2016
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
#include "servergamestate.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <Thor/Resources/SfmlLoaders.hpp>

#include "systems/renderingsystem.hpp"
#include "systems/inputsystem.hpp"
#include "systems/inputtranslationsystem.hpp"
#include "systems/pawnmovementsystem.hpp"
#include "systems/turrethandlersystem.hpp"
#include "systems/projectilesystem.hpp"
#include "systems/collisionsystem.hpp"
#include "systems/projectilecollisionhandler.hpp"
#include "systems/animationsystem.hpp"
#include "systems/gameplaysystem.hpp"
#include "systems/lifetimesystem.hpp"
#include "systems/pawndeletersystem.hpp"
#include "systems/networkmessagesendersystem.hpp"
#include "systems/networkmessagereceiversystem.hpp"
#include "systems/networkeventtranslator.hpp"
#include "systems/networkinputhandler.hpp"
#include "systems/aicontrollersystem.hpp"
#include "systems/healthsystem.hpp"
#include "systems/lifebarsystem.hpp"
#include "systems/tanktrailsystem.hpp"
#include "systems/pawnnamesystem.hpp"
#include "systems/powerupsystem.hpp"
#include "systems/shieldsystem.hpp"
#include "systems/tripleshootsystem.hpp"
#include "systems/scorepanelsystem.hpp"
#include "systems/soundsystem.hpp"

#include "components/drawable.hpp"
#include "components/pawn.hpp"
#include "components/childentities.hpp"
#include "components/tank.hpp"

#include "components/dependencies.hpp"

#include "events.hpp"

#include "utils.hpp"

ServerGameState::ServerGameState(Context &context)
    : m_context(context)
{
    events.subscribe<Quit>(*this);

    createResources();

    configureSystems();

    createEntities();
}

void ServerGameState::update(const sf::Time &dt)
{
    systems.update_all(dt.asSeconds());
}

void ServerGameState::receive(const Quit &)
{
    m_context.win.close();
}

void ServerGameState::configureSystems()
{
    register_dependencies(systems);

    systems.add<RenderingSystem>(m_context.res, m_context.win, m_context.isRenderPass);
    systems.add<InputSystem>(m_context.win);
    systems.add<InputTranslationSystem>();
    systems.add<PawnMovementSystem>();
    systems.add<TurretHandlerSystem>();
    systems.add<ProjectileSystem>(m_context.win.getSize());
    systems.add<CollisionSystem>();
    systems.add<ProjectileCollisionHandler>();
    systems.add<AnimationSystem>();
    systems.add<GameplaySystem>(m_context.win.getSize());
    systems.add<LifetimeSystem>();
    systems.add<PawnDeleterSystem>();
    systems.add<HealthSystem>();
    systems.add<TankTrailSystem>();
    systems.add<LifebarSystem>();
    systems.add<PawnNameSystem>();
    systems.add<PowerupSystem>();
    systems.add<ShieldSystem>();
    systems.add<TripleShootSystem>();
    systems.add<ScorePanelSystem>(Player::One, m_context.win.getSize());
    systems.add<SoundSystem>(m_context.res);

    systems.add<NetworkMessageReceiverSystem>(m_context.networkoptions);
    systems.add<NetworkMessageSenderSystem>(m_context.networkoptions);
    systems.add<NetworkEventTranslator>(m_context.networkoptions.isServer());
    systems.add<NetworkInputHandler>();

    systems.add<AiControllerSystem>(m_context.win.getSize());

    systems.configure();
}

void ServerGameState::createEntities()
{
    entityx::Entity bckg = entities.create();
    bckg.assign<Drawable>("background")->spriteSize = sf::Vector2f(m_context.win.getSize());
    bckg.component<Drawable>()->zorder = -100;

    // events.emit<SpawnTank>({sf::Vector2f{500, 500}, Player::AI});
    //            events.emit<SpawnTank>({sf::Vector2f{500, 300}, Player::AI});
    events.emit<SpawnRandomCrates>();
    //events.emit<SpawnRandomPowerup>();
    //    events.emit<SpawnPowerup>({sf::Vector2f{200, 250}, Powerup::Type::TripleShoot});
    //    events.emit<SpawnPowerup>({sf::Vector2f{250, 250}, Powerup::Type::Shield});
    if (m_context.networkoptions.isServer())
    {
        events.emit<SpawnTank>({sf::Vector2f{100, 100}, Player::One});
    }
    else
    {
        events.emit<SpawnTank>({sf::Vector2f{200, 200}, Player::Two});
    }
}

void ServerGameState::createResources()
{
    m_context.res.fonts.acquire("cousine-bold", thor::Resources::fromFile<sf::Font>("data/fonts/Cousine-Bold-Zero.otf"));

    m_context.res.sounds.acquire("explosion", thor::Resources::fromFile<sf::SoundBuffer>("data/sounds/explosion.wav"));

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
