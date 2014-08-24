//
//  NumberTenScene.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/07/06.
//
//

#include "NumberTenScene.h"
#include "SimpleAudioEngine.h"
#include "NativeCodeAst.h"
#include "SoundDef.h"
#include "GameRuleManager.h"
#include "GameOverLayer.h"

#define DEF_CENTER_OFFSET_H_VIEW_NUM  (200)
#define DEF_CENTER_OFFSET_H_INP_NUM   (0)
#define DEF_CENTER_OFFSET_H_BTN_NUM   (-100)
#define DEF_CENTER_OFFSET_H_BTN_MARK  (-200)
#define DEF_CENTER_OFFSET_H_BTN_ENT  (-300)

#define DEF_CHALENGE_MAX (30.0f)
#define DEF_CHALENGE_DOWN_COUNT (10)
#define DEF_CHALENGE_DOWN_TIME (5.0f)
#define DEF_CHALENGE_DOWN_MIN_TIME (10)

using namespace cocos2d;
using namespace CocosDenshion;

/**
 * コンストラクタ
 */
NumberTenScene::NumberTenScene()
:m_StageNo(0)
,m_menu(NULL)
,m_AnserDigit(4)
,m_buttonEnter(NULL)
,m_buttonBS(NULL)
,m_QuestionNumber(NULL)
,m_QuestionCounter(NULL)
,m_TimerCounter(NULL)
,m_QuestionData(NULL)
{
    this->m_buttonNumber = CCArray::create();
    CC_SAFE_RETAIN(this->m_buttonNumber);
    this->m_buttonMarker = CCArray::create();
    CC_SAFE_RETAIN(this->m_buttonMarker);
    this->m_usedButtonList = CCArray::create();
    CC_SAFE_RETAIN(this->m_usedButtonList);
}
/**
 * デストラクタ
 */
NumberTenScene::~NumberTenScene()
{
    CC_SAFE_RELEASE_NULL(this->m_buttonNumber);
    CC_SAFE_RELEASE_NULL(this->m_buttonMarker);
    CC_SAFE_RELEASE_NULL(this->m_usedButtonList);
    CC_SAFE_RELEASE_NULL(this->m_QuestionData);
}

