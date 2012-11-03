#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Hud.h"
#include "Group.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::CCLayer
{
private:
    Group *flies;
    Group *platforms;
    Group *gems;
    Entity * hero;
    
    CCNode *gameSpaceNode;
    Entity *entity;
    CCSize winSize;
    
    CCPoint position;
    CCPoint velocity;
    
    CCSize gameSpaceSize;
    
    int lastBlockContact;
    int currentBlockContact;
    unsigned int jumpsNum;
    
    CCPoint blockPosition;
    CCMutableArray<CCSprite *> *blocks;
    unsigned int blocksNum;
    CCSpriteBatchNode *blockBatchNode;
    int nextBlockIndex;
    
    CCMutableArray<CCSprite *> *enemies;
    unsigned int enemiesNum;
    CCPoint enemyPosition;
    
    bool isCollide;
    CCSprite *block;
    
    Hud *hud;
    
    void initHero();
    void initPlatforms();
    void initGems();
    void initEnemies();
    void initDebug();
    void clean();
    
    void didAccelerate(CCAcceleration* pAccelerationValue);
    void ccTouchesEnded(CCSet *touches, CCEvent *event);
    virtual void keyBackClicked();
    void update(ccTime dt);
    void addPlatform(CCPoint location);
    
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
    virtual void onEnter();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
