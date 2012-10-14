#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    this->setIsTouchEnabled(true);
    
    winSize = CCDirector::sharedDirector()->getWinSize();
	
    this->isCollide = false;
    this->velocity = ccp(0,-10);
    this->hero = CCSprite::spriteWithFile("front2.png");
    this->addChild(this->hero);
    this->hero->setPosition(ccp(winSize.width/2,winSize.height));
    
    this->blockBatchNode = CCSpriteBatchNode::batchNodeWithFile("block2.png");
    this->addChild(this->blockBatchNode);
    
    this->nextBlockIndex = 0;
    this->blocksNum = 10;
    this->blocks = new CCMutableArray<CCSprite *>();
    
    for (int i =0; i<this->blocksNum; i++) {
        block = CCSprite::spriteWithTexture(this->blockBatchNode->getTexture());
        block->setIsVisible(false);
        
        this->blocks->addObject(this->block);
        this->blockBatchNode->addChild(block);
    }

    scheduleUpdate();
	return true;
}

void HelloWorld::ccTouchesEnded(CCSet *touches, CCEvent *event)
{
    CCSetIterator iterator;
    CCTouch *touch;
    iterator = touches->begin();
    
    touch = (CCTouch*)(*iterator);
    
    if (touch) {
        CCPoint location = touch->locationInView(touch->view());
        location = CCDirector::sharedDirector()->convertToGL(location);
        addBlock(location);
    }

}

void HelloWorld::addBlock(CCPoint location)
{
    if (this->nextBlockIndex >= this->blocksNum) {
        return;
    }
    
    block = this->blocks->getObjectAtIndex(this->nextBlockIndex++);
    block->setPosition(location);
    block->setIsVisible(true);
}

void HelloWorld::update(ccTime dt)
{
    position = hero->getPosition();
    
    for (int i = 0; i<this->nextBlockIndex; i++) {
        block = this->blocks->getObjectAtIndex(i);
        blockPosition = block->getPosition();
        isCollide = false;
        
        if (fabs(position.x - blockPosition.x) <= 16 && fabs(position.y - blockPosition.y) <= 16) {
            isCollide = true;
            velocity.y = -50;
            break;
        }
    }
    
    velocity.y -= -1;
    position.y -= velocity.y*dt;
    
    hero->setPosition(position);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
