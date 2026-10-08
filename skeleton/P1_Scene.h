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
        //physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        //par = new Particle(Vector3D{10.0,0.0,0.0},Vector3D{1.0,0.0,0.0},Vector3D{0,-3,0});
        Camera* camera = GetCamera();
        //proyectile1 = new Proyectile(camera,500_m_s,-9.8_m_s,5_g,25_m_s);
        proyectile1 = new Proyectile(camera,100_m_s,-9.8_m_s,100_g,25_m_s);

        
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
        proyectile1->integrate(dt,IntegrationType::Symplectic_Euler);

        for (auto& proyectile : m_Particles)
        {
            proyectile->integrate(dt, IntegrationType::Symplectic_Euler);
        };

        //for (Particle& particle : m_particle) 
        //{
        //    particle.integrate(dt,IntegrationType::Euler);
        //}
    }
    void keyPress(unsigned char key, const physx::PxTransform& camera) override 
    {
        switch (key) {
            case '+':
                proyectile1->modify_real_mass(5);
                break;
            case '-':
                proyectile1->modify_real_mass(-5);
                break;
            case ' ':
                m_Particles.push_back(new Proyectile(GetCamera(), 100_m_s, -9.8_m_s, 100_g, 25_m_s));
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
        delete par;
        delete proyectile1;
    }
private:
    Particle* par{};
    Proyectile* proyectile1{};
    std::vector<Particle*> m_Particles{};
    std::vector<RenderItem*> m_renderItem{};
    //std::vector<Particle> m_particle;
};

