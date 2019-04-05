#pragma once
#include "Entity.h"

class Trophy : public Entity
{

	std::string name = "Trophy";	
	std::unique_ptr<GeometricPrimitive> model;
	ID3D11DeviceContext* deviceContext;
	Camera* camera;
	XMMATRIX world = DirectX::XMMatrixIdentity();
	float uptime = 0.0f;
public:
	PxRigidDynamic* rigidBody;
	void Init(ID3D11DeviceContext* deviceContext, PxPhysics* physx, PxScene* scene, float x, float y, float z);
	void Update();
	void Render(Camera camera);
};