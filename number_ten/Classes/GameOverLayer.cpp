//
//  GameOverLayer.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/20.
//
//

#include "GameOverLayer.h"
#include "TitleScene.h"
#include "SoundDef.h"
#include "SimpleAudioEngine.h"
#include "NativeTweet.h"

#define DEF_APP_DL_URL_ANDROID ("http://goo.gl/VKAoCX")

USING_NS_CC;

using namespace CocosDenshion;

GameOverLayer::GameOverLayer()
:m_score(0)
{
    
}
GameOverLayer::~GameOverLayer()
{
    
}

bool GameOverLayer::init()
{
    if(!CCLayerColor::init())
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    this->setColor(ccc3(0, 0, 0));
    this->setOpacity(0xBF);
    
    this->m_GameOverString = CCSprite::create("base/game_over_title.png");
    this->m_GameOverString->setPosition(ccp(size.width * 0.5f,size.height * 0.75f));
    this->addChild(this->m_GameOverString);
    
    
    CCMenu * menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    this->addChild(menu);

    //ツイートボタン
    CCLabelBMFont * labelTweet = CCLabelBMFont::create("[ T w e e t ]", "base/little_number2.fnt", 240, kCCTextAlignmentCenter);
    CCMenuItemLabel * labelTw = CCMenuItemLabel::create(labelTweet, this, menu_selector(GameOverLayer::onTweet));
    labelTw->setPosition(ccp(size.width * 0.5f,300));
    menu->addChild(labelTw);
    
    //戻るボタン
    CCLabelBMFont * labelBM = CCLabelBMFont::create("[ T i t l e ]", "base/little_number2.fnt", 200, kCCTextAlignmentCenter);
    CCMenuItemLabel * label = CCMenuItemLabel::create(labelBM, this, menu_selector(GameOverLayer::moveToTitle));
    
    label->setPosition(ccp(size.width * 0.5f,200));
    menu->addChild(label);
    
    return true;
}
/**
 * 記録の登録
 */
void GameOverLayer::entoryRecord(GAME_MODE mode,long value)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    this->m_score = value;
    
    //文言
    char buff[30];
    if(mode == GM_CHALENGE)
    {
        sprintf(buff,"Q.%2ld",value);
    }
    else
    {
        sprintf(buff,"%2ld:%02ld",static_cast<long>(value/60),value%60);
    }
    
    CCLabelBMFont * recordLabel  = CCLabelBMFont::create(buff, "base/little_number.fnt", 400, kCCTextAlignmentCenter);
    recordLabel->setPosition(ccp(size.width * 0.5f,size.height * 0.5f));
    this->addChild(recordLabel);
    
    if(GameRuleManager::getInstance()->isNewRecordScore(mode, value))
    {
        GameRuleManager::getInstance()->setRankingScore(mode, value);

        //記録更新の効果音
        SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_NEW_RECORD);
    }
    else
    {
        //ゲームオーバーの効果音
        SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_GAME_OVER);
    }
}

void GameOverLayer::moveToTitle()
{
    CCDirector::sharedDirector()->replaceScene(CCTransitionSlideInR::create(0.25f, TitleScene::scene()));
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_SELECT);
}

/**
 * tweetする
 */
void GameOverLayer::onTweet()
{
    std::string tweetStr;
    if(GameRuleManager::getInstance()->getGameMode() == GM_CHALENGE )
    {
        tweetStr += "[TEN] \'Chalenge Mode\' ";
    }
    else
    {
        tweetStr += "[TEN]\'Time Trial Mode\' ";
    }

    //文言
    char buff[30];
    if(GameRuleManager::getInstance()->getGameMode() == GM_CHALENGE)
    {
        sprintf(buff,"Q.%2ld",this->m_score);
    }
    else
    {
        sprintf(buff,"%2ld:%02ld",static_cast<long>(this->m_score/60),this->m_score%60);
    }
    
    tweetStr += buff;
    tweetStr += " ";
    
    //アプリDLの短縮URL
    tweetStr += DEF_APP_DL_URL_ANDROID;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeTweet::openTweetDialog(tweetStr.c_str());
#endif
}
