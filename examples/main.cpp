#include <iostream>
#include "ForceGenerators.h"
#include "Particle.h"
#include "raylib.h"

int main()
{
    InitWindow(500, 500, "PhysExample");
    SetTargetFPS(120);

    phys2::Particle part;
    phys2::ParticleRegistry registry;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircle(50.f, 50.f, 20.f, RED);

        EndDrawing();
    }

    CloseWindow();

    part.integrate(0.1);
    return 0;
}
