//
//  TimeCounterNode.h
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/21.
//
//

#ifndef __number_ten__TimeCounterNode__
#define __number_ten__TimeCounterNode__

#include "cocos2d.h"

typedef enum _TIMER_MODE
{
    TM_COUNT_DOWN,
    TM_COUNT_UP
}TIMER_MODE;

class TimeCounterNode : public cocos2d::CCNode
{
protected:
    CC_SYNTHESIZE(TIMER_MODE, m_TimerMode, TimerMode);
    CC_SYNTHESIZE(long, m_CountMax, CountMax);
    
    long m_count;
    cocos2d::CCLabelBMFont * m_CountStrLablel;
    
    cocos2d::CCObject * m_target;
    cocos2d::SEL_CallFunc m_func;
    
    /**
     * カウントアップする
     */
    void countUp();
    
    /**
     * 表示を更新する
     */
    void viewReflesh();
    
public:
    CREATE_FUNC(TimeCounterNode);
    TimeCounterNode();
    virtual ~TimeCounterNode();
    virtual bool init();
    
    /**
     * カウント最大値に達すると呼ばれる
     */
    void setTarget(CCObject* target,cocos2d::SEL_CallFunc func);
    
    /**
     * カウンターをリセットする
     */
    void resetCounter();
    
    /**
     * タイマーを開始する
     */
    void start();
    /**
     * タイマーを停止する
     */
    void stop();
};
#endif /* defined(__number_ten__TimeCounterNode__) */
