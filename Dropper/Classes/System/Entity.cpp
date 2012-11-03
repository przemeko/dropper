//
//  Enemy.cpp
//  Dropper
//
//  Created by Przemek on 21.10.2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Entity.h"
#include "cocos2d.h"
#include "Physics.h"

Entity::Entity(const char *fileName)
{
    this->node = CCSprite::spriteWithFile(fileName);
    this->physics = new Physics(this->node);
    
}
