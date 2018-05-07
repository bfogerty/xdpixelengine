#include "core/config/EngineConfig.h"
#include "GameMain.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/Camera.h"
#include "core/time/Time.h"
#include "core/resource/sceneLoader/SceneLoader.h"
#include "core/resource/prefabLoader/PrefabLoader.h"
#include "core/resource/materialLoader/MaterialLoader.h"

#include "renderer/RenderEngine.h"
#include "renderer/RendererConfig.h"
#include "renderer/PlatformRenderer.h"

#include "game/RenderTestComponent.h"
#include "game/TriangleComponent.h"
#include "game/TextComponent.h"
#include "game/ObjLoaderTestComponent.h"
#include "game/FPCameraControllerComponent.h"

extern "C"
{
#include "external/lua-5.2.2/src/lua.h"
#include "external/lua-5.2.2/src/lualib.h"
#include "external/lua-5.2.2/src/lauxlib.h"
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
	mpGameObject->mpTransform->worldMatrix.Translate(Vector3(0.0f, 0.0f, 0.0f));

	GameObject *pChildObj = new GameObject("Empty");

	SceneLoader::Load( EngineConfig::startScene->filename.c_str() , mpGameObject);
}

//-----------------------------------------------------------------------------------
void GameMain::OnUpdate()
{
	//sprintf(fpsTextBuffer, "FPS: %d", Time::GetInstance()->GetFPS());
	//fpsText->SetText( fpsTextBuffer );
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