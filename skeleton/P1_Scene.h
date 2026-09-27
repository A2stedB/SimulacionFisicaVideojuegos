#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "Particle.h"
class P1_Scene : public Scene
{
public:
	explicit P1_Scene(std::string name) : Scene(std::move(name)) {};

    void init() override 
    {
        //physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        par = new Particle(Vector3D{1.0,0.0,0.0},Vector3D{1.0,0.0,0.0},Vector3D{0,-3,0});
        //physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));
        //par->velocity = Vector3D{ 1,0,0 };
        //par->transform = physx::PxTransform(Vector3D{0.0f, 0.0f, 0.0f});
        //par->renderItem = new RenderItem(shape, &par->transform,YELLOW);
        //m_particle.push_back(Particle(Vector3D{1,0,0}, Vector3D{0,0,0}));
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
        par->integrate(dt,IntegrationType::Euler);

        //for (Particle& particle : m_particle) 
        //{
        //    particle.integrate(dt,IntegrationType::Euler);
        //}
    }
    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

    }

    void cleanup() override {
        for (RenderItem* render_item : m_renderItem)
            if (render_item) {
                render_item->release(); // Deregistra y destruye el item
                render_item = nullptr;
            }
        //delete par;
    }
private:
    Particle* par{};
    std::vector<RenderItem*> m_renderItem;
    //std::vector<Particle> m_particle;
};

