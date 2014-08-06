//
//  RunkingScene.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#include "RunkingScene.h"

USING_NS_CC;

/**
 * コンストラクタ
 */
RunkingScene::RunkingScene()
{
}
/**
 * デストラクタ
 */
RunkingScene::~RunkingScene()
{
}

CCScene* RunkingScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    RunkingScene *layer = RunkingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RunkingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    return true;
}