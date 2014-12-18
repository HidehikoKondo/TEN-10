//
//  AnswerPointNode.h
//  number_ten
//
//  Created by 大原幸夫 on 2014/11/12.
//
//

#ifndef __number_ten__AnswerPointNode__
#define __number_ten__AnswerPointNode__

#include "cocos2d.h"

class AnswerPointNode : public cocos2d::CCNode
{
protected:
    long m_count;
    cocos2d::CCLabelBMFont * m_CountStrLablel;
    
    cocos2d::CCObject * m_target;
    cocos2d::SEL_CallFunc m_func;
    
public:
    CREATE_FUNC(AnswerPointNode);
    AnswerPointNode();
    virtual ~AnswerPointNode();
    virtual bool init();
    
    /**
     * カウント最大値に達すると呼ばれる
     */
    void setTarget(CCObject* target,cocos2d::SEL_CallFunc func);
    
    /**
     * ポイントの取得
     */
    void onGetAnserPoint();
    
    /**
     * ポイントの消費
     */
    void onPayAnserPoint();

    /**
     * ポイントの消費
     */
    bool isPayAnserPoint();
    
};

#endif /* defined(__number_ten__AnswerPointNode__) */
