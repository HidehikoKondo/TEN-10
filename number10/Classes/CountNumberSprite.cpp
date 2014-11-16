//
//  CountNumber.cpp
//  rendaPower
//
//  Created by ooharayukio on 2014/05/28.
//
//

#include "CountNumberSprite.h"

USING_NS_CC;

bool CountNumberSprite::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    
    this->m_countLabel = CCLabelBMFont::create("0", "base/bmfRocket.fnt", 60,kCCTextAlignmentCenter);
    this->m_countLabel->setAnchorPoint(ccp(0,0));
    this->addChild(this->m_countLabel);
    
    this->setContentSize(CCSizeMake(70, 70));
    
    return true;
}
CountNumberSprite::CountNumberSprite()
:m_Count(0)
,m_type(CT_UP)
,m_countLabel(NULL)
,m_Add(1)
,m_Interval(1.0f)
,m_EndCallback(NULL)
,m_MinCount(0)
,m_MaxCount(10)
,m_EndCallbackTarget(NULL)
{
    
}
CountNumberSprite::~CountNumberSprite()
{
    
}

void CountNumberSprite::startCount()
{
    onCountUp();
}
void CountNumberSprite::stopCount()
{
    this->stopAllActions();
}
void CountNumberSprite::resetCount()
{
    switch (m_type)
    {
        case CT_DOWN:
            this->m_Count = this->m_MaxCount;
            break;
            
        case CT_UP:
        default:
            this->m_Count = this->m_MinCount;
            break;
    }
}

/**
 * カウントアップイベント
 */
void CountNumberSprite::onCountUp()
{

    //ラベルの文字設定
    char moji[5] = "";
    sprintf(moji, "%ld",this->m_Count);
    this->m_countLabel->setString(moji);
    
    //判定
    if(this->m_type == CT_DOWN)
    {
        if(this->m_Count <= this->m_MinCount)
        {
            onCountEnd();
            return;
        }
    }
    else
    {
        if(this->m_Count >= this->m_MaxCount)
        {
            onCountEnd();
            return;
        }
    }
    
    //アニメーション設定
    CCArray * count = CCArray::create();
    count->addObject(CCDelayTime::create(this->m_Interval));
    count->addObject(CCCallFunc::create(this, callfunc_selector(CountNumberSprite::onCountUp)));
    CCSequence *seq = CCSequence::create(count);
    runAction(seq);
    
    //増加
    if(this->m_type == CT_DOWN)
    {
        this->m_Count -= this->m_Add;
    }
    else
    {
        this->m_Count += this->m_Add;
    }
}
/**
 * カウント終了
 */
void CountNumberSprite::onCountEnd()
{
    if(this->m_EndCallbackTarget)
    {
        (this->m_EndCallbackTarget->*this->m_EndCallback)();
    }
}

/**
 * コールバックの設定
 */
void CountNumberSprite::setEndCallback(cocos2d::CCObject* endCallbackTarget,cocos2d::SEL_CallFunc endCallback)
{
    CC_SAFE_RELEASE_NULL(this->m_EndCallbackTarget);
    this->m_EndCallbackTarget = endCallbackTarget;
    CC_SAFE_RETAIN(this->m_EndCallbackTarget);
    
    this->m_EndCallback = endCallback;
}

#pragma mark ゲッターセッター
//====================================
// ゲッターセッター
//====================================
void CountNumberSprite::setType(COUNT_TYPE val)
{
    this->m_type = val;
}
COUNT_TYPE CountNumberSprite::getType()
{
    return this->m_type;
}

void CountNumberSprite::setMin(long val)
{
    this->m_MinCount = val;
}
long CountNumberSprite::getMin()
{
    return this->m_MinCount;
}
void CountNumberSprite::setMax(long val)
{
    this->m_MaxCount = val;
}
long CountNumberSprite::getMax()
{
    return this->m_MaxCount;
}
void CountNumberSprite::setAdd(long val)
{
    this->m_Add = val;
}
long CountNumberSprite::getAdd()
{
    return this->m_Add;
}
void CountNumberSprite::setInterval(long val)
{
    this->m_Interval = val;
}
long CountNumberSprite::getInterval()
{
    return this->m_Interval;
}
