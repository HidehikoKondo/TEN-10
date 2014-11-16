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

#define DEF_APP_DL_URL_ANDROID  ("http://goo.gl/VKAoCX")
#define DEF_APP_DL_URL_IOS      ("https://itunes.apple.com/jp/app/id942095807")

USING_NS_CC;

using namespace CocosDenshion;

GameOverLayer::GameOverLayer()
:m_score(0)
,m_LastMenuItem(NULL)
,m_lastQuestion("")
,m_LastQuestionLabel(NULL)
,m_AnswerNode(NULL)
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
    
    //アンサーポイント
    this->m_AnswerNode = AnswerPointNode::create();
    this->addChild(this->m_AnswerNode);
    this->m_AnswerNode->setPosition(ccp(size.width,size.height));
    this->m_AnswerNode->setAnchorPoint(ccp(1.0f,1.0f));
    
    CCMenu * menu = CCMenu::create();
    menu->setPosition(CCPointZero);
    this->addChild(menu);

    //解除ボタン
    char buff[255] = "";
    sprintf(buff, "[ Open the Answer]\n (AP -%lu) ",GameRuleManager::getInstance()->getAnswerSubValue());
    this->m_LastQuestionLabel = CCLabelBMFont::create(buff, "base/little_number2.fnt", 500, kCCTextAlignmentCenter);
    this->m_LastMenuItem = CCMenuItemLabel::create(this->m_LastQuestionLabel, this, menu_selector(GameOverLayer::onUnlockQuestion));
    this->m_LastMenuItem->setPosition(ccp(size.width * 0.5f,400));
    menu->addChild(this->m_LastMenuItem);
    //解除ポイント有無
    if(!this->m_AnswerNode->isPayAnserPoint())
    {
        this->m_LastMenuItem->setEnabled(false);
    }
    
    //ツイートボタン
    CCLabelBMFont * labelTweet = CCLabelBMFont::create("[ Tweet ]", "base/little_number2.fnt", 240, kCCTextAlignmentCenter);
    CCMenuItemLabel * labelTw = CCMenuItemLabel::create(labelTweet, this, menu_selector(GameOverLayer::onTweet));
    labelTw->setPosition(ccp(size.width * 0.5f,300));
    menu->addChild(labelTw);
    
    //戻るボタン
    CCLabelBMFont * labelBM = CCLabelBMFont::create("[ Title ]", "base/little_number2.fnt", 200, kCCTextAlignmentCenter);
    CCMenuItemLabel * label = CCMenuItemLabel::create(labelBM, this, menu_selector(GameOverLayer::moveToTitle));
    
    label->setPosition(ccp(size.width * 0.5f,200));
    menu->addChild(label);
    
    return true;
}
/**
 * 最後の問題
 */
void GameOverLayer::setLastQuestion(char* value)
{
    this->m_lastQuestion = value;
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
        tweetStr += "[TEN -10- ] \'CHALENGE MODE\' ";
    }
    else
    {
        tweetStr += "[TEN -10- ]\'TIME TRIAL MODE\' ";
    }

    //文言
    char buff[30];
    if(GameRuleManager::getInstance()->getGameMode() == GM_CHALENGE)
    {
        sprintf(buff,"Q.%2ld CREAR!!",this->m_score);
    }
    else
    {
        sprintf(buff,"%2ld:%02ld",static_cast<long>(this->m_score/60),this->m_score%60);
    }
    
    tweetStr += buff;
    tweetStr += " ";
    
    //アプリDLの短縮URL
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    tweetStr += DEF_APP_DL_URL_ANDROID;
#else
    tweetStr += DEF_APP_DL_URL_IOS;
#endif
    
    //Object-C or JNIに接続してツイートする
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    NativeTweet::openTweetDialog(tweetStr.c_str());
#else
    NativeTweet::openTweetDialog(tweetStr.c_str());
#endif

}

void GameOverLayer::onUnlockQuestion()
{
    this->m_LastMenuItem->setEnabled(false);
    
    this->m_AnswerNode->onPayAnserPoint();
    
    //問題の公開
    this->m_LastQuestionLabel->setString(this->m_lastQuestion.c_str());
}



