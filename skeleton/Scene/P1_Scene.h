#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "Particle.h"
#include "Proyectile.h"
#include "Unit.h"

class P1_Scene : public Scene
{
public:
	explicit P1_Scene(std::string name) : Scene(std::move(name)) {};

    void init() override 
    {
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        par1 = new Particle(shape,Velocity{10.0,0.0,0.0},Position{1.0,0.0,0.0},Acceleration{0,-3,0},RED,1_kg);
        par2 = new Particle(shape, Velocity{10.0,0.0,0.0}, Position{1.0,0.0,0.0},Acceleration{0,-3,0},RED,1_g);
        Camera* camera = GetCamera();
        //proyectile1 = new Proyectile(camera,500_m_s,-9.8_m_s,5_g,25_m_s);

        shape = CreateShape(physx::PxSphereGeometry(1.0f));
        //proyectile1 = new Proyectile(shape,camera, 100_m_s, -9.8_m_s, 100_g, 25_m_s, Color{0,1,0,1});

        
        //physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));
        //par->velocity = Vector3D{ 1,0,0 };
        //par->transform = physx::PxTransform(Vector3D{0.0f, 0.0f, 0.0f});
        //par->renderItem = new RenderItem(shape, &par->transform,YELLOW);
        //m_particle.push_back(Particle(Vector3D{1,0,0}, Vector3D{0,0,0}));
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
        //par->integrate(dt,IntegrationType::Euler);
        //proyectile1->integrate(dt,IntegrationType::Symplectic_Euler);

        for (auto& proyectile : m_Particles)
        {
            proyectile->Integrate(dt, IntegrationType::Symplectic_Euler);
            --proyectile->lifetime;

            if (proyectile->lifetime <= 0)
            {
                std::swap(proyectile, m_Particles[m_Particles.size() - 1]);
                delete proyectile;
                m_Particles.pop_back();
            }
        };

        //for (Particle& particle : m_particle) 
        //{
        //    particle.integrate(dt,IntegrationType::Euler);
        //}
    }
    void keyPress(unsigned char key, const physx::PxTransform& camera) override 
    {
        Proyectile* proyectile = nullptr;
        switch (key) {
            case '+':
                proyectile->modify_real_velocity(5);
                break;
            case '-':
                proyectile->modify_real_velocity(-5);
                break;
            case 'f':
                proyectile = new Proyectile(shape,GetCamera(), 100_m_s, -9.8_m_s, 100_g, 25_m_s, Color{0,1,0,1});
                m_Particles.push_back(proyectile);
                proyectile->lifetime = 500;
                break;
            case 'j':
                Proyectile* proyectile2 = new Proyectile(shape, GetCamera(), 300_m_s, -9.8_m_s, 8_g, 25_m_s, Color{ 0,0,1,1 });
                m_Particles.push_back(proyectile2);
                proyectile2->lifetime = 500;
                break;
        }
    }

    void cleanup() override {
        for (RenderItem* render_item : m_renderItem)
            if (render_item) {
                render_item->release(); // Deregistra y destruye el item
                render_item = nullptr;
            }

        for (Particle* particle : m_Particles)
            if (particle)
            {
                delete particle;
                particle = nullptr;
            }
        delete par1;
        delete par2;
    }

private:

private:
    Particle* par1{};
    Particle* par2{};
    std::vector<Particle*> m_Particles{};
    std::vector<RenderItem*> m_renderItem{};
    physx::PxShape* shape = nullptr;
    //std::vector<Particle> m_particle;
};

