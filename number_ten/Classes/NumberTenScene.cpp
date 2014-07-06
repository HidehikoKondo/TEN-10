//
//  NumberTenScene.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/07/06.
//
//

#include "NumberTenScene.h"

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
NumberTenScene::NumberTenScene()
:m_StageNo(0)
{
    
}
/**
 * デストラクタ
 */
NumberTenScene::~NumberTenScene()
{
    
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
    
    
    m_InputNumber = CCLabelBMFont::create("5+3+8", "base/view_number.fnt");
    this->addChild(this->m_InputNumber);
    this->m_InputNumber->setPosition(ccp(size.width  * 0.5f , size.height * 0.5f));
    
    return true;
}
/**
 * ナンバーの初期状態の設定する
 */
void NumberTenScene::stageInitSet()
{
    
}

