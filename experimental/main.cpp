#include "raylib.h"
#include "ParticleExperimental.h"

sim::Particle::ParticleData data;


int main()
{
    using namespace sim;
    Particle::ParticleData data;
    data.position = Position(0, 0, 0);
    data.velocity = Velocity(1, 0, 0);
    data.acceleration = Acceleration(0, -9.8, 0);

    Particle par = Particle(data);

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Simulacion Fisica");

    Camera3D camera = { 0 };
    camera.position = Vector3{ 0.0f, 10.0f, 10.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int cameraMode = CAMERA_FIRST_PERSON;

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    HideCursor();
    DisableCursor();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        {
            UpdateCamera(&camera, CAMERA_FREE);
            Particle_Integrate(&par, GetFrameTime(), IntegrateType::Symplectic_Euler);
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);

        {

            BeginMode3D(camera);

            //DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
            //DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

            //DrawGrid(10, 1.0f);

            DrawSphere(par.position,1.0f,BLUE);
            //DrawSphere(Vector3(10,-5,0), 1.0f, RED);

            EndMode3D();

            //DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

            //DrawFPS(10, 10);
        }

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}