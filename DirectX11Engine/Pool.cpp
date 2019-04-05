#include "Pool.h"

void Pool::Init(ID3D11DeviceContext * deviceContext, PxPhysics * physx, PxScene * scene, float x, float y, float z)
{
	
	PxMaterial* material = physx->createMaterial(0.5, 0.5, 0.8);
	PxShape* tempShape;
	PxFilterData filterData;

	PxTransform poolPos(PxVec3(x,y,z));
	rigidBody = PxCreateDynamic(*physx, poolPos, PxBoxGeometry(600.0f, 1.0f, 300.0f), *material, 0.8f);
	rigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
	rigidBody->getShapes(&tempShape, 1);
//	rigidBody->userData = "x\n";
	tempShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	tempShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	filterData.word0 = PxObjectGroup::TRIGGER;
	tempShape->setQueryFilterData(filterData);
	scene->addActor(*rigidBody);
}
