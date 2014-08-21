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
:m_count(1)
,m_CountMax(99)
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
    if(this->m_count < this->m_CountMax)
    {
        this->m_count++;
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
/**
 * カウンターをリセットする
 */
void TimeCounterNode::resetCounter()
{
    this->m_count = 1;
}
