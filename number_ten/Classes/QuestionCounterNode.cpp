//
//  QuestionCounterNode.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/21.
//
//

#include "QuestionCounterNode.h"

USING_NS_CC;

QuestionCounterNode::QuestionCounterNode()
:m_count(1)
,m_CountMax(99)
,m_CountStrLablel(NULL)
,m_target(NULL)
{
    
}
QuestionCounterNode::~QuestionCounterNode()
{
    CC_SAFE_RELEASE_NULL(this->m_target);
}
bool QuestionCounterNode::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    this->setContentSize(CCSizeMake(200, 30));
    
    this->m_CountStrLablel = CCLabelBMFont::create("Q. 1", "base/little_number2.fnt", 200, kCCTextAlignmentLeft);
    this->m_CountStrLablel->setPosition(CCPointZero);
    this->m_CountStrLablel->setAnchorPoint(CCPointZero);
    this->addChild(this->m_CountStrLablel);
    
    return true;
}
/**
 * カウント最大値に達すると呼ばれる
 */
void QuestionCounterNode::setTarget(CCObject* target,cocos2d::SEL_CallFunc func)
{
    CC_SAFE_RELEASE_NULL(this->m_target);
    this->m_target = target;
    CC_SAFE_RETAIN(this->m_target);
    
    this->m_func = func;
    
}
/**
 * カウントアップする
 */
void QuestionCounterNode::countUp()
{
    this->m_count++;
    
    if(this->m_count < this->m_CountMax)
    {        
        char buff[256];
        sprintf(buff, "Q.%2ld",this->m_count);
        this->m_CountStrLablel->setString(buff);
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
void QuestionCounterNode::resetCounter()
{
    this->m_count = 1;
}
long QuestionCounterNode::getCounterValue()
{
    return this->m_count - 1;
}