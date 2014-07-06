//
//  CountNumberSprite.h
//  rendaPower
//
//  Created by ooharayukio on 2014/05/28.
//
//

#ifndef __rendaPower__CountNumber__
#define __rendaPower__CountNumber__

#include "cocos2d.h"

typedef enum _COUNT_TYPE
{
    CT_DOWN = 0,
    CT_UP
}COUNT_TYPE;

/**
 * カウントダウンスプライトクラス
 */
class CountNumberSprite : public cocos2d::CCNode
{
protected:
    cocos2d::CCObject* m_EndCallbackTarget;
    cocos2d::SEL_CallFunc m_EndCallback;
    
    long m_MinCount;    //最大値
    long m_MaxCount;    //最小値
    long m_Count;       //カウント数
    long m_Add;         //カウント増加量
    long m_Interval;    //カウント間隔
    COUNT_TYPE m_type;
    
    /**
     * カウントアップイベント
     */
    void onCountUp();
    
    void onCountEnd();
    
    cocos2d::CCLabelBMFont *m_countLabel;
    
public:
    
    CREATE_FUNC(CountNumberSprite);
    virtual bool init();

    CountNumberSprite();
    virtual ~CountNumberSprite();

    /**
     * コールバックの設定
     */
    void setEndCallback(cocos2d::CCObject* endCallbackTarget,cocos2d::SEL_CallFunc endCallback);

    void startCount();
    void stopCount();
    void resetCount();
    void setType(COUNT_TYPE val);
    COUNT_TYPE getType();
    
    void setMin(long val);
    long getMin();
    void setMax(long val);
    long getMax();
    void setAdd(long val);
    long getAdd();
    void setInterval(long val);
    long getInterval();
    
};

#endif /* defined(__rendaPower__CountNumber__) */
