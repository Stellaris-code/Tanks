/*  src/systems/turrethandlersystem.cpp TurretHandlerSystem - Yann BOUCHER (yann) 06/11/2016
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
#include "systems/turrethandlersystem.hpp"

#include <random>

#include <SFML/Graphics/RectangleShape.hpp>

#include <Thor/Vectors/VectorAlgebra2D.hpp>

#include "events.hpp"

#include "components/turret.hpp"
#include "components/transform.hpp"
#include "components/drawable.hpp"
#include "components/bullet.hpp"
#include "components/pawn.hpp"
#include "components/tank.hpp"
#include "components/projectile.hpp"
#include "components/hitbox.hpp"
#include "components/lifetime.hpp"
#include "components/animation.hpp"
#include "components/ai.hpp"

#include "utils.hpp"

void TurretHandlerSystem::update(entityx::EntityManager &es, entityx::EventManager &events, entityx::TimeDelta dt)
{
    es.each<Turret, Transform>([this, &es, &events, dt](entityx::Entity ent, Turret& turret, Transform& transform)
    {
        for (const auto& pointTo : m_pointToEvents)
        {
            entityx::Entity instigator;

            es.each<Pawn, Tank>([&](entityx::Entity entity, Pawn& pawn, Tank&)
            {
                if (pointTo.player == pawn.controller)
                {
                    instigator = entity;
                }
            });

            if (pointTo.player == turret.player)
            {
                sf::Vector2f dir = pointTo.pos - transform.getPosition();
                if (dir == sf::Vector2f())
                {
                    dir = sf::Vector2f(1, 0);
                }
                dir = thor::unitVector(dir);
                thor::rotate(dir, 90.f);

                float angle = thor::polarAngle(dir) + 180;

                if (!nearlyEqual(transform.getRotation(), angle, 2.f))
                {
                    double delta = angle - transform.getRotation();

                    if (std::abs(delta) > std::abs(delta - 360))
                    {
                        delta = delta - 360;
                    }
                    else if (std::abs(delta) > std::abs(delta + 360))
                    {
                        delta = delta + 360;
                    }

                    transform.setRotation(transform.getRotation() + sgn(delta) * dt * turret.rotationSpeed);
                }
            }
        }

        turret.coolDownProgress += sf::seconds(dt);
        if (turret.coolDownProgress >= turret.coolDownTime)
        {
            events.emit<CanFire>({turret.player});
        }

        for (const auto& fire : m_fireEvents)
        {
            entityx::Entity instigator;

            es.each<Pawn, Tank>([&](entityx::Entity entity, Pawn& pawn, Tank&)
            {
                if (fire.player == pawn.controller)
                {
                    instigator = entity;
                }
            });

            if (fire.player == turret.player)
            {
                if (turret.coolDownProgress >= turret.coolDownTime)
                {
                    turret.coolDownProgress = sf::Time::Zero;

                    //                    entityx::Entity bullet = es.create();
                    //                    auto bulletTransform = bullet.assign<Transform>();
                    //                    bulletTransform->setPosition(thor::rotatedVector(turret.fireOffset, transform.getRotation()) + transform.getPosition());
                    //                    bulletTransform->setRotation(transform.getRotation());
                    //                    bullet.assign<Drawable>("bullet", sf::Vector2f{0.5, 0})->zorder = 5;

                    //                    bullet.assign<Projectile>(instigator.id(), 500);

                    //                    bullet.assign<Hitbox>()->hitbox = std::make_unique<sf::RectangleShape>(sf::Vector2f{20, 34});
                    //                    bullet.component<Hitbox>()->hitbox->setPosition({-20/2, -34/2});
                    //                    bullet.component<Hitbox>()->hitbox->setOrigin({20/2, 0});

                    //                    bullet.assign<Bullet>();
                    //                    bullet.assign<Lifetime>(sf::seconds(5));


                    //                    entityx::Entity flame = es.create();
                    //                    auto trans = flame.assign<Transform>();
                    //                    trans->setPosition(bullet.component<Transform>()->getPosition() - thor::rotatedVector({0, 10}, bullet.component<Transform>()->getRotation()));
                    //                    trans->setRotation(bullet.component<Transform>()->getRotation() + 180);

                    //                    std::random_device rd;
                    //                    std::mt19937 mt(rd());
                    //                    std::uniform_int_distribution<unsigned> dist(1, 4);

                    //                    flame.assign<Drawable>("flame_" + std::to_string(dist(mt)), sf::Vector2f{0.5, 1})->zorder = 15;

                    //                    AnimationKey key0;
                    //                    key0.transform = *trans.get();
                    //                    AnimationKey key1;
                    //                    key1.transform = *trans.get();
                    //                    key1.color = sf::Color(255, 255, 255, 0);

                    //                    flame.assign<Animation>(std::vector<std::pair<sf::Time, AnimationKey>>{{sf::seconds(0), key0}, {sf::seconds(0.15), key1}});
                    //                    flame.assign<Lifetime>(sf::seconds(0.5));

                    spawnBullet(es, instigator.id(), thor::rotatedVector(turret.fireOffset, transform.getRotation())
                                + transform.getPosition(), transform.getRotation());
                    if (turret.tripleShoot)
                    {
                        spawnBullet(es, instigator.id(), thor::rotatedVector(turret.fireOffset, transform.getRotation())
                                    + transform.getPosition(), transform.getRotation()+m_tripleShootSpread);
                        spawnBullet(es, instigator.id(), thor::rotatedVector(turret.fireOffset, transform.getRotation())
                                    + transform.getPosition(), transform.getRotation()-m_tripleShootSpread);
                    }
                }
            }
        }
    });
    m_fireEvents.clear();
    m_pointToEvents.clear();
}

void TurretHandlerSystem::receive(const PlayerEventPointTo &pointTo)
{
    m_pointToEvents.push_back(pointTo);
}

void TurretHandlerSystem::receive(const PlayerEventFire &fire)
{
    m_fireEvents.push_back(fire);
}

void TurretHandlerSystem::spawnBullet(entityx::EntityManager &es, const entityx::Entity::Id &instigator, const sf::Vector2f &pos, float angle)
{
    entityx::Entity bullet = es.create();
    auto bulletTransform = bullet.assign<Transform>();
    bulletTransform->setPosition(pos);
    bulletTransform->setRotation(angle);
    bullet.assign<Drawable>("bullet", sf::Vector2f{0.5, 0})->zorder = 5;

    bullet.assign<Projectile>(instigator, 500);

    bullet.assign<Hitbox>()->hitbox = std::make_unique<sf::RectangleShape>(sf::Vector2f{20, 34});
    bullet.component<Hitbox>()->hitbox->setPosition({-20/2, -34/2});
    bullet.component<Hitbox>()->hitbox->setOrigin({20/2, 0});

    bullet.assign<Bullet>();
    bullet.assign<Lifetime>(sf::seconds(5));


    entityx::Entity flame = es.create();
    auto trans = flame.assign<Transform>();
    trans->setPosition(bullet.component<Transform>()->getPosition() - thor::rotatedVector({0, 10}, bullet.component<Transform>()->getRotation()));
    trans->setRotation(bullet.component<Transform>()->getRotation() + 180);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<unsigned> dist(1, 4);

    flame.assign<Drawable>("flame_" + std::to_string(dist(mt)), sf::Vector2f{0.5, 1})->zorder = 15;

    AnimationKey key0;
    key0.transform = *trans.get();
    AnimationKey key1;
    key1.transform = *trans.get();
    key1.color = sf::Color(255, 255, 255, 0);

    flame.assign<Animation>(std::vector<std::pair<sf::Time, AnimationKey>>{{sf::seconds(0), key0}, {sf::seconds(0.15), key1}});
    flame.assign<Lifetime>(sf::seconds(0.5));
}
