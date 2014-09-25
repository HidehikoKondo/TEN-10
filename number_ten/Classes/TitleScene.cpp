//
//  TitleScene.cpp
//  TreeTest
//
//  Created by ooharayukio on 2013/12/16.
//
//

#include "TitleScene.h"
#include "GameRuleManager.h"
#include "NumberTenScene.h"
#include "RunkingScene.h"
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

    CCSprite* pSprite = CCSprite::create("title/title_number_ten.png");
    pSprite->setTag(5000);
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height*0.75f) );
    
    this->m_StartMenu = CCMenu::create();
    this->m_StartMenu->setPosition(CCPointZero);
    this->addChild(this->m_StartMenu);

    //チャレンジボタン
    CCSprite* pChallengeImg = CCSprite::create("title/button_challenge.png");
    CCSprite* pChallengeImg_sel = CCSprite::create("title/button_challenge.png");
    pChallengeImg_sel->setScale(1.05f);
    CCMenuItemSprite* challengeButton = CCMenuItemSprite::create(pChallengeImg,pChallengeImg_sel, this, menu_selector(TitleScene::moveSceneToChallenge));
    challengeButton->setAnchorPoint(ccp(0.5f,0.5f));
    challengeButton->setPosition(ccp(size.width/2,size.height * 0.55f));
    challengeButton->setScale(0.5f);
    this->m_StartMenu->addChild(challengeButton);

    //タイムトライアルボタン
    CCSprite* pTimeImg = CCSprite::create("title/button_time_trial.png");
    CCSprite* pTimeImg_sel = CCSprite::create("title/button_time_trial.png");
    pTimeImg_sel->setScale(1.05f);
    CCMenuItemSprite* timeButton = CCMenuItemSprite::create(pTimeImg,pTimeImg_sel, this, menu_selector(TitleScene::moveSceneToTimeTrial));
    timeButton->setAnchorPoint(ccp(0.5f,0.5f));
    timeButton->setPosition(ccp(size.width/2,size.height * 0.45f));
    timeButton->setScale(0.5f);
    this->m_StartMenu->addChild(timeButton);
    
    //ランキングボタン
    CCSprite* pRankingImg = CCSprite::create("title/button_ranking.png");
    CCSprite* pRankingImg_sel = CCSprite::create("title/button_ranking.png");
    pRankingImg_sel->setScale(1.05f);
    CCMenuItemSprite* rankingButton = CCMenuItemSprite::create(pRankingImg,pRankingImg_sel, this, menu_selector(TitleScene::moveSceneToRanking));
    rankingButton->setAnchorPoint(ccp(0.5f,0.5f));
    rankingButton->setPosition(ccp(size.width/2,size.height * 0.35f));
    rankingButton->setScale(0.5f);
    this->m_StartMenu->addChild(rankingButton);

    //HELP
    CCSprite* pHelpImg = CCSprite::create("title/button_help.png");
    CCSprite* pHelpImg_sel = CCSprite::create("title/button_help.png");
    pHelpImg_sel->setScale(1.05f);
    CCMenuItemSprite* helpButton = CCMenuItemSprite::create(pHelpImg,pHelpImg_sel, this, menu_selector(TitleScene::viewHelp));
    helpButton->setAnchorPoint(ccp(0.5f,0.5f));
    helpButton->setPosition(ccp(size.width/2,size.height * 0.25f));
    helpButton->setScale(0.5f);
    this->m_StartMenu->addChild(helpButton);
    
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

    //音声ファイル読み込み
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_SELECT);

    //ファイルのチェック
    CCObject * obj;
    CCArray *questionData = CCArray::createWithContentsOfFile("base/q_data.plist");
    CCARRAY_FOREACH(questionData, obj)
    {
        CCDictionary* data = dynamic_cast<CCDictionary*>(obj);
        CCString * str = dynamic_cast<CCString*>(data->objectForKey("question"));
        char workMoji[5] = "";
        char moji[5] = "";
        memset(moji, '\0', 5);
        sprintf(workMoji, "%04d", str->intValue());
        
        //問題に回答があるかチェックする
        char ques_moji[12] = "";
        GameRuleManager::getInstance()->questionCheck(ques_moji,ques_moji,workMoji);
    }

    return true;
}

void TitleScene::viewHelp()
{
    HelpLayer * layer = HelpLayer::create(this, dialog_result_selecter(TitleScene::onHelpResult));
    this->addChild(layer,1000);
    layer->setPosition(CCPointZero);
    layer->setTag(555555);
    
    this->m_StartMenu->setEnabled(false);
}
void TitleScene::onHelpResult(DIALOG_RESULT ret)
{
    HelpLayer * layer = dynamic_cast<HelpLayer*>(this->getChildByTag(555555));
    if(layer)
    {
        layer->removeFromParent();
    }
    this->m_StartMenu->setEnabled(true);
}

/**
 * 選択画面にいく
 */
void TitleScene::NextScene(CCObject*obj)
{
    CCSprite *sprite = static_cast<CCSprite*>(this->getChildByTag(5000));
    sprite->stopAllActions();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//    AstExt::NativeCodeAst::hideAst();
#endif
    
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_SELECT);
    
    CCDirector::sharedDirector()->replaceScene(
                                               CCTransitionSlideInR::create(0.25f,NumberTenScene::scene())
                                               );
}
/**
 * チャレンジモード
 */
void TitleScene::moveSceneToChallenge(CCObject*obj)
{
    GameRuleManager::getInstance()->setGameMode(GM_CHALENGE);
    
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_SELECT);
    
    CCDirector::sharedDirector()->replaceScene(
                                               CCTransitionSlideInR::create(0.25f,NumberTenScene::scene())
                                               );
}
/**
 * タイムトライアル
 */
void TitleScene::moveSceneToTimeTrial(CCObject*obj)
{
    GameRuleManager::getInstance()->setGameMode(GM_TIME_TRIAL);
    
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_SELECT);
    
    CCDirector::sharedDirector()->replaceScene(
                                               CCTransitionSlideInR::create(0.25f,NumberTenScene::scene())
                                               );
}
/**
 * ランキング
 */
void TitleScene::moveSceneToRanking(CCObject*obj)
{
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_SELECT);
    
    CCDirector::sharedDirector()->replaceScene(
                                               CCTransitionSlideInR::create(0.25f,RunkingScene::scene())
                                               );
}

void TitleScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
