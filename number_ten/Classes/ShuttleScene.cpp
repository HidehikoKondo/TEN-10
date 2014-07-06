//
//  ShuttleScene.cpp
//  rendaPower
//
//  Created by 大原幸夫 on 2014/02/23.
//
//

#include "ShuttleScene.h"

#define DEF_PRINTSTR_HISCORE    ("HiScore %8ld")
#define DEF_PRINTSTR_SCORE      ("Score   %8ld")
#define DEF_PRINTSTR_SPEED      ("Speed %4ld")
#define DEF_PRINTSTR_POWER      ("Power %4ld")


#define DEF_BG_HEIGHT   (4000)

#define DEF_TAG_RUSH_BTN (10000)

#define DEF_Z_UI (1000)

#define DEF_RUSH_TIME (10)
using namespace cocos2d;

/**
 * コンストラクタ
 */
ShuttleScene::ShuttleScene()
:m_ReadyLabel(NULL)
,m_ScoreLabel(NULL)
,m_PowerLabel(NULL)
,m_HiScoreLabel(NULL)
,m_SpeedLabel(NULL)
,m_menu(NULL)
,m_PlanetSprite(NULL)
,m_RocketSprite(NULL)
,m_CloudSprite1(NULL)
,m_CloudSprite2(NULL)
,m_BackGroundLayer(NULL)
,m_CountSprite(NULL)
,m_shotSceneState(SSHOT_NONE)
,m_moveShuttle(false)
,m_Score(0)
,m_HiScore(0)
,m_ScoreBackGround(NULL)
{
    
}
/**
 * デストラクタ
 */
ShuttleScene::~ShuttleScene()
{
    
}

