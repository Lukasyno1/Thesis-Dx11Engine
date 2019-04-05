#include "Platform.h"

void Platform::Init(ID3D11DeviceContext * deviceContext, PxPhysics * physx, PxScene * scene, float x, float y, float z)
{
	
	XMFLOAT3 size = XMFLOAT3(10.0f, 0.5f, 10.0f);	
	model = GeometricPrimitive::CreateBox(deviceContext, size);

	PxMaterial* material = physx->createMaterial(0.5, 0.5, 0.8);
	PxShape* tempShape;
	PxFilterData filterData;

	PxTransform	pos(PxVec3(x, y, z));
	rigidBody = PxCreateDynamic(*physx, pos, PxBoxGeometry(4.8f, 0.5f, 4.8f), *material, 1.0f);
	rigidBody->setLinearDamping(0.05);
	rigidBody->setAngularDamping(0.05);
	rigidBody->setMass(.0f);
	//rigidBody->userData = "Platform";
	filterData.word0 = PxObjectGroup::DYNAMIC;
	rigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	rigidBody->getShapes(&tempShape, 1);
	tempShape->setQueryFilterData(filterData);
	scene->addActor(*rigidBody);
}

void Platform::MakeMovable(bool vertical, bool left)
{
	this->moving = true;
	this->vertical = vertical;
	this->left = left;
}

void Platform::Update()
{
	uptime += 0.01f;
	world = DirectX::XMMatrixTranslation(rigidBody->getGlobalPose().p.x, rigidBody->getGlobalPose().p.y,
		rigidBody->getGlobalPose().p.z);

	if (moving && vertical)
		rigidBody->setGlobalPose(PxTransform(rigidBody->getGlobalPose().p.x, rigidBody->getGlobalPose().p.y + 0.3*sin(uptime), 
			rigidBody->getGlobalPose().p.z));
	else if(moving && !vertical && left)
		rigidBody->setGlobalPose(PxTransform(rigidBody->getGlobalPose().p.x + 0.3*sin(uptime),
			rigidBody->getGlobalPose().p.y, rigidBody->getGlobalPose().p.z));
	else if(moving && !vertical && !left)
		rigidBody->setGlobalPose(PxTransform(rigidBody->getGlobalPose().p.x - 0.3*sin(uptime),
			rigidBody->getGlobalPose().p.y, rigidBody->getGlobalPose().p.z));
	
}

void Platform::Render(Camera camera)
{
	model->Draw(world, camera.GetViewMatrix(), camera.GetProjectionMatrix(), Colors::Blue);
}
