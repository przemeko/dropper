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
    this->setIsAccelerometerEnabled(true);
    
    winSize = CCDirector::sharedDirector()->getWinSize();
	
    initHero();
    initBlocks();
    initGems();
    scheduleUpdate();
    
    CCLog("!!! ___ Dropper test ___");
    
	return true;
}
void HelloWorld::initHero()
{
    this->isCollide = false;
    this->velocity = ccp(0,-10);
    this->hero = CCSprite::spriteWithFile("front2.png");
    this->addChild(this->hero);
    this->hero->setPosition(ccp(winSize.width/2,winSize.height));
    
    this->lastBlockContact = 0;
    this->currentBlockContact = 0;
    this->jumpsNum = 0;
}

void HelloWorld::initBlocks()
{
    this->nextBlockIndex = 0;
    this->blocksNum = 50;
    this->blocks = new CCMutableArray<CCSprite *>();
    
    this->blockBatchNode = CCSpriteBatchNode::batchNodeWithFile("block2.png");
    this->addChild(this->blockBatchNode);
    
    for (int i =0; i<this->blocksNum; i++) {
        block = CCSprite::spriteWithTexture(this->blockBatchNode->getTexture());
        block->setIsVisible(false);
        
        this->blocks->addObject(this->block);
        this->blockBatchNode->addChild(block);
    } 
}

void HelloWorld::initGems()
{
    this->gemsNum = 20;
    this->gems = new CCMutableArray<CCSprite *>();
    
    CCSpriteBatchNode* gemsBatchNode = CCSpriteBatchNode::batchNodeWithFile("coin2.png");
    this->addChild(gemsBatchNode);

    for (int i =0; i<this->gemsNum; i++) {
        block = CCSprite::spriteWithTexture(gemsBatchNode->getTexture());
        block->setIsVisible(true);
        block->setPosition(ccp(winSize.width*CCRANDOM_0_1(), (winSize.height-50)*CCRANDOM_0_1()));
        this->gems->addObject(block);
        gemsBatchNode->addChild(block);
    } 
    
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

void HelloWorld::didAccelerate(CCAcceleration *pAccelerationValue)
{
	velocity.x = pAccelerationValue->x * 60.0f;
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
            CCLog("jumpsNum %d, %d", jumpsNum, i);
            if (currentBlockContact == i) {
                jumpsNum++;
            }
            else {
                jumpsNum = 0;
            }
            
            if (jumpsNum >= 3) {
                velocity.y = -100; // impact
                jumpsNum = 0;
            }else {
                velocity.y = -50; // impact
            }
            
            velocity.x = 0;
            currentBlockContact = i;
            break;
        }
    }
    
    for (int i = 0; i<this->gemsNum; i++) {
        block = this->gems->getObjectAtIndex(i);
        if (block->getIsVisible()) {
            blockPosition = block->getPosition();
            if (fabs(position.x - blockPosition.x) <= 16 && fabs(position.y - blockPosition.y) <= 16) {
                block->setIsVisible(false);
            }
        }
        
    }
    
    if (position.y <= 0) {
        velocity.y = -50; // impact
        velocity.x = 0;
    }
    
    velocity.y -= -2.0f;
    position.x += velocity.x*dt;
    position.y -= velocity.y*dt;
    
    // add velocity boundry
    if (velocity.y < -50) {
        //velocity.y = -50;
    }
    
    hero->setPosition(position);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