CCScene* ShuttleScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    ShuttleScene *layer = ShuttleScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ShuttleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();

        
    //背景
    CCSprite * backGroundUp = CCSprite::create("base/rocketBackGraund_up.png");
    CCSprite * backGroundDown = CCSprite::create("base/rocketBackGraund_down.png");
    m_BackGroundLayer = CCLayerGradient::create(ccc4(0x0, 0x0, 0x0, 0xFF), ccc4(0x3a, 0x3a, 0x3a, 0xff));
    this->m_BackGroundLayer->setContentSize(CCSizeMake(size.width, DEF_BG_HEIGHT + size.height));
    this->m_BackGroundLayer->addChild(backGroundUp,1);
    this->m_BackGroundLayer->addChild(backGroundDown,1);
    backGroundUp->setAnchorPoint(ccp(0.5f,0.0f));
    backGroundUp->setPosition(ccp(this->m_BackGroundLayer->getContentSize().width * 0.5f,
                                  this->m_BackGroundLayer->getContentSize().height * 0.5f));
    backGroundDown->setAnchorPoint(ccp(0.5f,1.0f));
    backGroundDown->setPosition(ccp(this->m_BackGroundLayer->getContentSize().width * 0.5f,
                                  this->m_BackGroundLayer->getContentSize().height * 0.5f));
    this->addChild(this->m_BackGroundLayer,0);
    
    this->m_PlanetSprite = CCSprite::create("base/planet.png");
    this->m_RocketSprite = ShuttleModel::create();
    this->m_CloudSprite1 = CCSprite::create("base/kumo.png");
    this->m_CloudSprite2 = CCSprite::create("base/kumo.png");
    
    this->m_BackGroundLayer->addChild(this->m_PlanetSprite, 10);
    this->m_BackGroundLayer->addChild(this->m_CloudSprite1, 15);
    this->m_BackGroundLayer->addChild(this->m_CloudSprite2, 16);
    this->m_BackGroundLayer->addChild(this->m_RocketSprite, 20);
    
    
    // position the sprite on the center of the screen
    this->m_PlanetSprite->setPosition(
                                      ccp(
                                          size.width * 0.5f,
                                        DEF_BG_HEIGHT + size.height * 0.5f) );

    this->m_menu = CCMenu::create();
    
    //RUSHボタンの生成
    CCSprite* normalSprite = CCSprite::create("base/tap_button.png");
    CCSprite* selectSprite = CCSprite::create("base/tap_button.png");
    selectSprite->setColor(ccc3(0x7F, 0x7F, 0x7F));
    CCMenuItemSprite * menuPush = CCMenuItemSprite::create(normalSprite, selectSprite);
    menuPush->setTarget(this, menu_selector(ShuttleScene::tapRushButton));
    menuPush->setTag(DEF_TAG_RUSH_BTN);
    this->m_menu->addChild(menuPush);
    // add the sprite as a child to this layer
    this->addChild(this->m_menu, 5000);
    
    //UIの初期位置設定
    char buff[100] = "";
    this->m_HiScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("HiScore", 0);
    
    //ハイスコア
    sprintf(buff,DEF_PRINTSTR_HISCORE,this->m_HiScore);
    this->m_HiScoreLabel = CCLabelBMFont::create(buff, "base/bmfRocket.fnt");
    this->m_HiScoreLabel->setAnchorPoint(ccp(0.0,1.0f));
    this->m_HiScoreLabel->setPosition(ccp(0,size.height));
    //スコア
    sprintf(buff,DEF_PRINTSTR_SCORE,this->m_Score);
    this->m_ScoreLabel = CCLabelBMFont::create(buff, "base/bmfRocket.fnt");
    this->m_ScoreLabel->setAnchorPoint(ccp(0.0,1.0f));
    this->m_ScoreLabel->setPosition(
                                    ccp(0,
                                        size.height -
                                        this->m_HiScoreLabel->getContentSize().height));

    //レディーラベル
    this->m_ReadyLabel = CCLabelBMFont::create("", "base/bmfRocket.fnt");
    this->m_ReadyLabel->setPosition(ccp(size.width * 0.5f,size.height * 0.5f));

    //スピードラベル
    sprintf(buff,DEF_PRINTSTR_SPEED,0L);
    this->m_SpeedLabel = CCLabelBMFont::create(buff, "base/bmfRocket.fnt");
    this->m_SpeedLabel->setAnchorPoint(ccp(0,0));
    this->m_SpeedLabel->setPosition(ccp(0,0));
    
    //パワーラベル
    sprintf(buff,DEF_PRINTSTR_POWER,0L);
    this->m_PowerLabel = CCLabelBMFont::create(buff, "base/bmfRocket.fnt");
    this->m_PowerLabel->setAnchorPoint(ccp(0,0));
    this->m_PowerLabel->setPosition(ccp(0,
                                        this->m_SpeedLabel->getContentSize().height));
    
    this->addChild(this->m_HiScoreLabel,DEF_Z_UI);
    this->addChild(this->m_ScoreLabel,DEF_Z_UI);
    this->addChild(this->m_ReadyLabel,DEF_Z_UI);
    this->addChild(this->m_SpeedLabel,DEF_Z_UI);
    this->addChild(this->m_PowerLabel,DEF_Z_UI);
    
    
    //ボタンの位置
    menuPush->setPosition(ccp(size.width -
                              menuPush->getContentSize().width * 0.5f,
                              menuPush->getContentSize().height * 0.5f));
    this->m_menu->setPosition(0, 0);
    this->m_ReadyLabel->setPosition(ccp(size.width * 0.5f,size.height * 0.5f));
    
    //カウントダウンスプライト
    this->m_CountSprite = CountNumberSprite::create();
    this->m_CountSprite->setAdd(1);
    this->m_CountSprite->setInterval(2.0f);
    this->m_CountSprite->setMax(5);
    this->m_CountSprite->setMin(0);
    this->m_CountSprite->setType(CT_DOWN);
    this->m_CountSprite->setEndCallback(this, callfunc_selector(ShuttleScene::shotChenge));
    this->m_CountSprite->setPosition(ccp(size.width * 0.5f,size.height * 0.25f));
    this->addChild(this->m_CountSprite,DEF_Z_UI);

    //スコア表示画面
    this->m_ScoreBackGround = ScoreLayer::create();
    this->m_ScoreBackGround->setPosition(ccp(0,0));
    this->m_ScoreBackGround->setVisible(false);
    this->m_ScoreBackGround->setRetryCallback(this, callfunc_selector(ShuttleScene::shotChenge));
    this->addChild(this->m_ScoreBackGround,DEF_Z_UI + 1);
    
    //開始
    shotChenge();
    
    return true;
}

/**
 * 設定をシーンによって変える
 */
void ShuttleScene::settingShotSceneObject(SHOT_SECNE val)
{
    switch (val) {
        case SSHOT_INIT: //初期準備
            this->planetLookAnime();
            break;
        case SSHOT_READY:
            this->readyCheck();
            break;
        case SSHOT_PUSH_PLAY:
            this->pushRushPlay();
            break;
        case SSHOT_SHUTTLE_TAKEOFF:
            this->launchShuttleAnime();
            break;
        case SSHOT_SHUTTLE_MOVE:
            this->launchShuttleMove();
            break;
        case SSHOT_SCORE:
            this->scoreView();
            break;
        case SSHOT_RETRY:
            this->retryView();
            break;
            
        default:
            break;
    }
}
/**
 * 次の設定シーンを取得する
 */
