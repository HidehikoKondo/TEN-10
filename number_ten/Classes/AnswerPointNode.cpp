//
//  AnswerPointNode.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/11/12.
//
//

#include "AnswerPointNode.h"
#include "GameRuleManager.h"

#define DEF_LABEL_STR_FORMAT ("AP:%6lu")
USING_NS_CC;

AnswerPointNode::AnswerPointNode()
:m_count(1)
,m_CountStrLablel(NULL)
,m_target(NULL)
{
    
}
AnswerPointNode::~AnswerPointNode()
{
    CC_SAFE_RELEASE_NULL(this->m_target);
}
bool AnswerPointNode::init()
{
    if(!CCNode::init())
    {
        return false;
    }
    this->setContentSize(CCSizeMake(640, 50));
    
    char buff[30]="";
    memset(buff, 0, 30);
    
    sprintf(buff, DEF_LABEL_STR_FORMAT,GameRuleManager::getInstance()->getAnswerPoint());
    
    this->m_CountStrLablel = CCLabelBMFont::create(buff, "base/little_number2.fnt", 640, kCCTextAlignmentRight);
    this->m_CountStrLablel->setPosition(CCPointZero);
    this->m_CountStrLablel->setAnchorPoint(CCPointZero);
    this->addChild(this->m_CountStrLablel);
    this->ignoreAnchorPointForPosition(false);
    
    return true;
}
/**
 * カウント最大値に達すると呼ばれる
 */
void AnswerPointNode::setTarget(CCObject* target,cocos2d::SEL_CallFunc func)
{
    CC_SAFE_RELEASE_NULL(this->m_target);
    this->m_target = target;
    CC_SAFE_RETAIN(this->m_target);
    
    this->m_func = func;
    
}

/**
 * ポイントの取得
 */
void AnswerPointNode::onGetAnserPoint()
{
    GameRuleManager::getInstance()->addAnswerPoint();

    char buff[256];
    sprintf(buff, DEF_LABEL_STR_FORMAT,GameRuleManager::getInstance()->getAnswerPoint());
    this->m_CountStrLablel->setString(buff);

    if(this->m_target)
    {
        //変更完了コールバック
        (this->m_target->*this->m_func)();
    }
}

/**
 * ポイントの消費
 */
void AnswerPointNode::onPayAnserPoint()
{
    GameRuleManager::getInstance()->subAnswerPoint();
    char buff[256];
    sprintf(buff, DEF_LABEL_STR_FORMAT,GameRuleManager::getInstance()->getAnswerPoint());
    this->m_CountStrLablel->setString(buff);
    
    if(this->m_target)
    {
        //変更完了コールバック
        (this->m_target->*this->m_func)();
    }
}

/**
 * ポイントの消費
 */
bool AnswerPointNode::isPayAnserPoint()
{
    return GameRuleManager::getInstance()->isAnswerPointToSub();
}