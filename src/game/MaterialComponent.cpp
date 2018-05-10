#include "game/MaterialComponent.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/time/Time.h"
#include "core/input/Input.h"

#include "core/resource/materialLoader/MaterialLoader.h"
#include "core/resource/image_loaders/ImageLoader.h"
#include "core/resource/model_loaders/ObjLoader.h"

#include "core/math/Vector3.h"
#include "core/math/Quaternion.h"
#include "core/math/MathHelper.h"
#include "graphics/Material.h"

//-----------------------------------------------------------------------------------
void MaterialComponent::OnAwake()
{
	this->mpGameObject->pMaterial = MaterialLoader::Load(this->materialFilePath.c_str());
}

