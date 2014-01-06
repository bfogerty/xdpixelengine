#include "MaterialComponent.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "../core/input/Input.h"

#include "./resource/materialLoader/MaterialLoader.h"
#include "./resource/image_loaders/ImageLoader.h"
#include "./resource/model_loaders/ObjLoader.h"

#include "../core/math/Vector3.h"
#include "../core/math/Quaternion.h"
#include "../core/math/MathHelper.h"
#include "../renderer/Material.h"

//-----------------------------------------------------------------------------------
void MaterialComponent::OnAwake()
{
	this->mpGameObject->pMaterial = MaterialLoader::Load(this->materialFilePath.c_str());
}

