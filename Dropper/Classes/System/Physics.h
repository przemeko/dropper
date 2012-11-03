//
//  Physics.h
//  Dropper
//
//  Created by Przemek on 21.10.2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Dropper_Physics_h
#define Dropper_Physics_h
#include "cocos2d.h"

using namespace cocos2d;

class Physics
{
private:
    CCNode *node;
    CCPoint position, shift, position2;
public:
    // wektor predkosci
    CCPoint v;
    // wektor przyspieszenia
    CCPoint a;
    // czy zastosowac nowo wyliczone polozenie do pozycji powiazanego node'a
    bool isEnabledImpactOfNodePosition;
    
    Physics(CCNode *node);
    bool isCollideWith(CCNode *node);
    void jump(float vy);
    void thrust(CCPoint vect);
    void update(ccTime dt);
    CCPoint getCalculatedPosition();
    CCPoint getCalculatedShift();
    void cleanup();
    

    
    

};

#endif
