#pragma once
#include "Vector3D.h"
class ForceGenerator
{
public:
	ForceGenerator();

	virtual Vector3D getForce(int mass) = 0;
public:
	// Una fuerza
	//Vector3D acceleration{};
	// Area de efecto (puede no tenerlo)
	// 
};


class GravityForceGenerator : public ForceGenerator 
{
public:
	Vector3D getForce(int mass) override
	{
		return acceleration * mass;
	}
public:
	
	Vector3D acceleration{ 0,-9.8,0 };
};



