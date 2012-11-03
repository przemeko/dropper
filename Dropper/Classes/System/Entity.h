//
//  Enemy.h
//  Dropper
//
//  Created by Przemek on 21.10.2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Dropper_Actor_h
#define Dropper_Actor_h

#import "cocos2d.h"
#import "Physics.h"

using namespace cocos2d;

class Entity : public CCNode
{


public:
    Entity(const char *fileName);
    
    void init();
    CCSprite *node;
    Physics *physics;
    
};

#endif