CCScene* NumberTenScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    NumberTenScene *layer = NumberTenScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool NumberTenScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    m_QuestionNumber = CCLabelBMFont::create("5 3 8", "base/view_number.fnt",400,kCCTextAlignmentCenter);
    this->addChild(this->m_QuestionNumber);
    this->m_QuestionNumber->setPosition(ccp(size.width  * 0.5f , size.height * 0.5f + DEF_CENTER_OFFSET_H_VIEW_NUM));
    
    m_InputNumber = CCLabelBMFont::create(" ", "base/view_number.fnt",400,kCCTextAlignmentCenter);
    this->addChild(this->m_InputNumber);
    this->m_InputNumber->setPosition(ccp(size.width  * 0.5f , size.height * 0.5f + DEF_CENTER_OFFSET_H_INP_NUM));
    this->m_InputNumber->setScale(0.5f);
    
    this->m_menu = CCMenu::create();
    this->addChild(this->m_menu);
    this->m_menu->setPosition(ccp(0,0));
    
    //エンター
    this->m_buttonEnter = ButtonFactory::createButton(NBT_ENTER);
    this->m_buttonEnter->setTarget(this, menu_selector(NumberTenScene::onTapButton));
    this->m_buttonEnter->setPosition(ccp(size.width / 3 * 1 ,size.height * 0.5f + DEF_CENTER_OFFSET_H_BTN_ENT));
    this->m_menu->addChild(this->m_buttonEnter);
    //バックスペース
    this->m_buttonBS = ButtonFactory::createButton(NBT_BACK);
    this->m_buttonBS->setTarget(this, menu_selector(NumberTenScene::onTapButton));
    this->m_buttonBS->setPosition(ccp(size.width / 4 * 3 ,size.height * 0.5f + DEF_CENTER_OFFSET_H_BTN_ENT));
    this->m_menu->addChild(this->m_buttonBS);

    //問題数用ラベル
    this->m_QuestionCounter = QuestionCounterNode::create();
    this->m_QuestionCounter->setTarget(this, callfunc_selector(NumberTenScene::viewGameOverLayer));
    this->m_QuestionCounter->setPosition(ccp(0,size.height - this->m_QuestionCounter->getContentSize().height));
    this->addChild(this->m_QuestionCounter,100);
    
    //時間計測用用ラベル
    this->m_TimerCounter = TimeCounterNode::create();
    this->m_TimerCounter->setTarget(this, callfunc_selector(NumberTenScene::viewGameOverLayer));
    this->m_TimerCounter->setPosition(ccp(size.width - this->m_TimerCounter->getContentSize().width,
                                          size.height - this->m_QuestionCounter->getContentSize().height));
    this->addChild(this->m_TimerCounter,100);
    
    //ゲームモードによる設定
    if(GM_CHALENGE == GameRuleManager::getInstance()->getGameMode())
    {
        this->m_QuestionCounter->setCountMax(99);
        this->m_TimerCounter->setCountMax(DEF_CHALENGE_MAX);
        this->m_TimerCounter->setTimerMode(TM_COUNT_DOWN);
    }
    else
    {
        //タイムトライアル
        this->m_QuestionCounter->setCountMax(10);
        //99分99秒
        this->m_TimerCounter->setCountMax(5999);
        this->m_TimerCounter->setTimerMode(TM_COUNT_UP);
    }
    
    this->m_TimerCounter->resetCounter();
    this->m_TimerCounter->start();
    
    //問題データ
    CC_SAFE_RELEASE_NULL(this->m_QuestionData);
    this->m_QuestionData = CCArray::createWithContentsOfFile("base/q_data.plist");
    CC_SAFE_RETAIN(this->m_QuestionData);
    
    //記号ボタンの設定
    this->initStageMarker();
    
    //最初の問題を持ってくる
    this->stageInitSet();
    
    //音声ファイル読み込み
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_GAME_OVER);
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_GOOD);
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_RUSH);
    
    return true;
}
/**
 * 記号ボタンの設定
 */
void NumberTenScene::initStageMarker()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    long difficulty = 5;
    
    //記号
    // [+]
    CCMenuItem * kigou = ButtonFactory::createButton(NBT_TASU);
    kigou->setTarget(this, menu_selector(NumberTenScene::onTapButton));
    this->m_buttonMarker->addObject(kigou);
    kigou->setPosition(ccp(size.width / difficulty * 1,size.height * 0.5f + DEF_CENTER_OFFSET_H_BTN_MARK));
    this->m_menu->addChild(kigou);
    // [-]
    kigou = ButtonFactory::createButton(NBT_HIKU);
    kigou->setTarget(this, menu_selector(NumberTenScene::onTapButton));
    this->m_buttonMarker->addObject(kigou);
    kigou->setPosition(ccp(size.width / difficulty * 2,size.height * 0.5f + DEF_CENTER_OFFSET_H_BTN_MARK));
    this->m_menu->addChild(kigou);
    // [*]
    kigou = ButtonFactory::createButton(NBT_KAKERU);
    kigou->setTarget(this, menu_selector(NumberTenScene::onTapButton));
    this->m_buttonMarker->addObject(kigou);
    kigou->setPosition(ccp(size.width / difficulty * 3,size.height * 0.5f + DEF_CENTER_OFFSET_H_BTN_MARK));
    this->m_menu->addChild(kigou);
    // [/]
    kigou = ButtonFactory::createButton(NBT_WARU);
    kigou->setTarget(this, menu_selector(NumberTenScene::onTapButton));
    this->m_buttonMarker->addObject(kigou);
    kigou->setPosition(ccp(size.width / difficulty * 4,size.height * 0.5f + DEF_CENTER_OFFSET_H_BTN_MARK));
    this->m_menu->addChild(kigou);

}
/**
 * ナンバーの初期状態の設定する
 */
