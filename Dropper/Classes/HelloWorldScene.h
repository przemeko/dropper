#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
private:
    CCSize winSize;
    
    CCSprite * hero;
    CCPoint position;
    CCPoint velocity;
    
    int lastBlockContact;
    int currentBlockContact;
    unsigned int jumpsNum;
    
    CCMutableArray<CCSprite *> *gems;
    unsigned int gemsNum;
    
    CCPoint blockPosition;
    CCMutableArray<CCSprite *> *blocks;
    unsigned int blocksNum;
    CCSpriteBatchNode *blockBatchNode;
    int nextBlockIndex;
    
    bool isCollide;
    CCSprite *block;
    
    void initHero();
    void initBlocks();
    void initGems();
    
    void didAccelerate(CCAcceleration* pAccelerationValue);
    void ccTouchesEnded(CCSet *touches, CCEvent *event);
    void update(ccTime dt);
    void addBlock(CCPoint location);
    
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
