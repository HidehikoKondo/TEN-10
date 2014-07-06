//
//  ScoreLayer.cpp
//  rendaPower
//
//  Created by ooharayukio on 2014/06/02.
//
//

#include "ScoreLayer.h"
#include "TitleScene.h"

USING_NS_CC;

ScoreLayer::ScoreLayer()
:m_HiScoreLabel(NULL)
,m_ScoreLabel(NULL)
,m_StrScoreSLabel(NULL)
,m_StrHiScoreSLabel(NULL)
,m_RetryLabelButton(NULL)
,m_target(NULL)
{
    
}
ScoreLayer::~ScoreLayer()
{
    
}

bool ScoreLayer::init()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    if(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 0x3A), size.width, size.height))
    {
        return false;
    }
    
    this->m_StrHiScoreSLabel = CCLabelTTF::create("HiScore:", "Helvetica", 50,CCSizeMake(250, 60),kCCTextAlignmentCenter);
    this->m_HiScoreLabel = CCLabelTTF::create("", "Helvetica", 50,CCSizeMake(250, 60),kCCTextAlignmentRight);
    this->m_StrScoreSLabel = CCLabelTTF::create("Score:", "Helvetica", 50,CCSizeMake(250, 60),kCCTextAlignmentCenter);
    this->m_ScoreLabel = CCLabelTTF::create("", "Helvetica", 50,CCSizeMake(250, 60),kCCTextAlignmentRight);
    
    this->addChild(this->m_StrHiScoreSLabel,1);
    this->addChild(this->m_HiScoreLabel,1);
    this->addChild(this->m_StrScoreSLabel,1);
    this->addChild(this->m_ScoreLabel,1);
    
    this->m_StrHiScoreSLabel->setPosition(ccp(size.width * 0.25f , size.height * 0.75f));
    this->m_HiScoreLabel->setPosition(ccp(size.width * 0.75f ,size.height * 0.75f));
    this->m_StrScoreSLabel->setPosition(ccp(size.width * 0.25f , size.height * 0.5f));
    this->m_ScoreLabel->setPosition(ccp(size.width * 0.75f , size.height * 0.5f));

    //リトライ
    CCLabelTTF *retrylabel = CCLabelTTF::create("[Retry?]", "Helvetica", 50,CCSizeMake(280, 60),kCCTextAlignmentCenter);
    this->m_RetryLabelButton = CCMenuItemLabel::create(retrylabel,this,menu_selector(ScoreLayer::onRetry));
    this->m_RetryLabelButton->setPosition(ccp(size.width * 0.25f,size.height * 0.25f));

    //トップ画面
    CCLabelTTF *toplabel = CCLabelTTF::create("[Top Menu?]", "Helvetica", 50,CCSizeMake(280, 60),kCCTextAlignmentCenter);
    this->m_TopLabelButton = CCMenuItemLabel::create(toplabel,this,menu_selector(ScoreLayer::onMoveSceneTop));
    this->m_TopLabelButton->setPosition(ccp(size.width * 0.75f,size.height *0.25f));

    CCMenu * menu = CCMenu::create(this->m_RetryLabelButton,this->m_TopLabelButton,NULL);
    this->addChild(menu,100);
    
    menu->setPosition(ccp(0,0));
    
    return true;
}

void ScoreLayer::setScore(unsigned long score,unsigned long hiscore)
{
    char buf[128] = "";
    sprintf(buf, "%ld",score);
    this->m_ScoreLabel->setString(buf);
    sprintf(buf, "%ld",hiscore);
    this->m_HiScoreLabel->setString(buf);
}
void ScoreLayer::setVisibleRetryButton(bool val)
{
    this->m_RetryLabelButton->setVisible(val);
    this->m_TopLabelButton->setVisible(val);
}

void ScoreLayer::setRetryCallback(cocos2d::CCObject * target,cocos2d::SEL_CallFunc  callback)
{
    this->m_target = target;
    this->m_callback = callback;
}

void ScoreLayer::onMoveSceneTop()
{
    CCDirector::sharedDirector()->replaceScene(TitleScene::scene());
}
void ScoreLayer::onRetry()
{
    if(this->m_target)
    {
        (this->m_target->*this->m_callback)();
    }
}
