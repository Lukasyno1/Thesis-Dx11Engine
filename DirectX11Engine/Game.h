#pragma once
#include "Engine.h"
#include "Player.h"
#include "Platform.h"
#include "Trophy.h"
#include "Pool.h"
#include <vector>

class Game : public Engine
{
	std::vector<Entity*>			entities;
	Pool							pool;		
	Trophy							Trophy;
	Player							player;
	Platform						p[12];

public: 	 
	void InitGame();
	void Render();
	void ProcessInput();
	void Update();
	void SimulatePhysics();
	void onTrigger(PxTriggerPair* pairs, PxU32 count);
	void onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs);

};