void NumberTenScene::stageInitSet()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    //ステージの問題を引っ張ってくる
    CCDictionary* data = dynamic_cast<CCDictionary*>(this->m_QuestionData->randomObject());
    CCString * str = dynamic_cast<CCString*>(data->objectForKey("question"));
    char workMoji[5] = "";
    char moji[5] = "";
    memset(moji, '\0', 5);
    sprintf(workMoji, "%04d", str->intValue());
    
    //並び替え
    long chengeCount = 0;
    while (chengeCount<4)
    {
        long index =rand()%4;
        if(workMoji[index] != '\0')
        {
            moji[chengeCount] = workMoji[index];
            workMoji[index] = '\0';
            chengeCount++;
        }
    }
    char viewMoji[10] = "";
    if(this->m_AnserDigit == 4)
    {
        sprintf(viewMoji, "%c %c %c %c", moji[0],moji[1],moji[2],moji[3]);
    }
    else if(this->m_AnserDigit == 3)
    {
        sprintf(viewMoji, "%c %c %c", moji[0],moji[1],moji[2]);
    }
    
    this->m_QuestionNumber->setString(viewMoji);

    //入力状態を初期化
    this->m_InputNumber->setString("");
    this->m_InputCount = 0;

    CCObject * obj;
    CCARRAY_FOREACH(this->m_buttonNumber, obj)
    {
        CCMenuItem * item = dynamic_cast<CCMenuItemImage*>(obj);
        if(item)item->removeFromParent();
    }
    this->m_buttonNumber->removeAllObjects();
    
    
    //桁数分の表示
    for(long index = 0;index < this->m_AnserDigit ;index++)
    {
        NUMBER_BUTTON_TYPE type;
        switch (moji[index])
        {
            case '0':type = NBT_0;break;
            case '1':type = NBT_1;break;
            case '2':type = NBT_2;break;
            case '3':type = NBT_3;break;
            case '4':type = NBT_4;break;
            case '5':type = NBT_5;break;
            case '6':type = NBT_6;break;
            case '7':type = NBT_7;break;
            case '8':type = NBT_8;break;
            case '9':type = NBT_9;break;
                
            default:
                break;
        }
        
        CCMenuItem * menuItem = ButtonFactory::createButton(type);
        menuItem->setTarget(this, menu_selector(NumberTenScene::onTapButton));
        this->m_menu->addChild(menuItem);
        this->m_buttonNumber->addObject(menuItem);
        
        menuItem->setPosition(ccp( size.width / (this->m_AnserDigit + 1) * (index + 1),
                                  size.height * 0.5f + DEF_CENTER_OFFSET_H_BTN_NUM));
    }

    //押せるボタンの設定
    this->chengePushButtonEnable();

}


/**
 * ボタンのタップ
 */
void NumberTenScene::onTapButton(cocos2d::CCObject* obj)
{
    CCMenuItem * menuItem = dynamic_cast<CCMenuItem*>(obj);
    if(NULL == menuItem)return;
    
    //大丈夫なボダンなら
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_RUSH);
    
    //押されたボタンを記録する
    this->m_AnserType[this->m_InputCount] = static_cast<NUMBER_BUTTON_TYPE>(menuItem->getTag() - NUMBER_TAG_OFFSET);
    
    CCLOG("INPUT %d",this->m_AnserType[this->m_InputCount]);
    
    //次の入力
    if(this->m_AnserType[this->m_InputCount] == NBT_BACK)
    {
        //入力を取り消す
        if(this->m_InputCount>0)
        {
            this->m_InputCount--;
            this->m_usedButtonList->removeObject(this->m_usedButtonList->lastObject());
        }
    }
    else if(this->m_AnserType[this->m_InputCount] == NBT_ENTER)
    {
        //答え合わせをする
        this->checkNumber();
    }
    else
    {
        
        //使用済みボタンとして登録する
        this->m_usedButtonList->addObject(menuItem);
        
        this->m_InputCount++;
    }
    
    //入力文字列を表示する
    char inputMoji[32]= "";
    for(long index = 0 ;index < this->m_InputCount ; index++)
    {
        char inputChar = '\0';
        switch (this->m_AnserType[index])
        {
            case NBT_0:inputChar='0';break;
            case NBT_1:inputChar='1';break;
            case NBT_2:inputChar='2';break;
            case NBT_3:inputChar='3';break;
            case NBT_4:inputChar='4';break;
            case NBT_5:inputChar='5';break;
            case NBT_6:inputChar='6';break;
            case NBT_7:inputChar='7';break;
            case NBT_8:inputChar='8';break;
            case NBT_9:inputChar='9';break;
            case NBT_TASU:inputChar='+';break;
            case NBT_HIKU:inputChar='-';break;
            case NBT_KAKERU:inputChar='*';break;
            case NBT_WARU:inputChar='/';break;
            default:
                break;
        }
        inputMoji[index] = inputChar;
    }
    this->m_InputNumber->setString(inputMoji);
    
    //押せるボタンの設定
    this->chengePushButtonEnable();
}
/**
 * 押せるボタンの設定
 */