ShuttleScene::SHOT_SECNE ShuttleScene::nextShotSceneSelecter(SHOT_SECNE val)
{
    SHOT_SECNE ret = SSHOT_NONE;
    
    switch (val) {
        case SSHOT_INIT:
            ret = SSHOT_READY;
            break;
        case SSHOT_READY:
            ret = SSHOT_PUSH_PLAY;
            break;
        case SSHOT_PUSH_PLAY:
            ret = SSHOT_SHUTTLE_TAKEOFF;
            break;
        case SSHOT_SHUTTLE_TAKEOFF:
            ret = SSHOT_SHUTTLE_MOVE;
            break;
        case SSHOT_SHUTTLE_MOVE:
            ret = SSHOT_SCORE;
            break;
        case SSHOT_SCORE:
            ret = SSHOT_RETRY;
            break;
        case SSHOT_RETRY:
        default:
            ret = SSHOT_INIT;
            break;
    }
    
    return ret;
}

/**
 * シーンを切り替える
 */
void ShuttleScene::shotChenge()
{
    //数値更新
    this->refreshStetusLabel();

    //次のシーンを選択
    this->m_shotSceneState = nextShotSceneSelecter(m_shotSceneState);
    
    //カットシーンに合わせて修正
    this->settingShotSceneObject(m_shotSceneState);
}

/**
 * ラッシュボタンのタップ
 */
void ShuttleScene::tapRushButton()
{
    if(this->m_shotSceneState == SSHOT_READY)
    {
        this->shotChenge();
    }
    
    //エネルギーチャージ
    this->m_RocketSprite->chargeEnergy();
    
    //項目の更新
    this->refreshStetusLabel();
}

/**
 * 数値関連の数値更新
 */
void ShuttleScene::refreshStetusLabel()
{
    char buff[100];
    
    //ハイスコア
    sprintf(buff,DEF_PRINTSTR_HISCORE,this->m_HiScore);
    this->m_HiScoreLabel->setString(buff);
    
    //スコア
    sprintf(buff,DEF_PRINTSTR_SCORE,this->m_Score);
    this->m_ScoreLabel->setString(buff);
    
    //スピードラベル
    sprintf(buff,DEF_PRINTSTR_SPEED,this->m_RocketSprite->getSpeed());
    this->m_SpeedLabel->setString(buff);
    
    //パワーラベル
    sprintf(buff,DEF_PRINTSTR_POWER,this->m_RocketSprite->getEnergy());
    this->m_PowerLabel->setString(buff);
    
}
/**
 * UIオブジェクトの表示非表示
 */
void ShuttleScene::UIsVisible(bool val)
{
    this->m_menu->setVisible(val);
    this->m_HiScoreLabel->setVisible(val);
    this->m_ScoreLabel->setVisible(val);
    this->m_SpeedLabel->setVisible(val);
    this->m_PowerLabel->setVisible(val);
}
/**
 * 画面更新
 */
void ShuttleScene::update(float delta)
{
    CCNode::update(delta);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //テイクオフ後の打ち上げに追従する
    if(m_moveShuttle)
    {
        CCPoint roketPos = this->m_RocketSprite->getPosition();
        CCPoint bkgPos = ccpSub(roketPos, ccp(size.width * 0.5f,size.height * 0.5f));
        this->m_BackGroundLayer->setPosition(-bkgPos);

        m_Score = bkgPos.y;
        
        this->m_PlanetSprite->setScale( 1.0f + (-this->m_BackGroundLayer->getPosition().y / DEF_BG_HEIGHT) * 3 );
        
        //終了条件
        if(this->m_RocketSprite->getSpeed() <= 0
           || this->m_BackGroundLayer->getPosition().y + DEF_BG_HEIGHT <= 0)
        {
            //ページ切り替え
            this->shotChenge();
        }
        
        this->refreshStetusLabel();
    }
}

#pragma mark カットシーン処理類
/**
 * 惑星を見上げたところからのアニメーション
 */
