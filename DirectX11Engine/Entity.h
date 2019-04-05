#pragma once
#include <string>
#include "Engine.h"


class Entity
{
	std::string name = "";
public:
	virtual void Init(ID3D11DeviceContext* deviceContext, PxPhysics* physx, PxScene* scene, float x, float y, float z) =0;
	virtual void Update()=0;		
	virtual void Render(Camera camera) =0;
};


