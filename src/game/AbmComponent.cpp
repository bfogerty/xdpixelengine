#include "game/AbmComponent.h"
#include "game/TextComponent.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/time/Time.h"
#include "core/input/Input.h"

#include "core/resource/materialLoader/MaterialLoader.h"
#include "core/resource/image_loaders/ImageLoader.h"
#include "core/resource/model_loaders/ObjLoader.h"
#include "core/resource/model_loaders/AbmLoader.h"
#include "core/resource/model_loaders/AbmData.h"

#include "core/math/Vector3.h"
#include "core/math/Quaternion.h"
#include "core/math/MathHelper.h"
#include "renderer/Material.h"

#include "renderer/DebugGfx.h"

//-----------------------------------------------------------------------------------
void AbmComponent::OnAwake()
{
	currentClip = 0;
	currentClipIndex = 0;
	currentFrameIndex = 0;
	tVal = 0.00f;

	paused = FALSE;
	showNormals = FALSE;

	std::map<std::string, std::string> mapParams;
	mapParams["characterwidth"] = "9";
	mapParams["characterheight"] = "9";
	mapParams["characterscale"] = "0.02";
	mapParams["kerning"] = "0.020";
	mapParams["spaceBetweenCharacters"] = "0.020";

	GameObject *textObject = new GameObject("AnimationName");
	textObject->pMaterial = MaterialLoader::Load("./assets/materials/text.txt");
	textComponent = (TextComponent*) TextComponent::Create(textObject, mapParams);
	textComponent->SetText("");
	mpGameObject->mpTransform->mChildren.push_back(textObject->mpTransform);
	textObject->mpTransform->position = Vector3(2.50f ,9.2f ,-1.00f);
	textObject->mpTransform->scale = Vector3(10, 10, 10);
	textObject->Layer = 2;

	Mesh *mesh = mpGameObject->mMesh = new Mesh();

	abmData = AbmLoader::Load(this->modelPath.c_str());

	mesh->normals.resize(abmData->NumberOfVerticies);
	for(vector<Vector3*>::iterator it = mesh->normals.begin(); it != mesh->normals.end(); ++it )
	{
		*it = new Vector3();
	}

	for(int i=0; i < abmData->NumberOfTextureCoordinates; ++i)
	{
		mesh->uvs.push_back( &abmData->TextureCoordinates[i].UV );
	}

	for(vector<AbmTriangle>::iterator it = abmData->Triangles.begin(); it != abmData->Triangles.end(); ++it )
	{

		short x = it->VertexIndicies[0];
		short y = it->VertexIndicies[1];
		short z = it->VertexIndicies[2];

		short u = it->TextureCoordinateIndicies[0];
		short v = it->TextureCoordinateIndicies[1];
		short w = it->TextureCoordinateIndicies[2];

		Face *face0 = new Face(	x, 
								x, 
								0,
								u );

		Face *face1 = new Face(	y, 
								y, 
								0,
								v );

		Face *face2 = new Face(	z, 
								z, 
								0,
								w );

		mesh->triangles.push_back( face0 );
		mesh->triangles.push_back( face1 );
		mesh->triangles.push_back( face2 );
	}

	mesh->verticies.resize(abmData->NumberOfVerticies);
	for(vector<Vector3>::iterator it = mesh->verticies.begin(); it != mesh->verticies.end(); ++it )
	{
		*it = Vector3();
	}


	PlayClip(abmData->ClipNames[currentClipIndex].c_str());
}

//-----------------------------------------------------------------------------------
void AbmComponent::PlayClip(string clipName)
{
	for(int clipIndex=0; clipIndex < abmData->NumberOfClips; ++clipIndex)
	{
		AbmClipData clipData = abmData->Clips[clipIndex];
		if( clipName == clipData.ClipName )
		{
			currentClip = &clipData;
			currentClipIndex = clipIndex;
			currentFrameIndex = 0;
			tVal = 0.00f;

			textComponent->SetText(clipName);
			return;
		}
	}
}

//-----------------------------------------------------------------------------------
void AbmComponent::PlayClip( int clipIndex )
{
	if( currentClipIndex >= abmData->NumberOfClips )
	{
		currentClipIndex = 0;
	}
	else if( currentClipIndex < 0 )
	{
		currentClipIndex = abmData->NumberOfClips-1;
	}

	PlayClip(abmData->ClipNames[currentClipIndex].c_str());
}

