#include <chrono>
#include <iostream>
#include "ForceGenerators.h"
#include "Particle.h"
#include "raylib.h"

int main()
{
    InitWindow(500, 500, "PhysExample");
    SetTargetFPS(120);

    phys2::Particle part;
    part.setMass(1.f);
    phys2::ParticleRegistry registry;
    phys2::DampingGenerator dumping(0.47f, 0.001f);
    phys2::GravityGenerator gravity;
    registry.addParticle(&part, &dumping);
    registry.addParticle(&part, &gravity);
    part.addVelocity({20.f, 0.f});

    while (!WindowShouldClose())
    {
        BeginDrawing();
        // ClearBackground(RAYWHITE);

        phys2::vec2 pos = part.getPosition();
        DrawCircle(50.f + pos.x, 50.f + pos.y, 10.f, RED);
        TraceLog(LOG_INFO, "%f, %f", pos.x, pos.y);

        EndDrawing();

        registry.updateAll(GetFrameTime());
        part.integrate(GetFrameTime());
        phys2::vec2 vel = part.getVelocity();
        TraceLog(LOG_INFO, "%f, %f", vel.x, vel.y);
    }

    CloseWindow();

    return 0;
}
