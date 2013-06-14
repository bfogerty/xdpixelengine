#include "GameMain.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"

#include "../game/RenderTestComponent.h"
#include "../game/TriangleComponent.h"

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
		OutputDebugStr(lua_tostring(pLuaState, i));
		OutputDebugStr("\n");
	}

	return 0;
}

//-----------------------------------------------------------------------------------
void GameMain::OnAwake()
{
	// The root should always be at the center of the world.
	mpGameObject->mpTransform->mMatWorld.Translate(Vector3(0.0f, 0.0f, 0.0f));

	// Add Game Specific logic below.
	GameObject *pGameObject = new GameObject("RenderTest0");
	pGameObject->AddComponent( static_cast<GameObjectComponent*>( new TriangleComponent(pGameObject) ) );
	mpGameObject->mpTransform->mChildren.push_back(pGameObject->mpTransform);
	

	pGameObject = new GameObject("RenderTest1");
	pGameObject->AddComponent( static_cast<GameObjectComponent*>( new RenderTestComponent(pGameObject) ) );
	mpGameObject->mpTransform->mChildren.push_back(pGameObject->mpTransform);
	
	pGameObject = new GameObject("RenderTest2");
	pGameObject->AddComponent( static_cast<GameObjectComponent*>( new RenderTestComponent(pGameObject) ) );
	mpGameObject->mpTransform->mChildren.push_back(pGameObject->mpTransform);
	
	LoadLua();
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