#include "PlaneShadowComponent.h"
#include "MeshComponent.h"
#include "MaterialComponent.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "../core/input/Input.h"

#include "./resource/image_loaders/ImageLoader.h"
#include "./resource/model_loaders/ObjLoader.h"

#include "../core/math/Vector3.h"
#include "../core/math/Quaternion.h"
#include "../core/math/MathHelper.h"
#include "../renderer/Material.h"

//-----------------------------------------------------------------------------------
void PlaneShadowComponent::OnAwake()
{
	shadowGameObject = new GameObject("Shadow");
	shadowGameObject->AddComponent(new MeshComponent(shadowGameObject, this->modelPath));
	shadowGameObject->AddComponent( new MaterialComponent(shadowGameObject, this->shaderPath) );
	shadowGameObject->SetLayer( this->mpGameObject->GetLayer() );

	shadowGameObject->mpTransform->Scale = mpGameObject->mpTransform->Scale;
	shadowGameObject->mpTransform->Position = mpGameObject->mpTransform->Position;
	shadowGameObject->mpTransform->Rotation = mpGameObject->mpTransform->Rotation;
	shadowGameObject->mpTransform->Update();

	this->mpGameObject->mpTransform->mChildren.push_back(shadowGameObject->mpTransform);

}


//-----------------------------------------------------------------------------------
void PlaneShadowComponent::OnUpdate()
{
	shadowGameObject->mpTransform->Scale = mpGameObject->mpTransform->Scale;
	shadowGameObject->mpTransform->Position = mpGameObject->mpTransform->Position;
	shadowGameObject->mpTransform->Rotation = mpGameObject->mpTransform->Rotation;
}