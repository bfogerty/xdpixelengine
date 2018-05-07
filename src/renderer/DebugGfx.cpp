#include "renderer/DebugGfx.h"
#include "renderer/RenderEngine.h"
#include "renderer/PlatformRenderer.h"
#include "core/GameObject.h"
#include "core/Transform.h"

vector<DebugGfxLine> DebugGfx::lineList;
GameObject* DebugGfx::rootObject;

//-----------------------------------------------------------------------------------
void DebugGfx::Initialize(GameObject *root)
{
	rootObject = root;
}

//-----------------------------------------------------------------------------------
void DebugGfx::Reset()
{
	lineList.clear();
}

//-----------------------------------------------------------------------------------
void DebugGfx::Render(PlatformRenderer *platformRenderer)
{
	for(vector<DebugGfxLine>::iterator it = lineList.begin(); it != lineList.end(); ++it)
	{
		DebugGfxLine line = *it;

		platformRenderer->SetTransform(PlatformRenderer::TS_WORLD, rootObject->mpTransform->worldMatrix);

		platformRenderer->DrawDebugLine(&it->start, &it->end, &it->color);
	}
}

//-----------------------------------------------------------------------------------
void DebugGfx::DrawLine(Vector3 start, Vector3 end, Color color)
{
	lineList.push_back(DebugGfxLine(start,end,color));
}