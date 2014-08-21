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

    this->m_QuestionCounter = QuestionCounterNode::create();
    this->m_QuestionCounter->setTarget(this, callfunc_selector(NumberTenScene::viewGameOverLayer));
    this->addChild(this->m_QuestionCounter,100);
    
    //ゲームモードによる設定
    if(GM_CHALENGE == GameRuleManager::getInstance()->getGameMode())
    {
        this->m_QuestionCounter->setCountMax(99);
    }
    else
    {
        //タイムトライアル
        this->m_QuestionCounter->setCountMax(10);
    }
    
    //記号ボタンの設定
    this->initStageMarker();
    
    //最初の問題を持ってくる
    this->stageInitSet();
    
    //音声ファイル読み込み
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
    long ans = rand()%9999;
    char moji[5] = "";
    sprintf(moji, "%04ld", ans);
    
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
    
    //使用済みボタンとして登録する
    this->m_usedButtonList->addObject(menuItem);

    //大丈夫なボダンなら
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_RUSH);
    
    //押されたボタンを記録する
    this->m_AnserType[this->m_InputCount] = static_cast<NUMBER_BUTTON_TYPE>(menuItem->getTag() - NUMBER_TAG_OFFSET);
    
    CCLOG("INPUT %d",this->m_AnserType[this->m_InputCount]);
    
    //次の入力
    if(this->m_AnserType[this->m_InputCount] == NBT_BACK)
    {
        //入力を取り消す
        if(this->m_InputCount>0)this->m_InputCount--;
    }
    else if(this->m_AnserType[this->m_InputCount] == NBT_ENTER)
    {
        //答え合わせをする
        this->checkNumber();
    }
    else
    {
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
            case NBT_WARU:ans /= this->m_AnserType[index+1];break;
            case NBT_KAKERU:ans *= this->m_AnserType[index+1];break;
            default:break;
        }
    }
    
    if(ans == 10)
    {
        CCLOG("正解");
        
        //次の問題に行く
        this->stageInitSet();
    }
    else
    {
        CCLOG("失敗");
    }
}

/**
 * ゲームオーバー
 */
void NumberTenScene::viewGameOverLayer()
{
    GameOverLayer * layer = GameOverLayer::create();
    this->addChild(layer,100000);
    layer->setPosition(CCPointZero);
}


