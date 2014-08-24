//
//  TimeCounterNode.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/21.
//
//

#include "TimeCounterNode.h"


USING_NS_CC;

TimeCounterNode::TimeCounterNode()
:m_count(10)
,m_TimerMode(TM_COUNT_DOWN)
,m_CountMax(10)
,m_CountStrLablel(NULL)
,m_target(NULL)
{
    
}
TimeCounterNode::~TimeCounterNode()
{
    CC_SAFE_RELEASE_NULL(this->m_target);
}
bool TimeCounterNode::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    
    this->setContentSize(CCSizeMake(100, 30));
    
    this->m_CountStrLablel = CCLabelBMFont::create("00:00", "base/little_number2.fnt", 100, kCCTextAlignmentRight);
    this->m_CountStrLablel->setPosition(CCPointZero);
    this->m_CountStrLablel->setAnchorPoint(CCPointZero);
    this->addChild(this->m_CountStrLablel);
    
    this->viewReflesh();
    
    return true;
}
/**
 * カウント最大値に達すると呼ばれる
 */
void TimeCounterNode::setTarget(CCObject* target,cocos2d::SEL_CallFunc func)
{
    CC_SAFE_RELEASE_NULL(this->m_target);
    this->m_target = target;
    CC_SAFE_RETAIN(this->m_target);
    
    this->m_func = func;
    
}
/**
 * カウントアップする
 */
void TimeCounterNode::countUp()
{
    if(this->m_TimerMode == TM_COUNT_DOWN)
    {
        if(this->m_count > 0)
        {
            this->m_count--;
            this->viewReflesh();
            //再度タイマー発動
            this->start();
        }
        else
        {
            if(this->m_target)
            {
                //最大値到達コールバック
                (this->m_target->*this->m_func)();
            }
        }
    }
    else
    {
        if(this->m_count < this->m_CountMax)
        {
            this->m_count++;
            this->viewReflesh();
            //再度タイマー発動
            this->start();
        }
        else
        {
            if(this->m_target)
            {
                //最大値到達コールバック
                (this->m_target->*this->m_func)();
            }
        }
    }
}
/**
 * 表示を更新する
 */
void TimeCounterNode::viewReflesh()
{
    char buff[30];
    sprintf(buff,"%2ld:%02ld",static_cast<long>(this->m_count/ 60),this->m_count%60);
    this->m_CountStrLablel->setString(buff);
}

/**
 * カウンターをリセットする
 */
void TimeCounterNode::resetCounter()
{
    if(this->m_TimerMode == TM_COUNT_DOWN)
    {
        this->m_count = this->m_CountMax;
    }
    else
    {
        this->m_count = 0;
    }
    
    this->viewReflesh();
}
/**
 * タイマーを開始する
 */
void TimeCounterNode::start()
{
    CCArray *seq = CCArray::create();
    seq->addObject(CCDelayTime::create(1.0f));
    seq->addObject(CCCallFunc::create(this, callfunc_selector(TimeCounterNode::countUp)));
    this->runAction(CCSequence::create(seq));
}
/**
 * タイマーを停止する
 */
void TimeCounterNode::stop()
{
    this->stopAllActions();
}
/**
 * カウンターの数値を取得
 */
long TimeCounterNode::getCounterValue()
{
    return this->m_count;
}

