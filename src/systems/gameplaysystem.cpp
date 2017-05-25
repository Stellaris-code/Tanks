/*  src/systems/gameplaysystem.cpp GameplaySystem - Yann BOUCHER (yann) 09/11/2016
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
#include "systems/gameplaysystem.hpp"

#include <cmath>

#include <random>

#include <SFML/Graphics/RectangleShape.hpp>

#include "components/transform.hpp"
#include "components/pawn.hpp"
#include "components/drawable.hpp"
#include "components/hitbox.hpp"
#include "components/tank.hpp"
#include "components/turret.hpp"
#include "components/childentities.hpp"
#include "components/animation.hpp"
#include "components/ai.hpp"
#include "components/health.hpp"
#include "components/lifetime.hpp"
#include "components/powerup.hpp"

#include "utils.hpp"

void GameplaySystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    m_entityManager = &es;

    updateTimers(sf::seconds(dt));

    for (const auto& tankSpawn : m_tankSpawns)
    {
        spawnTank(tankSpawn.pos, tankSpawn.player, es);
    }

    for (const auto& crateSpawn : m_crateSpawns)
    {
        spawnCrate(crateSpawn.pos, es);
    }

    for (const auto& explosionSpawn : m_explosionSpawns)
    {
        spawnExplosion(explosionSpawn.pos, es);
    }

    for (const auto& powerupSpawn : m_powerupSpawns)
    {
        spawnRandomPowerup(events);
    }

    m_tankSpawns.clear();
    m_crateSpawns.clear();
    m_explosionSpawns.clear();
    m_powerupSpawns.clear();
}

void GameplaySystem::receive(const SpawnTank &tank)
{
    m_tankSpawns.push_back(tank);
}

void GameplaySystem::receive(const SpawnCrate &crate)
{
    m_crateSpawns.push_back(crate);
}

void GameplaySystem::receive(const SpawnExplosion &explosion)
{
    m_explosionSpawns.push_back(explosion);
}

void GameplaySystem::receive(const SpawnRandomCrates &crates)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> amountdist(5, 10);
    std::uniform_real_distribution<float> posx(0, m_screenSize.x);
    std::uniform_real_distribution<float> posy(0, m_screenSize.y);

    const size_t amount = amountdist(mt);

    for (size_t i { 0 }; i < amount; ++i)
    {
        m_crateSpawns.push_back(SpawnCrate{{posx(mt), posy(mt)}});
    }
}

void GameplaySystem::receive(const SpawnRandomPowerup &powerup)
{
    m_powerupSpawns.push_back(powerup);
}

void GameplaySystem::registerServices(entityx::EventManager &events)
{
    addService(sf::seconds(10), [this, &events]
    {
        if (m_entityManager)
        {
            size_t powerupAmount { 0 };
            powerupAmount = std::distance(m_entityManager->entities_with_components<Powerup>().begin(),
                                          m_entityManager->entities_with_components<Powerup>().end());

            if (powerupAmount < m_gameplayConstants.maxPowerups)
            {
                spawnRandomPowerup(events);
            }
        }
    });

    addService(sf::seconds(5), [this, &events]
    {
        if (m_entityManager)
        {
            size_t aiAmount { 0 };
            aiAmount = std::distance(m_entityManager->entities_with_components<Ai>().begin(),
                                     m_entityManager->entities_with_components<Ai>().end());

            if (aiAmount < m_gameplayConstants.maxAi)
            {
                std::random_device rd;
                std::mt19937 mt(rd());

                const double distance { 50 };

                std::uniform_real_distribution<float> posx(0, m_screenSize.x);
                std::uniform_real_distribution<float> posxin(-distance, 0);
                std::uniform_real_distribution<float> posxout(m_screenSize.x + distance, m_screenSize.x);

                std::uniform_real_distribution<float> posy(0, m_screenSize.y);
                std::uniform_real_distribution<float> posyin(-distance, 0);
                std::uniform_real_distribution<float> posyout(m_screenSize.y + distance, m_screenSize.y);

                std::bernoulli_distribution randBool(0.5);

                const bool x_side = randBool(mt);

                float x { 0 };
                float y { 0 };

                if (x_side)
                {
                    x = posx(mt);
                    y = randBool(mt) ? posyin(mt) : posyout(mt);
                }
                else
                {
                    x = randBool(mt) ? posxin(mt) : posxout(mt);
                    y = posy(mt);
                }

                events.emit<SpawnTank>({{x, y}, Player::AI});
            }
        }
    });
}

void GameplaySystem::spawnTank(const sf::Vector2f &pos, Player player, entityx::EntityManager &es)
{
    entityx::Entity tank = es.create();
    tank.assign<Transform>()->setPosition(pos);
    tank.assign<Pawn>(player);
    std::string color = "beige";
    if (player == Player::One)
    {
        color = "blue";
    }
    else if (player == Player::Two)
    {
        color = "red";
    }
    else if (player == Player::Three)
    {
        color = "green";
    }
    else if (player == Player::Four)
    {
        color = "black";
    }
    else
    {
        color = "beige";
    }
    tank.assign<Drawable>("tank_base_" + color, sf::Vector2f{0.5, 0.5})->zorder = 1;
    tank.assign<Hitbox>()->hitbox = std::make_unique<sf::RectangleShape>(sf::Vector2f{83, 78});
    tank.component<Hitbox>()->hitbox->setPosition({-83/2, -78/2});
    tank.component<Hitbox>()->hitbox->setOrigin({83/2, 78/2});
    tank.assign<Health>(100)->showHealth = true;
    tank.assign<Tank>();
    if (player == Player::AI)
    {
        tank.assign<Ai>();
        tank.component<Pawn>()->controller = (Player)(tank.component<Ai>()->id);
    }

    entityx::Entity turret = es.create();
    turret.assign<Transform>()->setPosition(tank.component<Transform>()->getPosition());
    turret.assign<Drawable>("turret_" + color, sf::Vector2f{0.5, 0})->zorder = 7; // on top of tank
    turret.assign<Turret>(sf::Vector2f{0, 30}, tank.component<Pawn>()->controller, sf::seconds(1))->coolDownProgress = sf::Time::Zero;

    tank.assign<ChildEntities>(std::vector<Child>{{turret, true, false}});
}

void GameplaySystem::spawnCrate(const sf::Vector2f &pos, entityx::EntityManager &es)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> rotdist(0, 180);
    std::uniform_real_distribution<float> posdist(40, 80);

    entityx::Entity crate = es.create();
    auto trans = crate.assign<Transform>();
    trans->setPosition(pos);
    trans->setRotation(rotdist(mt));

    auto sideSize = posdist(mt);

    sf::Vector2f spriteSize { sideSize, sideSize };

    crate.assign<Drawable>("crate", sf::Vector2f{0.5, 0.5})->spriteSize = spriteSize;
    crate.assign<Hitbox>()->hitbox = std::make_unique<sf::RectangleShape>(spriteSize);
    crate.component<Hitbox>()->hitbox->setPosition({-spriteSize.x/2, -spriteSize.y/2});
    crate.component<Hitbox>()->hitbox->setOrigin({spriteSize.x/2, spriteSize.y/2});
    crate.assign<Health>(50);

}

void GameplaySystem::spawnExplosion(const sf::Vector2f &pos, entityx::EntityManager &es)
{
    entityx::Entity expl = es.create();
    expl.assign<Transform>()->setPosition(pos);
    expl.assign<Drawable>("explosion_0000", sf::Vector2f{0.5, 0.5})->zorder = 10;
    expl.component<Drawable>()->spriteSize = {350, 350};

    std::vector<std::pair<sf::Time, AnimationKey>> anims;

    for (size_t i { 0 }; i <= 118; ++i)
    {
        std::string str = "explosion_" + to_string_pad_zeroes(i, 4);

        AnimationKey anim;
        anim.transform.setPosition(pos);
        anim.texId = str;

        anims.push_back(std::make_pair(i == 0 ? sf::Time::Zero : sf::seconds(0.025), anim));
    }

    expl.assign<Animation>(anims);

    expl.assign<Lifetime>(sf::seconds(3));
}

void GameplaySystem::spawnRandomPowerup(entityx::EventManager &events)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> amountdist(5, 10);
    std::uniform_real_distribution<float> posx(0, m_screenSize.x);
    std::uniform_real_distribution<float> posy(0, m_screenSize.y);
    std::uniform_int_distribution<unsigned> type(0, (unsigned)Powerup::Type::MAX-1);

    events.emit<SpawnPowerup>({sf::Vector2f{posx(mt), posy(mt)}, (Powerup::Type)type(mt)});
}
