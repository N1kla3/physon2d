#include <chrono>
#include <iostream>
#include "ContactsResolver.h"
#include "ForceGenerators.h"
#include "Particle.h"
#include "ParticleContact.h"
#include "raylib.h"

int main()
{
    InitWindow(1000, 1000, "PhysExample");
    SetTargetFPS(120);

    phys2::ContactsResolver resolver(3);
    phys2::Particle part1;
    part1.setMass(1.f);
    phys2::Particle part2;
    part2.setMass(1.f);

    phys2::ParticleRegistry registry;
    phys2::DampingGenerator dumping(0.47f, 0.001f);
    phys2::GravityGenerator gravity;
    // registry.addParticle(&part1, &dumping);
    registry.addParticle(&part1, &gravity);
    registry.addParticle(&part2, &gravity);
    part1.addVelocity({20.f, 0.f});

    phys2::ParticleContact* contact = new phys2::ParticleContact(&part1, &part2);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        phys2::vec2 pos = part1.getPosition();
        DrawCircle(50.f + pos.x * 10.f, 50.f + pos.y * 10.f, 10.f, RED);
        TraceLog(LOG_INFO, "%f, %f", pos.x, pos.y);
        phys2::vec2 pos2 = part2.getPosition();
        DrawCircle(150.f + pos2.x * 10.f, 50.f + pos2.y * 10.f, 10.f, RED);

        EndDrawing();

        registry.updateAll(GetFrameTime());
        part1.integrate(GetFrameTime());
        part2.integrate(GetFrameTime());
        phys2::vec2 vel = part1.getVelocity();
        TraceLog(LOG_INFO, "%f, %f", vel.x, vel.y);

        if (CheckCollisionCircles({pos.x, pos.y}, 10.f, {pos2.x, pos2.y}, 10.f))
        {
            resolver.resolveContacts({contact}, GetFrameTime());
        }
    }

    delete contact;

    CloseWindow();

    return 0;
}
