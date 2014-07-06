//
//  NumberTenScene.h
//  number_ten
//
//  Created by 大原幸夫 on 2014/07/06.
//
//

#ifndef __number_ten__NumberTenScene__
#define __number_ten__NumberTenScene__

#include "cocos2d.h"

#define DEF_MAX_STAGE (10)

/**
 * ナンバー足しのゲームプレイ
 */
class NumberTenScene : public cocos2d::CCLayer
{
protected:
    unsigned long m_StageNo;
    
    unsigned long m_score;
   
    cocos2d::CCArray * m_buttonNumber;    //数値ボタン
    
    cocos2d::CCArray * m_buttonMarker;    //記号ボタン
    
    cocos2d::CCArray * m_QuestionNumber;
    
    cocos2d::CCLabelBMFont * m_InputNumber;
    /**
     * ナンバーの初期状態の設定する
     */
    virtual void stageInitSet();
        
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    /**
     * コンストラクタ
     */
    NumberTenScene();
    /**
     * デストラクタ
     */
    ~NumberTenScene();
    
    CREATE_FUNC(NumberTenScene);
    

};
#endif /* defined(__number_ten__NumberTenScene__) */
