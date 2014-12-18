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
#include "GameRuleManager.h"
#include "AppCCloudPlugin.h"

USING_NS_CC;
using namespace CocosDenshion;

/**
 * コンストラクタ
 */
RunkingScene::RunkingScene()
:m_rankingList(NULL)
{
}
/**
 * デストラクタ
 */
RunkingScene::~RunkingScene()
{
    CC_SAFE_RELEASE_NULL(this->m_rankingList);
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
    

    this->makeChalengeRanking();
    
    
    //世界ランキング
    CCLabelBMFont * GlobalStrLabel = CCLabelBMFont::create("[ NETWORK RANKING ]", "base/little_number2.fnt", 500, kCCTextAlignmentCenter);
    CCMenuItemLabel * Global = CCMenuItemLabel::create(GlobalStrLabel, this, menu_selector(RunkingScene::viewGlobalRanking));
    menu->addChild(Global);
    
    Global->setPosition(ccp(size.width * 0.5f, 300));
    
    //切り替えボタン
    CCLabelBMFont * chaStrLabel = CCLabelBMFont::create("[ CHALENGE ]", "base/little_number2.fnt", 300, kCCTextAlignmentCenter);
    CCMenuItemLabel * chalenge = CCMenuItemLabel::create(chaStrLabel, this, menu_selector(RunkingScene::chengeViewChalenge));
    chalenge->setAnchorPoint(ccp(0.5f,0.5f));
    menu->addChild(chalenge);
    
    chalenge->setPosition(ccp(size.width * 0.25f, 260));

    //切り替えボタン
    CCLabelBMFont * timeStrLabel = CCLabelBMFont::create("[ TIME TRIAL ]", "base/little_number2.fnt", 300, kCCTextAlignmentCenter);
    CCMenuItemLabel * timetrial = CCMenuItemLabel::create(timeStrLabel, this, menu_selector(RunkingScene::chengeViewTimeTrial));
    timetrial->setAnchorPoint(ccp(0.5f,0.5f));
    menu->addChild(timetrial);
    
    timetrial->setPosition(ccp(size.width * 0.75f, 260));
    
    
    //戻るボタン
    CCLabelBMFont * backStrLabel = CCLabelBMFont::create("[ BACK ]", "base/little_number2.fnt", 250, kCCTextAlignmentCenter);
    CCMenuItemLabel * back = CCMenuItemLabel::create(backStrLabel, this, menu_selector(RunkingScene::moveToTopScene));
    menu->addChild(back);
    
    back->setPosition(ccp(size.width * 0.5f, 220));

    return true;
}
/**
 * チャレンジモード用のランキング
 */
void RunkingScene::makeChalengeRanking()
{
    CCNode * node;
    while((node = this->getChildByTag(100)) != NULL)
    {
        node->removeFromParent();
    }
    
    CCSize size =CCDirector::sharedDirector()->getWinSize();
    //ランキングのリストを取得する
    CC_SAFE_RELEASE_NULL(this->m_rankingList);
    this->m_rankingList = GameRuleManager::getInstance()->getRankingList(GM_CHALENGE);
    CC_SAFE_RETAIN(this->m_rankingList);
    
    CCPoint rankingPos;
    rankingPos.x = size.width * 0.5f;
    rankingPos.y = size.height - 120.0f;
    
    CCObject * obj;
    char mojiBuff[256] = "";
    int rankingIndex = 1;
    CCARRAY_FOREACH(this->m_rankingList, obj)
    {
        CCString * moji = dynamic_cast<CCString*>(obj);
        if(moji)
        {
            sprintf(mojiBuff,"%2d :",rankingIndex);
            CCLabelBMFont * rankingNo = CCLabelBMFont::create(mojiBuff,"base/little_number2.fnt", 100, kCCTextAlignmentLeft);
            rankingPos.x = size.width * 0.25f;
            rankingNo->setAnchorPoint(CCPointZero);
            rankingNo->setPosition(rankingPos);
            rankingNo->setTag(100);
            this->addChild(rankingNo,10);
            
            sprintf(mojiBuff,"Q. %6d",moji->intValue());
            CCLabelBMFont * rankingStr = CCLabelBMFont::create(mojiBuff,"base/little_number2.fnt", 200, kCCTextAlignmentRight);
            rankingPos.x = size.width * 0.5f;
            rankingStr->setAnchorPoint(CCPointZero);
            rankingStr->setPosition(rankingPos);
            rankingStr->setTag(100);
            this->addChild(rankingStr,10);
            
            rankingPos.y -= 45;
            
            //次のランキング
            rankingIndex++;
        }
    }
}

/**
 * トライアルモード用のランキング
 */
void RunkingScene::makeTimeTrialRanking()
{
    CCNode * node;
    while((node = this->getChildByTag(100)) != NULL)
    {
        node->removeFromParent();
    }
    
    CCSize size =CCDirector::sharedDirector()->getWinSize();
    //ランキングのリストを取得する
    CC_SAFE_RELEASE_NULL(this->m_rankingList);
    this->m_rankingList = GameRuleManager::getInstance()->getRankingList(GM_TIME_TRIAL);
    CC_SAFE_RETAIN(this->m_rankingList);
    
    CCPoint rankingPos;
    rankingPos.x = size.width * 0.5f;
    rankingPos.y = size.height - 120.0f;
    
    CCObject * obj;
    char mojiBuff[256] = "";
    int rankingIndex = 1;
    CCARRAY_FOREACH(this->m_rankingList, obj)
    {
        CCString * moji = dynamic_cast<CCString*>(obj);
        if(moji)
        {
            sprintf(mojiBuff,"%2d :",rankingIndex);
            CCLabelBMFont * rankingNo = CCLabelBMFont::create(mojiBuff,"base/little_number2.fnt", 100, kCCTextAlignmentLeft);
            rankingPos.x = size.width * 0.25f;
            rankingNo->setAnchorPoint(CCPointZero);
            rankingNo->setPosition(rankingPos);
            rankingNo->setTag(100);
            this->addChild(rankingNo,10);
            
            sprintf(mojiBuff,"%2ld:%02d",static_cast<long>(moji->intValue()/60),moji->intValue()%60);
            CCLabelBMFont * rankingStr = CCLabelBMFont::create(mojiBuff,"base/little_number2.fnt", 200, kCCTextAlignmentRight);
            rankingPos.x = size.width * 0.5f;
            rankingStr->setAnchorPoint(CCPointZero);
            rankingStr->setPosition(rankingPos);
            rankingStr->setTag(100);
            this->addChild(rankingStr,10);
            
            rankingPos.y -= 45;
            
            //次のランキング
            rankingIndex++;
        }
    }
}
void RunkingScene::chengeViewChalenge(cocos2d::CCObject sender)
{
    this->makeChalengeRanking();
}
void RunkingScene::chengeViewTimeTrial(cocos2d::CCObject sender)
{
    this->makeTimeTrialRanking();
}
void RunkingScene::viewGlobalRanking(cocos2d::CCObject sender)
{
    AppCCloudPlugin::Gamers::showGamersView();
}

/**
 * メインメニューに戻る
 */
void RunkingScene::moveToTopScene(cocos2d::CCObject sender)
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.25f, TitleScene::scene()));
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_SELECT);
}
