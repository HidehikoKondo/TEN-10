//
//  GameOverLayer.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/20.
//
//

#include "GameOverLayer.h"

USING_NS_CC;

GameOverLayer::GameOverLayer()
{
    
}
GameOverLayer::~GameOverLayer()
{
    
}

bool GameOverLayer::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    this->m_GameOverString = CCSprite::create("base/game_over_title.png");
    this->m_GameOverString->setPosition(ccp(size.width * 0.5f,size.height * 0.75f));
    this->addChild(this->m_GameOverString);
    
    return true;
}


