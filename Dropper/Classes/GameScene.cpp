#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Hud.h"
#include "Entity.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	GameScene *layer = GameScene::node();
    
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
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
    
    gameSpaceSize.width = winSize.width;
    gameSpaceSize.height = 800;
    gameSpaceNode = CCLayer::node();
    
    addChild(gameSpaceNode);
    
    initBg();
    initHero();
    initPlatforms();
    initGems();
    initEnemies();
    //initDebug();
    scheduleUpdate();
    
	return true;
}

void GameScene::onEnter()
{
    CCLayer::onEnter();
}

void GameScene::draw()
{
    CCLayer::draw();
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(2);
    glColor4ub(255, 0, 0, 0);
    //ccDrawLine( CCPointMake(10, 10), CCPointMake(gameSpaceSize.width, 0));
    //ccDrawLine( CCPointMake(0, gameSpaceSize.height), CCPointMake(gameSpaceSize.width, gameSpaceSize.height));
}
void GameScene::initBg()
{
    
}

void GameScene::initHero()
{
    this->hero = new Entity("front2.png");
    this->hero->physics->a.y = -1.2f;
    this->hero->node->setPosition(ccp(gameSpaceSize.width/2,gameSpaceSize.height-100));
    gameSpaceNode->addChild(hero->node);
    position = gameSpaceNode->getPosition();
    gameSpaceNode->setPosition(CCPointMake(position.x, position.y-hero->node->getPosition().y + winSize.height - 100));
    lastBlockContact = -1;
    
}
void GameScene::initPlatforms()
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

void GameScene::initGems()
{
    this->gems = new Group();
    
    for (int i = 0; i< 10; i++) {
        entity = new Entity("coin2.png");
        this->gems->add(entity);
        entity->node->setPosition(ccp(gameSpaceSize.width*CCRANDOM_0_1(), (gameSpaceSize.height-50)*CCRANDOM_0_1()));

        gameSpaceNode->addChild(entity->node);
    }
}

void GameScene::initEnemies()
{
    this->flies = new Group();
    Entity *fly;
    for (int i = 0; i<2; i++) {
        fly = new Entity("fly_fly2.png");
        //this->addChild(fly->node);
        gameSpaceNode->addChild(fly->node);
        fly->node->setPosition(CCPointMake(-10*CCRANDOM_0_1(), CCRANDOM_0_1()*(gameSpaceSize.height - 50)));
        fly->physics->v.x = CCRANDOM_0_1()*30;
        this->flies->add(fly);
    }
}

void GameScene::initDebug()
{
    
}

void GameScene::ccTouchesEnded(CCSet *touches, CCEvent *event)
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

void GameScene::didAccelerate(CCAcceleration *pAccelerationValue)
{
	this->hero->physics->v.x = pAccelerationValue->x * 60.0f;
}

void GameScene::addPlatform(CCPoint location)
{
    if (this->nextBlockIndex >= this->platforms->count()) {
        return;
    }
    
    entity = this->platforms->get()->getObjectAtIndex(this->nextBlockIndex++);
    entity->node->setPosition(gameSpaceNode->convertToNodeSpace(location));
    entity->node->setIsVisible(true);
    
}

void GameScene::update(ccTime dt)
{
    // center hero
    position = hero->node->getPosition();
    if (position.y < gameSpaceSize.height - winSize.height/2 && position.y> winSize.height/2) {
        position = hero->physics->getCalculatedShift();
        //position.x = -position.x;
        position.x = 0;
        gameSpaceNode->setPosition(ccpAdd(gameSpaceNode->getPosition(), position));
    }
    
    // hero get bounds
    position = hero->node->getPosition();
    if (position.x < 8) {
        hero->node->setPosition(CCPointMake(8, hero->node->getPosition().y));
    }
    
    if (position.x > gameSpaceSize.width) {
        hero->node->setPosition(CCPointMake(gameSpaceSize.width-8, hero->node->getPosition().y));
    }
    
    // platforms
    for (int i = 0; i<this->platforms->count(); i++) {
        entity = this->platforms->get()->getObjectAtIndex(i);
        if (entity->node->getIsVisible()) {
            if (entity->physics->isCollideWith(this->hero->node)) {
                //CCLog("kontakt");
                int jumpHeight = -50;
                lastBlockContact = i;
                this->hero->physics->jump(jumpHeight);   
            }
        }
    }
    
    // gems
    for (int i = 0; i<this->gems->count(); i++) {
        entity = this->gems->get()->getObjectAtIndex(i);
        
        if (entity->node->getIsVisible()) {
            if (entity->physics->isCollideWith(this->hero->node)) {
                entity->node->setIsVisible(false);
                this->hud->addPoints(1);
            }
        }
    }
    
    // enemies
    for (int i; i<this->flies->count(); i++) {
        entity = this->flies->get()->getObjectAtIndex(i);
        //@TODO collision
    }

    // debug
    if (this->hero->node->getPosition().y < 16) {
        this->hero->physics->jump(-50);
    }
    
    this->flies->update(dt);
    this->hero->physics->update(dt);
}

void GameScene::clean()
{
    CC_SAFE_DELETE(this->hero);
    CC_SAFE_DELETE(this->flies);
    CC_SAFE_DELETE(this->gems);
    CC_SAFE_DELETE(this->platforms);
}

void GameScene::keyBackClicked() 
{
    clean();
    CCDirector::sharedDirector()->end();
}

void GameScene::menuCloseCallback(CCObject* pSender)
{
    clean();
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
