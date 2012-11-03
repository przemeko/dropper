//
//  Group.h
//  Dropper
//
//  Created by Przemek on 21.10.2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Dropper_Group_h
#define Dropper_Group_h

#include "cocos2d.h"
#include "Entity.h"

using namespace cocos2d;

class Group
{
private:
    CCMutableArray<Entity *> *entities;
    Entity *entity;
    unsigned int entitiesNum;
    unsigned int i;
    CCPoint pos1,pos2;
    
public:
    Group();
    void add(Entity *entity);
    CCMutableArray<Entity *> *get();
    void update(ccTime dt);
    bool isCollide(unsigned int entityIndex, CCNode *node);
    unsigned int count();
    void cleanup();
};

#endif
