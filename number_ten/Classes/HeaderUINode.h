//
//  HeaderUINode.h
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#ifndef __number_ten__HeaderUINode__
#define __number_ten__HeaderUINode__

#include "cocos2d.h"
#include "GameRuleManager.h"

/**
 * ヘッダーUIノード
 */
class HeaderUINode : public cocos2d::CCNode
{
protected:
    unsigned long m_Timer;
    unsigned long m_QuestionCount;
    
    cocos2d::CCLabelBMFont * m_QuestionCountString;
    cocos2d::CCLabelBMFont * m_TimeString;
public:
    CREATE_FUNC(HeaderUINode);
    virtual bool init();
    
    /**
     * タイマーをリセットする。
     */
    void resetTimer();

    /**
     * ゲームモードを設定する
     */
    void setMode(GAME_MODE mode);
};

#endif /* defined(__number_ten__HeaderUINode__) */
