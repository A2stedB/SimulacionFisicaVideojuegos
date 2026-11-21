#include "raylib.h"
#include "ParticleExperimental.h"
#include <vector>

namespace
{
    using namespace sim;
    Particle par;
    Particle::Data par_data;

    //Projectile proj;
    //Projectile::Data proj_data;

    //bool render_proj = false;

    std::vector<Particle> vector_particle = std::vector<Particle>();
    std::vector<Projectile> vector_projectile = std::vector<Projectile>();
};


int main()
{
    using namespace sim;
    par_data.position = Position(0, 0, 0);
    par_data.velocity = Velocity(1, 0, 0);
    par_data.acceleration = Acceleration(0, -9.8, 0);

    par = Particle(par_data);

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Simulacion Fisica");

    Camera3D camera = { 0 };
    camera.position = Vector3{ -10.0f, 10.0f, 10.0f };
    camera.target = Vector3{ 0.0f, 0.0f, 0.0f };
    camera.up = Vector3{ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    int cameraMode = CAMERA_FIRST_PERSON;


    HideCursor();
    DisableCursor();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        {
            UpdateCamera(&camera, CAMERA_FREE);
            const Matrix m = GetCameraMatrix(camera);
            //std::cout << camera.target.x << " " << camera.target.y << " " << camera.target.z << " " << std::endl;
            //std::cout << -m.m2 << " " << -m.m6 << " " << -m.m10 << " " << std::endl;
            if (IsKeyPressed(KEY_SPACE))
            {
                Projectile::Data proj_data;
                proj_data.mass = 0.01f;
                proj_data.particle_data.acceleration = Acceleration{ 0.0f,-9.8f,0.0f };
                proj_data.particle_data.position = Position(camera.position.x,camera.position.y,camera.position.z);

                Vector3D camera_front = Vector3D(m.m2, m.m6, m.m10) * -1;
                proj_data.particle_data.velocity = Velocity(camera_front * 10);

                const Projectile proj = Projectile(proj_data);

                vector_projectile.push_back(proj);
            }

            float dt = GetFrameTime();

            for (sim::Particle& particle : vector_particle)
            {
                Particle_Integrate(&particle, dt, IntegrateType::Symplectic_Euler);
            }

            for (Projectile& projectile : vector_projectile)
            {
                Particle_Integrate(&projectile.particle, dt, IntegrateType::Symplectic_Euler);
            }
            //Particle_Integrate(&par, dt, IntegrateType::Symplectic_Euler);

            //if (render_proj)
            //{
            //    Particle_Integrate(&proj.particle, dt, IntegrateType::Symplectic_Euler);
            //}
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);

        {

            BeginMode3D(camera);

            DrawCube(Vector3{0,0,0}, 2.0f, 2.0f, 2.0f, RED);
            DrawCubeWires(Vector3{ 0,0,0 }, 2.0f, 2.0f, 2.0f, MAROON);

            DrawGrid(10, 1.0f);

            DrawSphere(Vector3{par.position.x,par.position.y,par.position.z}, 1.0f, BLUE);

            {

                for (Projectile& projectile : vector_projectile)
                {
                    const Position& pos = projectile.particle.position;
                    DrawSphere(Vector3{ pos.x,pos.y,pos.z }, 0.5f, RED);
                }
                //if (render_proj)
                //{
                //    const Position& pos = proj.particle.position;
                //    DrawSphere(Vector3{ pos.x,pos.y,pos.z }, 1.0f, RED);
                //}
            }
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