void NumberTenScene::chengePushButtonEnable()
{
    CCObject* obj;
    bool number = false;
    bool mark = false;
    
    if(this->m_InputCount != this->m_AnserDigit * 2-1)
    {
        if(this->m_InputCount % 2 == 0)
        {
            //数字入力中
            number = true;
            mark = false;
        }
        else
        {
            //記号入力中
            number = false;
            mark = true;
        }
    }
    
    CCARRAY_FOREACH(this->m_buttonNumber, obj)
    {
        CCMenuItem * menuItem = dynamic_cast<CCMenuItem*>(obj);
        if(menuItem)
        {
            menuItem->setEnabled(number);
            //既に押されていないか検索
            long count = this->m_usedButtonList->count();
            for(long index = 0;index < count ; index++)
            {
                //既に押されている
                if(menuItem == this->m_usedButtonList->objectAtIndex(index))
                {
                    menuItem->setEnabled(false);
                    break;
                }
            }
        }
    }
    CCARRAY_FOREACH(this->m_buttonMarker, obj)
    {
        CCMenuItem * menuItem = dynamic_cast<CCMenuItem*>(obj);
        if(menuItem)
        {
            menuItem->setEnabled(mark);
        }
    }
    
    //バックスペース
    if(this->m_InputCount == 0)
    {
        this->m_buttonBS->setEnabled(false);
    }
    else
    {
        this->m_buttonBS->setEnabled(true);
    }
    
    //エンター
    if(this->m_InputCount == this->m_AnserDigit * 2-1)
    {
        this->m_buttonEnter->setEnabled(true);
    }
    else
    {
        this->m_buttonEnter->setEnabled(false);
    }
}
/**
 * クリアチェック
 */
void NumberTenScene::checkNumber()
{
    long ans = this->m_AnserType[0];
    
    for (long index = 1; index <= this->m_InputCount; index+=2)
    {
        switch(this->m_AnserType[index])
        {
            case NBT_TASU:ans += this->m_AnserType[index+1];break;
            case NBT_HIKU:ans -= this->m_AnserType[index+1];break;
            case NBT_WARU:
                if(this->m_AnserType[index+1] != 0)
                {
                    ans /= this->m_AnserType[index+1];
                }
                else
                {
                    ans = 0;
                }
                break;
            case NBT_KAKERU:ans *= this->m_AnserType[index+1];break;
            default:break;
        }
    }
    
    if(ans == 10)
    {
        CCLOG("正解");
        
        //正解アニメーション
        this->startGoodAnimation();
        
        //次の問題に行く
        this->stageInitSet();
        
        //カウントアップ
        this->m_QuestionCounter->countUp();
        
        //押されたボタンの記憶
        this->m_usedButtonList->removeAllObjects();
        
        //タイマーの設定
        if(GameRuleManager::getInstance()->getGameMode() == GM_CHALENGE)
        {
            this->m_TimerCounter->stop();
            //一定問題数毎に制限時間を減らす
            if(this->m_QuestionCounter->getCounterValue() % DEF_CHALENGE_DOWN_COUNT == 0)
            {
                long max = DEF_CHALENGE_MAX - (DEF_CHALENGE_DOWN_TIME * this->m_QuestionCounter->getCounterValue() / DEF_CHALENGE_DOWN_COUNT);
                if(max < DEF_CHALENGE_DOWN_MIN_TIME)
                {
                    max = DEF_CHALENGE_DOWN_MIN_TIME;
                }
                this->m_TimerCounter->setCountMax(max);
            }
            this->m_TimerCounter->resetCounter();
            this->m_TimerCounter->start();
        }
    }
    else
    {
        CCLOG("失敗");
        
        this->startBadAnimation();
    }
}