void ShuttleScene::planetLookAnime()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //ラベル類初期化
    this->m_ReadyLabel->setVisible(false);
    this->m_CountSprite->setVisible(false);
    this->m_CountSprite->resetCount();
    this->m_ScoreBackGround->setVisible(false);
    
    //ロケット初期位置
    this->m_RocketSprite->setPosition(size.width * 0.5f,size.height * 0.5f);
    this->m_RocketSprite->resetParam();

    this->m_PlanetSprite->setScale(1.0f);
    
    //雲の配置
    this->m_CloudSprite1->setPosition(ccp(this->m_PlanetSprite->getPosition().x - 30.0f,
                                          this->m_PlanetSprite->getPosition().y + 5));
    this->m_CloudSprite2->setPosition(ccp(this->m_PlanetSprite->getPosition().x + 30.0f,
                                          this->m_PlanetSprite->getPosition().y - 5));
    this->m_CloudSprite1->setOpacity(0xFF);
    this->m_CloudSprite2->setOpacity(0xFF);
    this->m_CloudSprite1->setScale(1.5f);
    this->m_CloudSprite2->setScale(1.5f);
    
    //背景見上げる
    this->m_BackGroundLayer->setPosition(
                                         ccp(this->m_BackGroundLayer->getPosition().x,
                                             - DEF_BG_HEIGHT));
    CCArray * seqlist = CCArray::create();
    seqlist->addObject(CCDelayTime::create(2.5f));
    seqlist->addObject(CCMoveTo::create(1.5f, ccp(this->m_BackGroundLayer->getPosition().x,0)));
    seqlist->addObject(CCCallFunc::create(this, callfunc_selector(ShuttleScene::shotChenge)));
    this->m_BackGroundLayer->runAction(CCSequence::create(seqlist));
    
    //雲が開けるアニメーション
    this->m_CloudSprite1->runAction(CCSequence::create(CCDelayTime::create(1.0f),
                                                       CCSpawn::createWithTwoActions(
                                                                                     CCMoveBy::create(1, ccp(-100, 0)),
                                                                                     CCFadeTo::create(1,0)
                                                                                     )
                                                       ,NULL)
                                    );
    this->m_CloudSprite2->runAction(CCSequence::create(CCDelayTime::create(1.0f),
                                                       CCSpawn::createWithTwoActions(
                                                                                     CCMoveBy::create(1, ccp(100, 0)),
                                                                                     CCFadeTo::create(1,0)
                                                                                     )
                                                       ,NULL)
                                    );
    
    //ステータスやボタンを押せなくする
    this->UIsVisible(false);
}
/**
 * 準備完了？の処理
 */
void ShuttleScene::readyCheck()
{
    this->m_ReadyLabel->setVisible(true);
    this->m_ReadyLabel->setString("Are you ready?");
    
    this->UIsVisible(true);
}
/**
 * RUSHタイム
 */
void ShuttleScene::pushRushPlay()
{
    this->m_ReadyLabel->setVisible(false);
    this->m_CountSprite->setVisible(true);

    this->m_CountSprite->startCount();
}
/**
 * シャトル発射
 */
void ShuttleScene::launchShuttleAnime()
{
    this->m_menu->setVisible(false);
    this->m_CountSprite->setVisible(false);
    
    this->m_RocketSprite->rocketStart(this, callfunc_selector(ShuttleScene::shotChenge));
}

/**
 * シャトル飛ぶ
 */
void ShuttleScene::launchShuttleMove()
{
    CCArray * seq = CCArray::create();
    seq->addObject(CCDelayTime::create(0.5f));
    seq->addObject( CCCallFunc::create(this,callfunc_selector(ShuttleScene::scheduleUpdate)));
    runAction(CCSequence::create(seq));

    this->m_moveShuttle = true;
}
/**
 * スコア表示
 */
void ShuttleScene::scoreView()
{
    //アップデート停止
    this->unscheduleUpdate();
    
    this->m_moveShuttle = false;
    
    if(this->m_HiScore < this->m_Score)
    {
        this->m_HiScore = this->m_Score;
        CCUserDefault::sharedUserDefault()->setIntegerForKey("HiScore", this->m_HiScore);
    }
    
    this->m_ScoreBackGround->setVisible(true);
    this->m_ScoreBackGround->setScore(this->m_Score, this->m_HiScore);
    this->m_ScoreBackGround->setVisibleRetryButton(false);
    
    //すぐ次のシーン
    CCArray * seq = CCArray::create();
    seq->addObject(CCDelayTime::create(1));
    seq->addObject(CCCallFunc::create(this, callfunc_selector(ShuttleScene::shotChenge)));    
    this->runAction(CCSequence::create(seq));
}

/**
 * リトライ表示
 */
void ShuttleScene::retryView()
{
    this->m_ScoreBackGround->setVisibleRetryButton(true);
}


