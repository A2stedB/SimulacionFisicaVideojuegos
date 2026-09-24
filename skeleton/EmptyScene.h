#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "PxPhysicsAPI.h"

using namespace physx;

class EmptyScene : public Scene {
public:
    explicit EmptyScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        m_transform = physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f));

        // Se registra el RenderItem exactamente como en la plantilla original
        m_renderItem.push_back(new RenderItem(shape, &m_transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f)));
        


        m_x = PxTransform{ PxVec3{10.0f,10.0f,0.0f} };
        m_renderItem.push_back(new RenderItem(shape, &m_x, Vector4{ 1,0,0,1 }));

        m_y = PxTransform{PxVec3{0.0f,20.0f,0.0f}};
        m_renderItem.push_back(new RenderItem(shape, &m_y, Vector4{ 0,1,0,1 }));

        m_z = PxTransform{ PxVec3{0.0f,10.0f,10.0f} };
        m_renderItem.push_back(new RenderItem(shape, &m_z, Vector4{ 0,0,1,1 }));
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        }
    }

    void cleanup() override {
        for(RenderItem* render_item : m_renderItem)
        if (render_item) {
            render_item->release(); // Deregistra y destruye el item
            render_item = nullptr;
        }
    }

private:
    physx::PxTransform m_transform;
    physx::PxTransform m_x;
    physx::PxTransform m_y;
    physx::PxTransform m_z;
    std::vector<RenderItem*> m_renderItem;
};