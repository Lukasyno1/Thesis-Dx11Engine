#include "Player.h"

void Player::Init(ID3D11DeviceContext* deviceContext, PxPhysics* physx, PxScene* scene, float x, float y, float z)
{
	initPos = XMFLOAT3(x, y, z);
	model = GeometricPrimitive::CreateSphere(deviceContext);
	PxMaterial* material = physx->createMaterial(0.5, 0.5, 0.8); 
	PxShape* tempShape;
	PxFilterData filterData;

	PxTransform	pos(PxVec3(x,y,z));
	rigidBody = PxCreateDynamic(*physx, pos, PxSphereGeometry(0.57f), *material, 0.02f);
	rigidBody->setLinearDamping(0.1);
	rigidBody->setAngularDamping(2);
	//rigidBody->userData = 1;
	filterData.word0 = PxObjectGroup::DYNAMIC;
	rigidBody->getShapes(&tempShape, 1);
	tempShape->setQueryFilterData(filterData);
	scene->addActor(*rigidBody);
}

void Player::Update()
{
		world = DirectX::XMMatrixTranslation(rigidBody->getGlobalPose().p.x, rigidBody->getGlobalPose().p.y, rigidBody->getGlobalPose().p.z);
}

void Player::OnContact()
{
	rigidBody->addForce(PxVec3(0.0f, 0.05f, 0.0f), PxForceMode::eIMPULSE);
}

void Player::OnTrigger(std::string trigger)
{
	if (trigger == "Pool") Reset();
}

void Player::Reset()
{
	rigidBody->setGlobalPose(PxTransform(PxVec3(initPos.x, initPos.y, initPos.z)));
}

void Player::Render(Camera camera)
{
    model->Draw(world, camera.GetViewMatrix(), camera.GetProjectionMatrix(), Colors::Yellow);
}

void Player::Move(char x)
{
	switch (x)
	{
	case 'W':
		rigidBody->addForce(PxVec3(0.0f, 0.0f, 0.01f), PxForceMode::eIMPULSE);
		break;

	case 'S':
		rigidBody->addForce(PxVec3(0.0f, 0.0f, -0.01f), PxForceMode::eIMPULSE);
		break;

	case 'A':
		rigidBody->addForce(PxVec3(-0.01f, 0.0f, 0.0f), PxForceMode::eIMPULSE);
		break;
		
	case 'D':
		rigidBody->addForce(PxVec3(0.01f, 0.0f, 0.0f), PxForceMode::eIMPULSE);
		break;
	}
}
