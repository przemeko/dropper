#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Hud.h"
#include "Entity.h"

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
    this->setIsKeypadEnabled(true);
    
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    hud = Hud::node();
    this->addChild(hud);
    
    gameSpaceSize.width = 600;
    gameSpaceSize.height = 800;
    gameSpaceNode = CCNode::node();
    addChild(gameSpaceNode);
    
    //asasx
    //gameSpaceNode->setPosition(ccp(10, -100));
    initHero();
    initPlatforms();
    initGems();
    initEnemies();
    //initDebug();
    scheduleUpdate();
    
	return true;
}

void HelloWorld::onEnter()
{
    CCLayer::onEnter();
}

void HelloWorld::initHero()
{
    this->hero = new Entity("front2.png");
    this->hero->physics->a.y = -1.2f;
    this->hero->node->setPosition(ccp(winSize.width/2,winSize.height/2));
    gameSpaceNode->addChild(hero->node);
    //this->addChild(this->hero->node);
    
}
void HelloWorld::initPlatforms()
{
    this->platforms = new Group();
    
    for (int i = 0; i<30; i++) {
        entity = new Entity("block2.png");
        entity->node->setIsVisible(false);
        this->platforms->add(entity);
        //this->addChild(entity->node);
        gameSpaceNode->addChild(entity->node);
    }
}

void HelloWorld::initGems()
{
    this->gems = new Group();
    
    for (int i = 0; i< 10; i++) {
        entity = new Entity("coin2.png");
        this->gems->add(entity);
        entity->node->setPosition(ccp(winSize.width*CCRANDOM_0_1(), (winSize.height-50)*CCRANDOM_0_1()));
        //this->addChild(entity->node);
        gameSpaceNode->addChild(entity->node);
    }
}

void HelloWorld::initEnemies()
{
    this->flies = new Group();
    Entity *fly;
    for (int i = 0; i<2; i++) {
        fly = new Entity("fly_fly2.png");
        //this->addChild(fly->node);
        gameSpaceNode->addChild(fly->node);
        fly->node->setPosition(CCPointMake(-10*CCRANDOM_0_1(), CCRANDOM_0_1()*(winSize.height - 50)));
        fly->physics->v.x = CCRANDOM_0_1()*20;
        this->flies->add(fly);
    }
}

void HelloWorld::initDebug()
{
    
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
        addPlatform(location);
    }

}

void HelloWorld::didAccelerate(CCAcceleration *pAccelerationValue)
{
	this->hero->physics->v.x = pAccelerationValue->x * 60.0f;
}

void HelloWorld::addPlatform(CCPoint location)
{
    if (this->nextBlockIndex >= this->platforms->count()) {
        return;
    }
    
    entity = this->platforms->get()->getObjectAtIndex(this->nextBlockIndex++);
    entity->node->setPosition(gameSpaceNode->convertToNodeSpace(location));
    entity->node->setIsVisible(true);
    
}

void HelloWorld::update(ccTime dt)
{
    gameSpaceNode->setPosition(ccpAdd(gameSpaceNode->getPosition(), hero->physics->getCalculatedShift()));
        
    for (int i = 0; i<this->platforms->count(); i++) {
        entity = this->platforms->get()->getObjectAtIndex(i);
        if (entity->node->getIsVisible()) {
            if (entity->physics->isCollideWith(this->hero->node)) {
                this->hero->physics->jump(-50);
            }
        }
    }
    
    for (int i = 0; i<this->gems->count(); i++) {
        entity = this->gems->get()->getObjectAtIndex(i);
        
        if (entity->node->getIsVisible()) {
            if (entity->physics->isCollideWith(this->hero->node)) {
                entity->node->setIsVisible(false);
                this->hud->addPoints(1);
            }
        }
    }
    
    
    for (int i; i<this->flies->count(); i++) {
        entity = this->flies->get()->getObjectAtIndex(i);
    }

    if (this->hero->node->getPosition().y < 16) {
        this->hero->physics->jump(-50);
    }
    
    this->flies->update(dt);
    this->hero->physics->update(dt);
}

void HelloWorld::clean()
{
    CC_SAFE_DELETE(this->hero);
    CC_SAFE_DELETE(this->flies);
    CC_SAFE_DELETE(this->gems);
    CC_SAFE_DELETE(this->platforms);
}

void HelloWorld::keyBackClicked() 
{
    clean();
    CCDirector::sharedDirector()->end();
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    clean();
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
