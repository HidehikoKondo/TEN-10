//
//  ShuttleScene.h
//  rendaPower
//
//  Created by 大原幸夫 on 2014/02/23.
//
//

#ifndef __rendaPower__PlayScene__
#define __rendaPower__PlayScene__

#include "cocos2d.h"
#include "ShuttleModel.h"
#include "CountNumberSprite.h"
#include "ScoreLayer.h"

/**
 * スペースシャトルのゲームプレイ
 */
class ShuttleScene : public cocos2d::CCLayer
{
protected:
    cocos2d::CCSprite * m_PlanetSprite;
    ShuttleModel * m_RocketSprite;
    cocos2d::CCSprite * m_CloudSprite1;
    cocos2d::CCSprite * m_CloudSprite2;
    cocos2d::CCLayerGradient * m_BackGroundLayer;
    
    cocos2d::CCMenu * m_menu;
    
    cocos2d::CCLabelBMFont * m_HiScoreLabel;
    cocos2d::CCLabelBMFont * m_ScoreLabel;
    cocos2d::CCLabelBMFont * m_ReadyLabel;
    cocos2d::CCLabelBMFont * m_SpeedLabel;
    cocos2d::CCLabelBMFont * m_PowerLabel;
    
    CountNumberSprite * m_CountSprite;
    
    bool m_moveShuttle;
    
    long m_Score;
    long m_HiScore;

    
    enum SHOT_SECNE
    {
        SSHOT_NONE = -1,
        SSHOT_INIT = 0,
        SSHOT_READY,
        SSHOT_START_COUNT,
        SSHOT_PUSH_PLAY,
        SSHOT_SHUTTLE_TAKEOFF,
        SSHOT_SHUTTLE_MOVE,
        SSHOT_SCORE,
        SSHOT_RETRY
    };
    
    SHOT_SECNE m_shotSceneState;
    
    ScoreLayer * m_ScoreBackGround;

    /**
     * 設定をシーンによって変える
     */
    virtual void settingShotSceneObject(SHOT_SECNE val);

    /**
     * 次の設定シーンを取得する
     */
    virtual SHOT_SECNE nextShotSceneSelecter(SHOT_SECNE val);
    
    /**
     * 画面更新
     */
    virtual void update(float delta);
    
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    /**
     * コンストラクタ
     */
    ShuttleScene();
    /**
     * デストラクタ
     */
    ~ShuttleScene();
        
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(ShuttleScene);
    
    /**
     * シーンを切り替える
     */
    virtual void shotChenge();
    
    /**
     * ラッシュボタンのタップ
     */
    virtual void tapRushButton();
    
    /**
     * 数値関連の数値更新
     */
    virtual void refreshStetusLabel();
    
    /**
     * UIオブジェクトの表示非表示
     */
    virtual void UIsVisible(bool val);

#pragma mark カットシーン処理類
    /**
     * 惑星を見上げたところからのアニメーション
     */
    virtual void planetLookAnime();

    /**
     * 準備完了？の処理
     */
    virtual void readyCheck();
    
    /**
     * RUSHタイム
     */
    virtual void pushRushPlay();
    
    /**
     * シャトル発射
     */
    virtual void launchShuttleAnime();
    
    /**
     * シャトル飛ぶ
     */
    virtual void launchShuttleMove();
    
    /**
     * スコア表示
     */
    virtual void scoreView();

    /**
     * リトライ表示
     */
    virtual void retryView();
};

#endif /* defined(__rendaPower__PlayScene__) */
