#include "Trophy.h"

void Trophy::Init(ID3D11DeviceContext * deviceContext, PxPhysics * physx, PxScene * scene, float x, float y, float z)
{
		
	model = GeometricPrimitive::CreateTeapot(deviceContext, 3.0f);

	PxMaterial* material = physx->createMaterial(0.5, 0.5, 0.8);
	PxShape* tempShape;
	PxFilterData filterData;

	PxTransform	pos(PxVec3(x,y,z));
	rigidBody = PxCreateDynamic(*physx, pos, PxBoxGeometry(1.5f, 1.5f, 1.5f), *material, 0.8f);
	rigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	rigidBody->getShapes(&tempShape, 1);
	//rigidBody->userData = "Trophy";
	tempShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	tempShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	filterData.word0 = PxObjectGroup::TRIGGER;
	tempShape->setQueryFilterData(filterData);
	scene->addActor(*rigidBody);
}

void Trophy::Update()
{
	world = DirectX::XMMatrixTranslation(rigidBody->getGlobalPose().p.x, rigidBody->getGlobalPose().p.y, rigidBody->getGlobalPose().p.z);
}

void Trophy::Render(Camera camera)
{
	model->Draw(world, camera.GetViewMatrix(), camera.GetProjectionMatrix(), Colors::Red);
}
