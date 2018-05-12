cmake_minimum_required(VERSION 3.5)

project( xdPixelEngine )

SET(GCC_COVERAGE_COMPILE_FLAGS "-v")

set(CPUArchitecture "x86" CACHE STRING "The CPU architecture to compile for.")
set_property (CACHE CPUArchitecture PROPERTY STRINGS x86 x64)

set(SRC src)
set(CORE_SRC src/core)
set(GAME_SRC src/game)
set(GRAPHICS_SRC src/graphics)
set(DX9_SRC src/graphics/gfxdevice/dx9)
set(OPENGL_SRC src/graphics/gfxdevice/opengl)
set(EXTERNAL_SRC src/external)

include_directories(${SRC})
include_directories(${EXTERNAL_SRC}/jsoncpp-src-0.5.0/include)
include_directories(${EXTERNAL_SRC}/zlib-1.2.11/)
include_directories(${EXTERNAL_SRC}/lpng162/)
include_directories(${EXTERNAL_SRC}/lua-5.2.2/src)
include_directories(${EXTERNAL_SRC}/glad/)
include_directories(${EXTERNAL_SRC}/)

file(GLOB src
    "${SRC}/*.h"
    "${SRC}/*.cpp"
    "${SRC}/*.c"
)

file(GLOB core_src
    "${CORE_SRC}/BaseObject.cpp"
    "${CORE_SRC}/BaseObject.h"
    "${CORE_SRC}/Camera.cpp"
    "${CORE_SRC}/Camera.h"
    "${CORE_SRC}/Engine.cpp"
    "${CORE_SRC}/Engine.h"
    "${CORE_SRC}/GameObject.cpp"
    "${CORE_SRC}/GameObject.h"
    "${CORE_SRC}/GameObjectComponent.cpp"
    "${CORE_SRC}/GameObjectComponent.h"
    "${CORE_SRC}/main.cpp"
    "${CORE_SRC}/platform.h"
    "${CORE_SRC}/Transform.cpp"
    "${CORE_SRC}/Transform.h"
    "${CORE_SRC}/config/EngineConfig.cpp"
    "${CORE_SRC}/config/EngineConfig.h"
    "${CORE_SRC}/GameObjectComponents/RenderComponent.cpp"
    "${CORE_SRC}/GameObjectComponents/RenderComponent.h"
    "${CORE_SRC}/input/Input.cpp"
    "${CORE_SRC}/input/Input.h"
    "${CORE_SRC}/input/Keycode.h"
    "${CORE_SRC}/math/MathHelper.cpp"
    "${CORE_SRC}/math/MathHelper.h"
    "${CORE_SRC}/math/Matrix4x4.cpp"
    "${CORE_SRC}/math/Matrix4x4.h"
    "${CORE_SRC}/math/Quaternion.cpp"
    "${CORE_SRC}/math/Quaternion.h"
    "${CORE_SRC}/math/Vector3.cpp"
    "${CORE_SRC}/math/Vector3.h"
    "${CORE_SRC}/math/Vector4.cpp"
    "${CORE_SRC}/math/Vector4.h"
    "${CORE_SRC}/mesh/Mesh.cpp"
    "${CORE_SRC}/mesh/Mesh.h"
    "${CORE_SRC}/resource/image_loaders/ImageLoader.cpp"
    "${CORE_SRC}/resource/image_loaders/ImageLoader.h"
    "${CORE_SRC}/resource/image_loaders/ImageLoader_PNG.cpp"
    "${CORE_SRC}/resource/image_loaders/ImageLoader_PNG.h"
    "${CORE_SRC}/resource/materialLoader/MaterialLoader.cpp"
    "${CORE_SRC}/resource/materialLoader/MaterialLoader.h"
    "${CORE_SRC}/resource/model_loaders/ObjLoader.cpp"
    "${CORE_SRC}/resource/model_loaders/ObjLoader.h"
    "${CORE_SRC}/resource/model_loaders/AbmData.cpp"
    "${CORE_SRC}/resource/model_loaders/AbmData.h"
    "${CORE_SRC}/resource/model_loaders/AbmLoader.cpp"
    "${CORE_SRC}/resource/model_loaders/AbmLoader.h"
    "${CORE_SRC}/resource/prefabLoader/PrefabLoader.cpp"
    "${CORE_SRC}/resource/prefabLoader/PrefabLoader.h"
    "${CORE_SRC}/resource/sceneLoader/SceneLoader.cpp"
    "${CORE_SRC}/resource/sceneLoader/SceneLoader.h"
    "${CORE_SRC}/resource/texture2d/DX9Texture2D.cpp"
    "${CORE_SRC}/resource/texture2d/DX9Texture2D.h"
    "${CORE_SRC}/resource/texture2d/OpenGLTexture2D.cpp"
    "${CORE_SRC}/resource/texture2d/OpenGLTexture2D.h"
    "${CORE_SRC}/resource/texture2d/Texture2D.cpp"
    "${CORE_SRC}/resource/texture2d/Texture2D.h"
    "${CORE_SRC}/time/Time.cpp"
    "${CORE_SRC}/time/Time.h"
)

