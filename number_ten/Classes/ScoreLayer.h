//
//  ScoreLayer.h
//  rendaPower
//
//  Created by ooharayukio on 2014/06/02.
//
//

#ifndef __rendaPower__ScoreLayer__
#define __rendaPower__ScoreLayer__

#include "cocos2d.h"

class ScoreLayer : public cocos2d::CCLayerColor
{
protected:
    //スコア
    cocos2d::CCLabelTTF * m_ScoreLabel;
    //ハイスコア
    cocos2d::CCLabelTTF * m_HiScoreLabel;
    
    //現在のスコア
    cocos2d::CCLabelTTF * m_StrScoreSLabel;
    //現在のスコア
    cocos2d::CCLabelTTF * m_StrHiScoreSLabel;

    //リトライ
    cocos2d::CCMenuItemLabel * m_RetryLabelButton;
    //トップ画面
    cocos2d::CCMenuItemLabel * m_TopLabelButton;
    
    virtual void onMoveSceneTop();
    virtual void onRetry();
    
    cocos2d::CCObject * m_target;
    cocos2d::SEL_CallFunc m_callback;
    
public:
    CREATE_FUNC(ScoreLayer);
    virtual bool init();
    
    ScoreLayer();
    ~ScoreLayer();
    
    void setScore(unsigned long score,unsigned long hiscore);
    void setVisibleRetryButton(bool val);
    
    void setRetryCallback(cocos2d::CCObject * target,cocos2d::SEL_CallFunc callback);
    
};

#endif /* defined(__rendaPower__ScoreLayer__) */
