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

USING_NS_CC;

using namespace CocosDenshion;

GameOverLayer::GameOverLayer()
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
