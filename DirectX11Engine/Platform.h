#pragma once
#include "Entity.h"

class Platform : public Entity
{
	std::string name = "Platform";
	std::unique_ptr<GeometricPrimitive> model;
	ID3D11DeviceContext* deviceContext;
	Camera* camera;
	XMMATRIX world = DirectX::XMMatrixIdentity();
	float uptime = 0.0f;
	bool moving = false;
	bool vertical = false;
	bool left=false;
public:
	PxRigidDynamic* rigidBody;
	void Init(ID3D11DeviceContext* deviceContext, PxPhysics* physx, PxScene* scene, float x, float y, float z) ;
	void MakeMovable(bool vertical,bool left);
	void Update() ;
	void Render(Camera camera) ;
};