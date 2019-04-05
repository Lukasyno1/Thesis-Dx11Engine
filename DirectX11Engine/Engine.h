#pragma once
#include "Window.h"
#include "KeyboardClass.h"
#include "MouseClass.h"
#include <PxPhysicsAPI.h>
#include <cmath>
#include "AdapterReader.h"
#include "Shaders.h"
#include "Vertex.h"
#include <SpriteBatch.h>
#include <SpriteFont.h>
#include <WICTextureLoader.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "Timer.h"
#include <Effects.h>
#include <Model.h>
#include <GeometricPrimitive.h>
#include <CommonStates.h>

using namespace physx;

enum PxObjectGroup //object types
{
	DYNAMIC = (1 << 0),
	TEREN = (1 << 1),
	TRIGGER = (1 << 2),	
};

class Engine : public PxSimulationEventCallback
{
public:
	bool Initialize(HINSTANCE hInstance, std::string window_title, std::string window_class, int width, int height);
	bool ProcessMessages();
	bool InitPhysx();
	void ConnectPVD();
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	bool InitializeDirectX(HWND hwnd);	

	//event callback	
	void onConstraintBreak(PxConstraintInfo*, PxU32);
	void onWake(PxActor**, PxU32);
	void onSleep(PxActor**, PxU32);


	//input
	Window													window;
	KeyboardClass											keyboard;
	MouseClass												mouse;
	
	//physx
	PxPhysics*												g_PhysicsSDK = NULL;			//Instance of PhysX SDK
	PxFoundation*											g_Foundation = NULL;			//Instance of singleton foundation SDK class
	PxDefaultErrorCallback									g_DefaultErrorCallback;		    //Instance of default implementation of the error callback
	PxDefaultAllocator										g_DefaultAllocatorCallback;	    //Instance of default implementation of the allocator interface required by the SDK

	PxVisualDebuggerConnection*								g_Connection = NULL;
	PxScene*												g_PxScene = NULL;	//Instance of PhysX Scene	
	PxRigidStatic*											g_PxTeren = NULL;
	
	//graphics
public:
	Camera													camera;
protected:	
	Timer timer1;
	//graphics
	Microsoft::WRL::ComPtr<ID3D11Device>					device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>				deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain>					swapchain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>			renderTargetView;
	
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>			depthStencilView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>					depthStencilBuffer;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>			depthStencilState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>			rasterizerState;
	
	//std::unique_ptr<DirectX::SpriteBatch>					spriteBatch;
	//std::unique_ptr<DirectX::SpriteFont>					spriteFont;

	Microsoft::WRL::ComPtr<ID3D11SamplerState>				sampleState;
	
	int windowWidth = 0;
	int windowHeight = 0;
};