file(GLOB game_src
    "${GAME_SRC}/AbmComponent.cpp"
    "${GAME_SRC}/AbmComponent.h"
    "${GAME_SRC}/AutoRotateComponent.cpp"
    "${GAME_SRC}/AutoRotateComponent.h"
    "${GAME_SRC}/FPCameraControllerComponent.cpp"
    "${GAME_SRC}/FPCameraControllerComponent.h"
    "${GAME_SRC}/FPSTextComponent.cpp"
    "${GAME_SRC}/FPSTextComponent.h"
    "${GAME_SRC}/FullScreenQuadComponent.cpp"
    "${GAME_SRC}/FullScreenQuadComponent.h"
    "${GAME_SRC}/GameMain.cpp"
    "${GAME_SRC}/GameMain.h"
    "${GAME_SRC}/MaterialComponent.cpp"
    "${GAME_SRC}/MaterialComponent.h"
    "${GAME_SRC}/MeshComponent.cpp"
    "${GAME_SRC}/MeshComponent.h"
    "${GAME_SRC}/MoverComponent.cpp"
    "${GAME_SRC}/MoverComponent.h"
    "${GAME_SRC}/ObjLoaderTestComponent.cpp"
    "${GAME_SRC}/ObjLoaderTestComponent.h"
    "${GAME_SRC}/PlaneShadowComponent.cpp"
    "${GAME_SRC}/PlaneShadowComponent.h"
    "${GAME_SRC}/RenderTestComponent.cpp"
    "${GAME_SRC}/RenderTestComponent.h"
    "${GAME_SRC}/TextComponent.cpp"
    "${GAME_SRC}/TextComponent.h"
    "${GAME_SRC}/TriangleComponent.cpp"
    "${GAME_SRC}/TriangleComponent.h"
)

file(GLOB graphics_src
    "${GRAPHICS_SRC}/BitmapText.cpp"
    "${GRAPHICS_SRC}/BitmapText.h"
    "${GRAPHICS_SRC}/Color.cpp"
    "${GRAPHICS_SRC}/Color.h"
    "${GRAPHICS_SRC}/DebugGfx.cpp"
    "${GRAPHICS_SRC}/DebugGfx.h"
    "${GRAPHICS_SRC}/Material.cpp"
    "${GRAPHICS_SRC}/Material.h"
    "${GRAPHICS_SRC}/PlatformRenderer.cpp"
    "${GRAPHICS_SRC}/PlatformRenderer.h"
    "${GRAPHICS_SRC}/RenderEngine.cpp"
    "${GRAPHICS_SRC}/RenderEngine.h"
    "${GRAPHICS_SRC}/RendererConfig.h"
    "${GRAPHICS_SRC}/shaders/ShaderPass.cpp"
    "${GRAPHICS_SRC}/shaders/ShaderPass.h"
    "${GRAPHICS_SRC}/shaders/ShaderProgram.cpp"
    "${GRAPHICS_SRC}/shaders/ShaderProgram.h"
    "${GRAPHICS_SRC}/shaders/ShaderTechnique.cpp"
    "${GRAPHICS_SRC}/shaders/ShaderTechnique.h"
)

file(GLOB dx9_src
    "${DX9_SRC}/DX9Renderer.cpp"
    "${DX9_SRC}/DX9Renderer.h"
)

file(GLOB opengl_src
    "${OPENGL_SRC}/OpenGLRenderer.cpp"
    "${OPENGL_SRC}/OpenGLRenderer.h"
)

