#pragma once
#include "Entity.h"

class Pool : public Entity
{
public:
	std::string name = "Pool";
	PxRigidDynamic* rigidBody;
	std::unique_ptr<GeometricPrimitive> model;
	ID3D11DeviceContext* deviceContext;
	Camera* camera;
	XMMATRIX world = DirectX::XMMatrixIdentity();
	float uptime = 0.0f;
public:
	void Init(ID3D11DeviceContext* deviceContext, PxPhysics* physx, PxScene* scene, float x, float y, float z);
	void Update() {};
	void Render(Camera camera) {};
};