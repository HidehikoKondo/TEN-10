//
//  SelectMenuScene.cpp
//  rendaPower
//
//  Created by 大原幸夫 on 2014/02/23.
//
//

#include "SelectMenuScene.h"
#include "SimpleAudioEngine.h"
#include "SoundDef.h"

#include "ShuttleScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* SelectMenuScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SelectMenuScene *layer = SelectMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    bool bRet = CCLayer::init();
    if ( false == bRet )
    {
        return false;
    }
    
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    /* 背景 */
    CCLayerColor *backGround = CCLayerColor::create(ccc4(255, 255, 255, 255), size.width, size.height);
    backGround->setPosition(CCPointZero);
    this->addChild(backGround);

    //タイトル
    CCLabelTTF * menuTitle = CCLabelTTF::create("Game Menu", "Helvetica", 40);
    menuTitle->setColor(ccc3(255, 0, 0));
    menuTitle->setPosition(ccp(size.width/2,size.height * 0.85f));
    this->addChild(menuTitle);

    //スペースシャトルボタン
    CCSprite *normalSprite = CCSprite::create("base/menu_space_shuttle.png");
    CCSprite *selectSprite = CCSprite::createWithTexture(normalSprite->getTexture());
    selectSprite->setColor(ccc3(0x7F, 0x7F, 0x7F));
    CCMenuItem *menu_space_shuttle = CCMenuItemSprite::create(normalSprite, selectSprite);
    menu_space_shuttle->setTarget(this, menu_selector(SelectMenuScene::ShuttleScene));
    
    CCMenu * StartMenu = CCMenu::create(menu_space_shuttle,NULL);
    this->addChild(StartMenu);
    
    StartMenu->setPosition(CCPointZero);
    menu_space_shuttle->setAnchorPoint(ccp(0.5f,0.5f));
    menu_space_shuttle->setPosition(ccp(size.width/2,size.height * 0.65f));
        
    return true;
}
/**
 * 選択画面にいく
 */
void SelectMenuScene::ShuttleScene(CCObject*obj)
{
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_SELECT);
    
    CCDirector::sharedDirector()->replaceScene(ShuttleScene::scene());
}

void SelectMenuScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
