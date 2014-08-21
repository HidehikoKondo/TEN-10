//
//  RunkingScene.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#include "RunkingScene.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "SoundDef.h"

USING_NS_CC;
using namespace CocosDenshion;

/**
 * コンストラクタ
 */
RunkingScene::RunkingScene()
{
}
/**
 * デストラクタ
 */
RunkingScene::~RunkingScene()
{
}

CCScene* RunkingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    RunkingScene *layer = RunkingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RunkingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size =CCDirector::sharedDirector()->getWinSize();
    
    CCSprite *title = CCSprite::create("base/ranking_title.png");
    
    this->addChild(title);
    title->setPosition(ccp(size.width * 0.5f,size.height - 45));
    
    
    CCMenu * menu = CCMenu::create();
    this->addChild(menu,0);
    menu->setPosition(CCPointZero);
    
    //戻るボタン
    CCLabelBMFont * backStrLabel = CCLabelBMFont::create("Back", "base/little_number2.fnt", 150, kCCTextAlignmentCenter);
    CCMenuItemLabel * back = CCMenuItemLabel::create(backStrLabel, this, menu_selector(RunkingScene::moveToTopScene));
    menu->addChild(back);
    
    back->setPosition(ccp(size.width * 0.5f, 100));
    
    return true;
}
/**
 * メインメニューに戻る
 */
void RunkingScene::moveToTopScene(cocos2d::CCObject sender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.25f, TitleScene::scene()));
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_SELECT);
}
