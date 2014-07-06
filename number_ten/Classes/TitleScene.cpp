//
//  TitleScene.cpp
//  TreeTest
//
//  Created by ooharayukio on 2013/12/16.
//
//

#include "TitleScene.h"
#include "NumberTenScene.h"
#include "SimpleAudioEngine.h"
#include "NativeCodeAst.h"
#include "SoundDef.h"

using namespace cocos2d;
using namespace CocosDenshion;

/**
 * タイトル画面
 */
CCScene* TitleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    TitleScene *layer = TitleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AstExt::NativeCodeAst::showAst();
#endif
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCSprite* pSprite = CCSprite::create("base/title_number_ten.png");
    pSprite->setTag(5000);
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height*0.75f) );
    
    
    CCLabelTTF * TapStringLabel = CCLabelTTF::create("タッチしてスタート", "Helvetica", 32);
    CCMenuItemLabel* LabelButton = CCMenuItemLabel::create(TapStringLabel, this, menu_selector(TitleScene::NextScene));
    CCMenu * StartMenu = CCMenu::create(LabelButton,NULL);
    this->addChild(StartMenu);

    StartMenu->setPosition(CCPointZero);
    
    //タップしてスタート
    LabelButton->setAnchorPoint(ccp(0.5f,0.5f));
    LabelButton->setPosition(ccp(size.width/2,size.height * 0.25f));
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    //音声ファイル読み込み
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_SELECT);
    
    return true;
}
/**
 * 選択画面にいく
 */
void TitleScene::NextScene(CCObject*obj)
{
    CCSprite *sprite = static_cast<CCSprite*>(this->getChildByTag(5000));
    sprite->stopAllActions();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AstExt::NativeCodeAst::hideAst();
#endif
    
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_SELECT);
    
    CCDirector::sharedDirector()->replaceScene(NumberTenScene::scene());
}

void TitleScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
