//
//  GameRuleManager.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#include "GameRuleManager.h"

USING_NS_CC;

GameRuleManager::GameRuleManager()
{
    
}
GameRuleManager::~GameRuleManager()
{
    
}

/**
 * シングルトンインスタンス
 */
GameRuleManager * GameRuleManager::getInstance()
{
    static GameRuleManager model;
    return &model;
}

/**
 * ランキングの情報を取得する
 * @return CCArray[CCString] ランキングリスト
 */
cocos2d::CCArray * GameRuleManager::getRankingList(GAME_MODE mode)
{
    CCArray *ret = CCArray::create();
    char buff[256];
    for(int index = 0; index < 10 ; index++)
    {
        sprintf(buff,"ranking_%02d_%02d",mode,index);
        int a = CCUserDefault::sharedUserDefault()->getIntegerForKey(buff, 0);
        ret->addObject(CCString::createWithFormat("%d",a));
    }
    
    return ret;
}

/**
 * ランキングのスコアを登録する
 */
void GameRuleManager::setRankingScore(GAME_MODE mode,long value)
{
    //検索
    int newRecordIndex = 10;
    char buff[256];
    for(int index = 0; index < 10 ; index++)
    {
        sprintf(buff,"ranking_%02d_%02d",mode,index);
        int a = CCUserDefault::sharedUserDefault()->getIntegerForKey(buff, 0);
        if(a < value)
        {
            newRecordIndex = index;
        }
    }

    //書き換え
    int afterScore = value;
    int beforeScore;
    for(int index = newRecordIndex; index < 10 ; index++)
    {
        sprintf(buff,"ranking_%02d_%02d",mode,index);
        beforeScore = CCUserDefault::sharedUserDefault()->getIntegerForKey(buff, 0);
        CCUserDefault::sharedUserDefault()->setIntegerForKey(buff, afterScore);
        afterScore = beforeScore;
    }
}
