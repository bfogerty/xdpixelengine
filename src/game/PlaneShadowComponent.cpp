#include "game/PlaneShadowComponent.h"
#include "game/MeshComponent.h"
#include "game/MaterialComponent.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/time/Time.h"
#include "core/input/Input.h"

#include "core/resource/image_loaders/ImageLoader.h"
#include "core/resource/model_loaders/ObjLoader.h"

#include "core/math/Vector3.h"
#include "core/math/Quaternion.h"
#include "core/math/MathHelper.h"
#include "renderer/Material.h"

//-----------------------------------------------------------------------------------
void PlaneShadowComponent::OnAwake()
{
	shadowGameObject = new GameObject("Shadow");
	//shadowGameObject->AddComponent(new MeshComponent(shadowGameObject, this->modelPath));
	shadowGameObject->AddComponent( new MaterialComponent(shadowGameObject, this->shaderPath) );
	shadowGameObject->SetLayer( this->mpGameObject->GetLayer() );

	shadowGameObject->mpTransform->scale = mpGameObject->mpTransform->scale;
	shadowGameObject->mpTransform->position = mpGameObject->mpTransform->position;
	shadowGameObject->mpTransform->rotation = mpGameObject->mpTransform->rotation;
	shadowGameObject->mpTransform->Update();

	this->mpGameObject->mpTransform->mChildren.push_back(shadowGameObject->mpTransform);

}


//-----------------------------------------------------------------------------------
void PlaneShadowComponent::OnUpdate()
{
	if (gameObjectReference == NULL)
	{
		return;
	}

	shadowGameObject->mMesh->Clone(gameObjectReference->mMesh);

	shadowGameObject->mpTransform->scale = mpGameObject->mpTransform->scale;
	shadowGameObject->mpTransform->position = mpGameObject->mpTransform->position;
	shadowGameObject->mpTransform->rotation = mpGameObject->mpTransform->rotation;
}