#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
	PxRigidDynamic* rigidBody;	
	std::string name = "Player";
	std::unique_ptr<GeometricPrimitive> model;
	ID3D11DeviceContext* deviceContext;
	Camera* camera;
	XMMATRIX world = DirectX::XMMatrixIdentity();
	XMFLOAT3 initPos;
	void Init(ID3D11DeviceContext* deviceContext, PxPhysics* physx, PxScene* scene, float x, float y, float z) ;
	 void Update() ;
	 void OnContact();
	 void OnTrigger(std::string trigger);
	 void Reset();
	 void Render(Camera camera) ;
	 void Move(char x);
};
