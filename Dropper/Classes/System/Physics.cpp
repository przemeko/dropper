//
//  Physics.cpp
//  Dropper
//
//  Created by Przemek on 21.10.2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Physics.h"

Physics::Physics(CCNode *node)
{
    this->node = node;
    this->isEnabledImpactOfNodePosition = true;
}

void Physics::update(ccTime dt)
{
    this->v.x += this->a.x;
    this->v.y -= this->a.y;
    
    this->shift.x = this->v.x*dt;
    this->shift.y = this->v.y*dt;
    
    this->position = this->node->getPosition();
    this->position.x += this->shift.x;
    this->position.y -= this->shift.y;
    
    if (this->isEnabledImpactOfNodePosition) {
        this->node->setPosition(this->position);
    }
}

CCPoint Physics::getCalculatedPosition()
{
    return this->position;
}

CCPoint Physics::getCalculatedShift()
{
    return this->shift;
}

bool Physics::isCollideWith(CCNode *colliderNode)
{
    this->position = this->node->getPosition();
    this->position2 = colliderNode->getPosition();
    
    if (fabs(this->position.x - this->position2.x) <= 16 && fabs(this->position.y - this->position2.y) <= 16) {
        //CCLog("pos1.x: %f pos1.y: %f pos2.x: %f pos2.y: %f", this->position.x, this->position.y, this->position2.x, this->position2.y);
        return true;
    }
    
    return false;
}

void Physics::jump(float vy) {
    this->v.y = vy;
    //this->thrust(CCPointMake(0, vy));
}

void Physics::thrust(CCPoint vect) {
    this->v.x = vect.x;
    this->v.y = vect.y;
}
