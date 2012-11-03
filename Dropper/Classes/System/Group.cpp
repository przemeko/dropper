//
//  Group.cpp
//  Dropper
//
//  Created by Przemek on 21.10.2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "cocos2d.h"
#include "Group.h"

Group::Group()
{
    this->entities = new CCMutableArray<Entity *>();
}

void Group::add(Entity *entity)
{
    this->entities->addObject(entity);
    this->entitiesNum = this->entities->count();
}

CCMutableArray<Entity *> *Group::get()
{
    return this->entities;
}

void Group::update(ccTime dt)
{
    for (i=0; i<this->entitiesNum; i++) {
        this->entity = this->entities->getObjectAtIndex(i);
        this->entity->physics->update(dt);
    }
}

bool Group::isCollide(unsigned int entityIndex, CCNode *node)
{
    pos1 = node->getPosition();
    pos2 = this->entities->getObjectAtIndex(entityIndex)->getPosition();
    
    if (fabs(pos1.x - pos2.x) <= 16 && fabs(pos1.y - pos2.y) <= 16) {
        return true;
    }
    
    return false;
}

unsigned int Group::count()
{
    return this->entitiesNum;
}

void Group::cleanup()
{
    this->entities->release();
    delete this->entity;
}
