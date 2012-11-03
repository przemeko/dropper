//
//  Hud.cpp
//  Dropper
//
//  Created by Przemek on 20.10.2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Hud.h"
using namespace cocos2d;


// on "init" you need to initialize your instance
bool Hud::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    points = 0;
    
    this->pointsLabel = CCLabelTTF::labelWithString("points:0", "Arial", 12);
    this->pointsLabel->setPosition(ccp(winSize.width/2, winSize.height - 10));
    this->addChild(pointsLabel);
    
    // display info about compilation time
    /*
    time_t pt;
    time (&pt);
    char* tm= ctime (&pt);
    sprintf(tm, "%s", tm);
    CCLabelTTF * label = CCLabelTTF::labelWithString(tm, "Arial", 10);
    label->setPosition(ccp(winSize.width/2, winSize.height - 10));
    this->addChild(label);
    */
    
    return true;
}

void Hud::addPoints(int value)
{
    points += value;
    
    char ch[12] = {0};
    sprintf(ch, "points: %d", points);
    
    this->pointsLabel->setString(ch);
}

