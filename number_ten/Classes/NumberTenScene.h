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
#include "ButtonFactory.h"
#include "QuestionCounterNode.h"
#include "TimeCounterNode.h"

#define DEF_MAX_STAGE (10)
/**
 * ナンバー足しのゲームプレイ
 */
class NumberTenScene : public cocos2d::CCLayer
{
protected:
    unsigned long m_StageNo;
    
    unsigned long m_score;
    
    unsigned long m_InputCount;
    
    //桁数
    unsigned long m_AnserDigit;
    
    NUMBER_BUTTON_TYPE m_AnserType[8];
   
    cocos2d::CCArray * m_buttonNumber;    //数値ボタン
    cocos2d::CCArray * m_buttonMarker;    //記号ボタン
    cocos2d::CCArray * m_usedButtonList;    //使用済みボタン
    
    cocos2d::CCMenuItem * m_buttonEnter;
    cocos2d::CCMenuItem * m_buttonBS;
    
    cocos2d::CCLabelBMFont * m_QuestionNumber;
    
    cocos2d::CCLabelBMFont * m_InputNumber;
    
    cocos2d::CCMenu * m_menu;
    
    QuestionCounterNode * m_QuestionCounter;
    TimeCounterNode * m_TimerCounter;
    
    /**
     * 記号ボタンの設定
     */
    virtual void initStageMarker();
    /**
     * ナンバーの初期状態の設定する
     */
    virtual void stageInitSet();
    
    /**
     * 押せるボタンの設定
     */
    virtual void chengePushButtonEnable();
    
    /**
     * クリアチェック
     */
    virtual void checkNumber();
        
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
    
    /**
     * ボタンのタップ
     */
    void onTapButton(cocos2d::CCObject* obj);
    
    /**
     * ゲームオーバー
     */
    void viewGameOverLayer();

};
#endif /* defined(__number_ten__NumberTenScene__) */
