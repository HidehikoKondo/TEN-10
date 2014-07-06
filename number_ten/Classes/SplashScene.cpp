//
//  SplashScene.cpp
//  TreeTest
//
//  Created by ooharayukio on 2013/12/16.
//
//

#include "SplashScene.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

CCScene* SplashScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SplashScene *layer = SplashScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

/**
 * 初期化
 */
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //ロゴ
    CCSprite* pSprite = CCSprite::create("Default-568h@2x.png");
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    //１秒間表示
    runAction(
              CCSequence::create(
                                 CCDelayTime::create(1.0f),
                                 CCCallFunc::create(this,callfunc_selector(SplashScene::nextScene)),
                                 NULL)
              );
    
    return true;
}
/**
 * 次のシーンへ移動
 */
void SplashScene::nextScene()
{
    CCDirector::sharedDirector()->replaceScene(TitleScene::scene());
}

