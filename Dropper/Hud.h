//
//  Hud.h
//  Dropper
//
//  Created by Przemek on 20.10.2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef Dropper_Hud_h
#define Dropper_Hud_h

#import "cocos2d.h"

using namespace cocos2d;

class Hud : public CCLayer {
private:
    int points;
    CCLabelTTF *pointsLabel;
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  	
    
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(Hud);
    
    void addPoints(int value);
};

#endif
