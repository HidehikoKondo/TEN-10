//
//  GameRuleManager.h
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#ifndef __number_ten__GameRuleManager__
#define __number_ten__GameRuleManager__

#include "cocos2d.h"

typedef enum _GAME_MODE
{
    GM_CHALENGE,
    GM_TIME_TRIAL
}GAME_MODE;

class GameRuleManager : public cocos2d::CCObject
{
    //ゲームモード
    CC_SYNTHESIZE(GAME_MODE, m_GameMode, GameMode);
    
public:
    GameRuleManager();
    ~GameRuleManager();
    
    /**
     * シングルトンインスタンス
     */
    static GameRuleManager * getInstance();
    
};

#endif /* defined(__number_ten__GameRuleManager__) */