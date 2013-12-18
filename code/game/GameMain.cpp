#include "GameMain.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/Camera.h"
#include "../core/time/Time.h"
#include "../core/resource/prefabLoader/PrefabLoader.h"

#include "../renderer/RenderEngine.h"
#include "../renderer/RendererConfig.h"
#include "../renderer/PlatformRenderer.h"

#include "../game/RenderTestComponent.h"
#include "../game/TriangleComponent.h"
#include "../game/TextComponent.h"
#include "../game/ObjLoaderTestComponent.h"
#include "../game/FPCameraControllerComponent.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

//-----------------------------------------------------------------------------------
int LuaTest(lua_State *pLuaState)
{
	int argc = lua_gettop(pLuaState);

	for(int i=1; i<=argc; ++i)
	{
		//OutputDebugStr(lua_tostring(pLuaState, i));
		//OutputDebugStr("\n");
	}

	return 0;
}

//-----------------------------------------------------------------------------------
void GameMain::OnAwake()
{
	// The root should always be at the center of the world.
	mpGameObject->mpTransform->mMatWorld.Translate(Vector3(0.0f, 0.0f, 0.0f));

	// Add Game Specific logic below.
	
	GameObject *pChildObj = new GameObject("Empty");

	pChildObj = PrefabLoader::Load("./assets/prefabs/Robot.txt");
	if( pChildObj )
	{
		mpGameObject->mpTransform->mChildren.push_back(pChildObj->mpTransform);
		pChildObj->mpTransform->Position = Vector3(-0.04f,0.15f,1);
	}

	pChildObj = PrefabLoader::Load("./assets/prefabs/TekkaMan.txt");
	if( pChildObj )
	{
		mpGameObject->mpTransform->mChildren.push_back(pChildObj->mpTransform);
		pChildObj->mpTransform->Position = Vector3(0.04f,0.15f,1);
	}

	pChildObj = new GameObject("TitleText");
	TextComponent *textComponent = new TextComponent(pChildObj);
	pChildObj->AddComponent( static_cast<TextComponent*>( textComponent ) );
	mpGameObject->mpTransform->mChildren.push_back(pChildObj->mpTransform);
	pChildObj->mpTransform->Position = Vector3(-0.15f,0.30f,1);
	textComponent->SetText("xdPixelEngine v0.01");

	pChildObj = new GameObject("FPSText");
	fpsText = new TextComponent(pChildObj);
	pChildObj->AddComponent( static_cast<TextComponent*>( fpsText ) );
	mpGameObject->mpTransform->mChildren.push_back(pChildObj->mpTransform);
	pChildObj->mpTransform->Position = Vector3(-0.15f,0.25f,1);
	fpsText->SetText("FPS: 30");

	/*
	GameObject *pChildObj = new GameObject("RenderTest1");
	pChildObj->AddComponent( static_cast<GameObjectComponent*>( new RenderTestComponent(pChildObj) ) );
	mpGameObject->mpTransform->mChildren.push_back(pChildObj->mpTransform);
	

	
	pChildObj = new GameObject("RenderTest2");
	pChildObj->AddComponent( static_cast<GameObjectComponent*>( new RenderTestComponent(pChildObj) ) );
	mpGameObject->mpTransform->mChildren.push_back(pChildObj->mpTransform);
	
	pChildObj = new GameObject("Triangle");
	pChildObj->AddComponent( static_cast<GameObjectComponent*>( new TriangleComponent(pChildObj) ) );
	mpGameObject->mpTransform->mChildren.push_back(pChildObj->mpTransform);
	*/

	pChildObj = new GameObject("Camera");
	Camera *camera = new Camera(pChildObj);
	pChildObj->AddComponent(static_cast<Camera*>( camera ));
	mpGameObject->mpTransform->mChildren.push_back(pChildObj->mpTransform);

	pChildObj->mpTransform->Position = Vector3(0,-0.2f,0.0f);
	camera->BackGroundColor = Color(Color::GRAY);
	camera->mAspectRatio = RenderEngine::GetInstance()->GetRenderConfig()->GetAspectRatio();
	camera->mFov = 45.0f;
	camera->mNear = 0.01f;
	camera->mFar = 10000.0f;
	camera->BuffersToClear = PlatformRenderer::BT_COLOR | PlatformRenderer::BT_DEPTH | PlatformRenderer::BT_STENCIL;
	camera->Depth = 0;

	pChildObj->AddComponent(static_cast<FPCameraControllerComponent*>(new FPCameraControllerComponent(pChildObj)));




	/*
	pChildObj = new GameObject("Camera2");
	camera = new Camera(pChildObj);
	pChildObj->AddComponent(static_cast<Camera*>( camera ));
	pChildObj->mpTransform->SetParent(*mpGameObject->mpTransform);

	pChildObj->mpTransform->Position = Vector3(0,-0.2f,0.0f);
	camera->BackGroundColor = Color(Color::GRAY);
	camera->mAspectRatio = RenderEngine::GetInstance()->GetRenderConfig()->GetAspectRatio();
	camera->mFov = 45.0f;
	camera->mNear = 0.01f;
	camera->mFar = 10000.0f;
	camera->BuffersToClear = PlatformRenderer::BT_DEPTH;
	camera->Depth = 1;
	*/
	
	//LoadLua();
}

//-----------------------------------------------------------------------------------
void GameMain::OnUpdate()
{
	sprintf(fpsTextBuffer, "FPS: %d", Time::GetInstance()->GetFPS());
	fpsText->SetText( fpsTextBuffer );
}

//-----------------------------------------------------------------------------------
void GameMain::LoadLua()
{
	lua_State *pLuaState = luaL_newstate();

	luaopen_base(pLuaState);
	luaopen_string(pLuaState);
	luaopen_os(pLuaState);
	luaopen_io(pLuaState);
	luaopen_math(pLuaState);

	//lua_pushstring(pLuaState,"./assets/scripts/");
	//lua_setglobal(pLuaState, "LUA_PATH");
	
	lua_register(pLuaState, "test", LuaTest);
	luaL_dofile(pLuaState, "main.lua");
	lua_pcall(pLuaState,0,LUA_MULTRET,0);
	lua_close(pLuaState);

}