/**
 * 正解
 */
void NumberTenScene::startGoodAnimation()
{
    //効果音
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_GOOD);

    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPoint defaultPos = ccp(size.width * 0.5f, size.height * 0.5f + 50.0f);
    
    CCSprite * animeSprite = CCSprite::create("base/good_label.png");
    animeSprite->setPosition(ccpAdd(defaultPos, ccp(0,-100)));
    animeSprite->setOpacity(0);
    this->addChild(animeSprite,1000);
    CCArray * seq1 = CCArray::create();
    CCArray * seq2 = CCArray::create();
    
    seq1->addObject(CCFadeIn::create(0.125f));
    seq1->addObject(CCScaleTo::create(0.125f, 1.15f));
    seq1->addObject(CCScaleTo::create(0.125f, 1.0f));
    
    seq2->addObject(CCMoveTo::create(0.25f, defaultPos));
    seq2->addObject(CCMoveTo::create(0.125f, ccp(defaultPos.x,defaultPos.y - 10) ) );
    seq2->addObject(CCMoveTo::create(0.125f, defaultPos));
    seq2->addObject(CCCallFunc::create(animeSprite, callfunc_selector(CCSprite::removeFromParent)));

    animeSprite->runAction(CCSpawn::createWithTwoActions(CCSequence::create(seq1),
                                                         CCSequence::create(seq2)));
}
/**
 * 失敗
 */
void NumberTenScene::startBadAnimation()
{
    //効果音
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_BAD);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCPoint defaultPos = ccp(size.width * 0.5f, size.height * 0.5f + 50.0f);
    
    CCSprite * animeSprite = CCSprite::create("base/bad_label.png");
    animeSprite->setPosition(ccpAdd(defaultPos, ccp(0,100)));
    animeSprite->setOpacity(0);
    this->addChild(animeSprite,1000);
    
    CCArray * seq1 = CCArray::create();
    CCArray * seq2 = CCArray::create();
    
    seq1->addObject(CCFadeIn::create(0.125f));
    seq1->addObject(CCRotateTo::create(0.125f, 25.0f));
    seq1->addObject(CCFadeOut::create(0.125f));
    
    seq2->addObject(CCMoveTo::create(0.25f, defaultPos));
    seq2->addObject(CCMoveTo::create(0.125f, ccp(defaultPos.x,defaultPos.y + 10) ) );
    seq2->addObject(CCMoveTo::create(0.125f, ccpSub(defaultPos,ccp(0,100))));
    seq2->addObject(CCCallFunc::create(animeSprite, callfunc_selector(CCSprite::removeFromParent)));
    
    animeSprite->runAction(CCSpawn::createWithTwoActions(CCSequence::create(seq1),
                                                         CCSequence::create(seq2)));
}

/**
 * ゲームオーバー
 */
void NumberTenScene::viewGameOverLayer()
{
    //タイマーを停止する
    this->m_TimerCounter->stop();
    
    //全部のボタンを押せなくする
    this->m_menu->setEnabled(false);
    
    GameOverLayer * layer = GameOverLayer::create();
    this->addChild(layer,100000);
    layer->setPosition(CCPointZero);
    
    //スコアの登録
    if(GameRuleManager::getInstance()->getGameMode() == GM_CHALENGE)
    {
        layer->entoryRecord(GameRuleManager::getInstance()->getGameMode(), this->m_QuestionCounter->getCounterValue());
    }
    else
    {
        layer->entoryRecord(GameRuleManager::getInstance()->getGameMode(), this->m_TimerCounter->getCounterValue());
    }
}


