#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "PxPhysicsAPI.h"
#include "Vector3D.h"
#include "Helper.h"
using namespace physx;

class P0S_Scene : public Scene {
public:

    explicit P0S_Scene(std::string name) : Scene(std::move(name)) {};

	void init() override 
    {
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        m_transform = physx::PxTransform(physx::PxVec3(0.0f, 0.0f, 0.0f));

        // Se registra el RenderItem exactamente como en la plantilla original
        m_renderItem.push_back(new RenderItem(shape, &m_transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f)));

        
        //t_x = physx::PxTransform(u);
        //t_y = physx::PxTransform(v);
        //t_z = physx::PxTransform(w);

        //t_x.p *= 5;
        //t_y.p *= 5;
        //t_z.p *= 5;

        //m_renderItem.push_back(new RenderItem(shape, &t_x, RED));
        //m_renderItem.push_back(new RenderItem(shape, &t_y, GREEN));
        //m_renderItem.push_back(new RenderItem(shape, &t_z, BLUE));

        float dot = dot_product(origin.p,p_1.p);
        if (dot > 0)
        {
            m_renderItem.push_back(new RenderItem(shape, &p_1, GREEN));
        }
        dot = dot_product(origin.p,p_2.p);
        if (dot < 0)
        {
            m_renderItem.push_back(new RenderItem(shape, &p_2, RED));
        }
        dot = dot_product(origin.p, p_3.p);
        if (dot == 0)
        {
            m_renderItem.push_back(new RenderItem(shape, &p_3, YELLOW));
        }


    };
    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }
    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        //if (key == 'r' || key == 'R') {
        //    m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        //}
    }

    void cleanup() override {
        for (RenderItem* render_item : m_renderItem)
            if (render_item) {
                render_item->release(); // Deregistra y destruye el item
                render_item = nullptr;
            }
    }
private:
    //Vector3D u{ 3.0f,1.0f,0.0f }, v{ 0.0f,4.0f,0.0f };
    //Vector3D w = cross_product(u,v);
    physx::PxTransform m_transform;
    //physx::PxTransform t_x;
    //physx::PxTransform t_y;
    //physx::PxTransform t_z;
    PxTransform origin = PxTransform(Vector3D{ 0,0,0 });
    PxTransform p_1 = PxTransform(Vector3D{ 2.0, 0.0, 3.0 });
    PxTransform p_2 = PxTransform(Vector3D{ -4.0, 0.0, 1.0 });
    PxTransform p_3 = PxTransform(Vector3D{ 0.0, 0.0,5.0 });
    PxTransform p_4 = PxTransform(Vector3D{ 3.0, 0.0, 0.0 });
    std::vector<RenderItem*> m_renderItem;
};