#ifndef __TRIANGLE_COMPONENT__
#define __TRIANGLE_COMPONENT__
#include "GameObjectComponent.h"

class TriangleComponent : public GameObjectComponent
{
public:

        TriangleComponent( GameObject *pGameObject ) : GameObjectComponent(pGameObject)
        {

        }

        virtual void OnAwake();
        virtual void OnUpdate();

protected:

        float mft;
        char mDir;

};

#endif