//
//  GameRuleManager.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#include "GameRuleManager.h"

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