//-----------------------------------------------------------------------------------
void AbmComponent::OnUpdate()
{
	if( currentClip < 0 )
	{
		return;
	}

	/*
	float unit = 1.0f;
	DebugGfx::DrawLine(Vector3(0,0,0), Vector3(unit,0,0), Color::RED);
	DebugGfx::DrawLine(Vector3(0,0,0), Vector3(0,unit,0), Color::GREEN);
	DebugGfx::DrawLine(Vector3(0,0,0), Vector3(0,0,unit), Color::BLUE);
	*/

	if( Input::Inst()->GeyKeyDown( KeyCode::N ) )
	{
		PlayClip(++currentClipIndex);
	}
	else if( Input::Inst()->GeyKeyDown( KeyCode::B ) )
	{
		PlayClip(--currentClipIndex);
	}

	if( Input::Inst()->GeyKeyDown( KeyCode::P ) )
	{
		if( paused )
		{
			paused = FALSE;
		}
		else
		{
			paused = TRUE;
		}
	}

	if( Input::Inst()->GeyKeyDown( KeyCode::H ) )
	{
		if( showNormals )
		{
			showNormals = FALSE;
		}
		else
		{
			showNormals = TRUE;
		}
	}

	AbmClipData *currentClip = &abmData->Clips[currentClipIndex];
	int totalFramesInClip = abmData->Clips[currentClipIndex].FrameCount;

	Mesh *mesh = mpGameObject->mMesh;

	for(int i=0; i<abmData->NumberOfVerticies; ++i)
	{
		Vector3 start = currentClip->Frames[currentFrameIndex].Verticies[i];
		Vector3 nStart = currentClip->Frames[currentFrameIndex].Normals[i];

		Vector3 end;
		Vector3 nEnd;
		if( currentFrameIndex+1 < totalFramesInClip )
		{
			end = currentClip->Frames[currentFrameIndex+1].Verticies[i];
			nEnd = currentClip->Frames[currentFrameIndex+1].Normals[i];
		}
		else
		{
			end = currentClip->Frames[0].Verticies[i];
			nEnd = currentClip->Frames[0].Normals[i];
		}

		if( tVal > 1.00f )
		{
			tVal = 1.00f;
		}

		Vector3 newPos = start*(1.00f-tVal) + (end*tVal);
		Vector3 newNormal = nStart*(1.00f-tVal) + (nEnd*tVal);

		if( !paused )
		{
			float dt = Time::GetInstance()->GetDeltaTime();
			tVal += ( dt * (1.0f/ (1000.0f/currentClip->FramesPerSecond)));
		}

		mesh->verticies[i].Set(newPos.x(),newPos.y(),newPos.z());

		newNormal.Normalize();
		float dist = newNormal.Magnitude();
		newNormal = newNormal * 1.000f;
		mesh->normals[i]->Set(newNormal.x(),newNormal.y(),newNormal.z());

		if( showNormals )
		{
			Vector4 start4 = this->mpGameObject->mpTransform->worldMatrix * Vector4(newPos.x(),newPos.y(),newPos.z(),1.0f);
			Vector4 normal4 = this->mpGameObject->mpTransform->worldMatrix * Vector4(newNormal.x(),newNormal.y(),newNormal.z(),1.0f);

			Vector3 startP = Vector3(start4.x(), start4.y(), start4.z());
			Vector3 nP = Vector3(normal4.x(), normal4.y(), normal4.z());

			Vector3 endP = startP + (nP * 1.50f);

			float r = Vector3::Dot(nP, Vector3::Right());
			float u = Vector3::Dot(nP, Vector3::Up());
			float f = Vector3::Dot(nP, Vector3::Forward());
			Color c(r*255, u*255, f*255);
			DebugGfx::DrawLine(startP, endP, c);
		}

	}

	//DrawAABB();
	
	if( tVal >= 1.00f )
	{
		++currentFrameIndex;
		if( currentFrameIndex >= totalFramesInClip )
		{
			currentFrameIndex = 0;
		}

		tVal = 0.00f;
	}
	

	mesh->Build();
}

//-----------------------------------------------------------------------------------
void AbmComponent::DrawAABB()
{
	Vector3 minExt(-0.5,-1,-1);
	Vector3 maxExt(0.5,1,1);

	Vector3 origin = mpGameObject->mpTransform->position;
	Vector3 up = Vector3::Up();
	Vector3 fwd = Vector3::Forward();
	Vector3 right = Vector3::Right();

	Vector3 frontLeft = origin + (fwd*maxExt.z()) + (right*minExt.x());
	Vector3 backLeft = origin + (fwd*minExt.z()) + (right*minExt.x());

	Vector3 frontRight = origin + (fwd*maxExt.z()) + (right*maxExt.x());
	Vector3 backRight = origin + (fwd*minExt.z()) + (right*maxExt.x());

	Vector3 bfl = frontLeft+(up*minExt.y());
	Vector3 tfl = frontLeft+(up*maxExt.y());
	Vector3 bbl = backLeft+(up*minExt.y());
	Vector3 tbl = backLeft+(up*maxExt.y());

	Vector3 bfr = frontRight+(up*minExt.y());
	Vector3 tfr = frontRight+(up*maxExt.y());
	Vector3 bbr = backRight+(up*minExt.y());
	Vector3 tbr = backRight+(up*maxExt.y());

	DebugGfx::DrawLine(bfl, tfl, Color(Color::GREEN));
	DebugGfx::DrawLine(bbl, tbl, Color(Color::GREEN));
	DebugGfx::DrawLine(bfr, tfr, Color(Color::GREEN));
	DebugGfx::DrawLine(bbr, tbr, Color(Color::GREEN));

	DebugGfx::DrawLine(tfl, tfr, Color(Color::GREEN));
	DebugGfx::DrawLine(bfl, bfr, Color(Color::GREEN));

	DebugGfx::DrawLine(tbl, tbr, Color(Color::GREEN));
	DebugGfx::DrawLine(bbl, bbr, Color(Color::GREEN));

	DebugGfx::DrawLine(tfl, tbl, Color(Color::GREEN));
	DebugGfx::DrawLine(bfl, bbl, Color(Color::GREEN));

	DebugGfx::DrawLine(tfr, tbr, Color(Color::GREEN));
	DebugGfx::DrawLine(bfr, bbr, Color(Color::GREEN));
}