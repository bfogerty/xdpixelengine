#include "GameMain.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/Camera.h"
#include "../core/time/Time.h"

#include "../renderer/RenderEngine.h"
#include "../renderer/RendererConfig.h"

#include "../game/RenderTestComponent.h"
#include "../game/TriangleComponent.h"
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
	
	GameObject *pChildObj = new GameObject("RenderTest0");
	pChildObj->AddComponent( static_cast<GameObjectComponent*>( new ObjLoaderTestComponent(pChildObj) ) );
	mpGameObject->mpTransform->mChildren.push_back(pChildObj->mpTransform);
	

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

	pChildObj->mpTransform->Position = Vector3(0,0.2f,-0.2f);
	camera->BackGroundColor = Color(Color::GRAY);
	camera->mAspectRatio = RenderEngine::GetInstance()->GetRenderConfig()->GetAspectRatio();
	camera->mFov = 45.0f;
	camera->mNear = 0.01f;
	camera->mFar = 10000.0f;

	pChildObj->AddComponent(static_cast<FPCameraControllerComponent*>(new FPCameraControllerComponent(pChildObj)));
	
	//LoadLua();
}

//-----------------------------------------------------------------------------------
void GameMain::OnUpdate()
{
	
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