#include "Game.h"

void Game::InitGame()
{
	//create player
	player.Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 0.0f, 13.0f, 0.0f);
	entities.push_back(&player);

	//create platforms
	p[0].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 0.0f, 10.0f, 0.0f);
	entities.push_back(&p[0]);
	p[1].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 0.0f, 10.0f, 10.0f);
	entities.push_back(&p[1]);
	p[2].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 0.0f, 10.0f, 20.0f);
	p[2].MakeMovable(true, false);
	entities.push_back(&p[2]);
	p[3].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 0.0f, 70.0f, 30.0f);	
	entities.push_back(&p[3]);
	p[4].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, -20.0f, 70.0f, 50.0f);
	entities.push_back(&p[4]);
	p[5].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 20.0f, 70.0f, 70.0f);
	entities.push_back(&p[5]);
	p[6].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, -20.0f, 70.0f, 90.0f);
	entities.push_back(&p[6]);
	p[7].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 0.0f, 70.0f, 110.0f);
	entities.push_back(&p[7]);
	p[8].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, -20.0f, 70.0f, 140.0f);
	p[8].MakeMovable(false,true);
	entities.push_back(&p[8]);
	p[9].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 20.0f, 70.0f, 170.0f);
	p[9].MakeMovable(false,false);
	entities.push_back(&p[9]);
	p[10].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, -20.0f, 70.0f, 200.0f);
	p[10].MakeMovable(false,true);
	entities.push_back(&p[10]);
	p[11].Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 0.0f, 70.0f, 220.0f);
	entities.push_back(&p[11]);

	//create pool
	pool.Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 150.0f, 0.0f, 0.0f);
	entities.push_back(&pool);

	//create Trophy
	Trophy.Init(this->deviceContext.Get(), g_PhysicsSDK, g_PxScene, 0.0f, 72.0f, 220.0f);
	entities.push_back(&Trophy);	
}

void Game::Render()
{	
	float bgcolor[] = { 0.0f, 0.0f, 0.0f, 0.3f };
	this->deviceContext->ClearRenderTargetView(this->renderTargetView.Get(), bgcolor);
	this->deviceContext->ClearDepthStencilView(this->depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//render entities
	for (auto& entity : entities)	
		entity->Render(camera);	
	
	//present
	this->swapchain->Present(1, NULL);  //1-> v-sync on, 0-> v-sync off
}

void Game::ProcessInput()
{	
	while (!keyboard.CharBufferIsEmpty())
	{
		unsigned char ch = keyboard.ReadChar();
	}

	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
	}

	while (!mouse.EventBufferIsEmpty())
	{
		MouseEvent me = mouse.ReadEvent();		
		if (me.GetType() == MouseEvent::EventType::RAW_MOVE)			
				camera.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);		
	}	

	if(keyboard.KeyIsPressed('W'))	
		player.Move('W');	
	
	if(keyboard.KeyIsPressed('S'))	
		player.Move('S');		

	if (keyboard.KeyIsPressed('A'))	
		player.Move('A');		

	if (keyboard.KeyIsPressed('D'))	
		player.Move('D');		

	if (keyboard.KeyIsPressed(0x1B)) // escape	
	{
		PostMessage(this->window.GetHWND(), WM_CLOSE, 0, 0);
	}	
}

void Game::SimulatePhysics()
{
	g_PxScene->simulate(1.0f / 60.0f); //simulate physics 1/60s
	g_PxScene->fetchResults(true);
}

void Game::Update()
{	
	//update camera
	camera.SetPosition(player.rigidBody->getGlobalPose().p.x, player.rigidBody->getGlobalPose().p.y+1.5f, 
		player.rigidBody->getGlobalPose().p.z-3.0f);

	//update entities
	for ( auto& entity : entities) 
		entity->Update();	
}

void Game::onTrigger(PxTriggerPair * pairs, PxU32 count)
{
	for (PxU32 i = 0; i < count; i++)
	{		
		if (pairs[i].flags & (PxTriggerPairFlag::eDELETED_SHAPE_TRIGGER | PxTriggerPairFlag::eDELETED_SHAPE_OTHER))
			continue;

		if (pairs[i].triggerActor == pool.rigidBody)
		{
			if (pairs[i].otherActor == player.rigidBody)
			{
				if (pairs[i].status == PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					player.OnTrigger("Pool");
				}					
			}
		}

		else if (pairs[i].triggerActor == Trophy.rigidBody)
		{
			if (pairs[i].otherActor == player.rigidBody)
			{
				if (pairs[i].status == PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					PostMessage(this->window.GetHWND(), WM_CLOSE, 0, 0);
				}
			}
		}
	}
}

void Game::onContact(const PxContactPairHeader & pairHeader, const PxContactPair * pairs, PxU32 nbPairs)
{
	const PxU32 bufferSize = 64;
	PxContactPairPoint contacts[bufferSize];
	for (PxU32 i = 0; i < nbPairs; i++)
	{
		const PxContactPair& cp = pairs[i];		
		if (cp.events & PxPairFlag::eNOTIFY_TOUCH_FOUND)		
			if ((pairHeader.actors[0] == player.rigidBody) || (pairHeader.actors[1] == player.rigidBody)) 									
				player.OnContact();	
	}
}

