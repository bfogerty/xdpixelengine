#include "FullScreenQuadComponent.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/time/Time.h"
#include "core/resource/image_loaders/ImageLoader.h"

#include "core/math/Vector3.h"
#include "core/math/Quaternion.h"
#include "core/math/MathHelper.h"

//-----------------------------------------------------------------------------------
void FullScreenQuadComponent::OnAwake()
{
	GameObject *quad = GameObject::CreatePrimitive(GameObject::FullScreenQuad);
	quad->mpTransform->Position = Vector3(0,-10000,0);

	this->mpGameObject->mMesh->Clone(quad->mMesh);
	this->mpGameObject->mpTransform->Position = Vector3(0,0,0);
}