file(GLOB external_src
    "${EXTERNAL_SRC}/*.h"
    "${EXTERNAL_SRC}/*.cpp"
    "${EXTERNAL_SRC}/*.c"

    "${EXTERNAL_SRC}/jsoncpp-src-0.5.0/src/lib_json/*.h"
    "${EXTERNAL_SRC}/jsoncpp-src-0.5.0/src/lib_json/*.c"
    "${EXTERNAL_SRC}/jsoncpp-src-0.5.0/src/lib_json/*.cpp"

    "${EXTERNAL_SRC}/zlib-1.2.11/*.h"
    "${EXTERNAL_SRC}/zlib-1.2.11/*.c"
    "${EXTERNAL_SRC}/zlib-1.2.11/*.cpp"

    "${EXTERNAL_SRC}/lpng162/*.h"
    "${EXTERNAL_SRC}/lpng162/*.c"
    "${EXTERNAL_SRC}/lpng162/*.cpp"

    "${EXTERNAL_SRC}/lua-5.2.2/src/*.h"
    "${EXTERNAL_SRC}/lua-5.2.2/src/*.c"
    "${EXTERNAL_SRC}/lua-5.2.2/src/*.cpp"

    "${EXTERNAL_SRC}/KHR/*.h"
    "${EXTERNAL_SRC}/KHR/*.c"
    "${EXTERNAL_SRC}/KHR/*.cpp"

    "${EXTERNAL_SRC}/glad/*.h"
    "${EXTERNAL_SRC}/glad/*.c"
    "${EXTERNAL_SRC}/glad/*.cpp"

    "${EXTERNAL_SRC}/khronos/gl/*.h"
    "${EXTERNAL_SRC}/khronos/gl/*.c"
    "${EXTERNAL_SRC}/khronos/gl/*.cpp"
)

get_filename_component(lua_lua_c ${EXTERNAL_SRC}/lua-5.2.2/src/lua.c ABSOLUTE)
list(REMOVE_ITEM external_src "${lua_lua_c}")

get_filename_component(libpng_example_c ${EXTERNAL_SRC}/lpng162/example.c ABSOLUTE)
list(REMOVE_ITEM external_src "${libpng_example_c}")
get_filename_component(libpng_pngtest_c ${EXTERNAL_SRC}/lpng162/pngtest.c ABSOLUTE)
list(REMOVE_ITEM external_src "${libpng_pngtest_c}")

source_group("src" FILES ${src})
source_group("core" FILES ${core_src})
source_group("game" FILES ${game_src})
source_group("graphics" FILES ${graphics_src})
source_group("graphics\\gfxdevice\\dx9" FILES ${dx9_src})
source_group("graphics\\gfxdevice\\opengl" FILES ${opengl_src})
source_group("external" FILES ${external_src})

list(SORT src)
list(SORT core_src)
list(SORT game_src)
list(SORT graphics_src)
list(SORT dx9_src)
list(SORT opengl_src)
list(SORT external_src)

if(${CPUArchitecture} MATCHES "x86")
    link_directories(src/external/directx/x86/)
    link_directories(src/external/windows_sdk/10.0.16299.0/um/x86)
else()
    link_directories(src/external/directx/x64/)
    link_directories(src/external/windows_sdk/10.0.16299.0/um/x64)
endif()

link_directories(src/external/cg/lib/)

# add the executable
add_executable(xdPixelEngine WIN32 ${main_src} ${core_src} ${game_src} ${graphics_src} ${dx9_src} ${opengl_src} ${external_src})

target_link_libraries(xdPixelEngine d3d9)
target_link_libraries(xdPixelEngine cg)
target_link_libraries(xdPixelEngine cgD3D9)
target_link_libraries(xdPixelEngine cgGL)
target_link_libraries(xdPixelEngine winMM)
target_link_libraries(xdPixelEngine OpenGL32)
target_link_libraries(xdPixelEngine GlU32)

# Set the Visual Studio debug working directory
set_target_properties(xdPixelEngine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(ProjectDir)/../")

# Set the Visual Studio default startup project to xdPixelEngine.
# https://stackoverflow.com/questions/7304625/how-do-i-change-the-startup-project-of-a-visual-studio-solution-via-cmake/37994396
#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT xdPixelEngine)
SET(CMAKE_DEFAULT_STARTUP_PROJECT xdPixelEngine)