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

    //答えポイント
    CC_SYNTHESIZE(unsigned long, m_AnswerPoint, AnswerPoint);

    //答えポイント加算値
    CC_SYNTHESIZE(unsigned long, m_AnswerAddValue, AnswerAddValue);
    
    //答えポイント減算値
    CC_SYNTHESIZE(unsigned long, m_AnswerSubValue, AnswerSubValue);
public:
    GameRuleManager();
    virtual ~GameRuleManager();
    
    /**
     * 答えポイントの追加
     */
    void addAnswerPoint();
    
    /**
     * 答えポイントの減算
     */
    bool subAnswerPoint();

    /**
     * 答えポイントの減算可能化
     */
    bool isAnswerPointToSub();
    
    /**
     * シングルトンインスタンス
     */
    static GameRuleManager * getInstance();
    
    /**
     * ランキングの情報を取得する
     */
    cocos2d::CCArray * getRankingList(GAME_MODE mode);

    /**
     * ランキングのスコアを登録する
     */
    void setRankingScore(GAME_MODE mode,long value);
    
    /**
     * ランキングの登録がされるか
     */
    bool isNewRecordScore(GAME_MODE mode,long value);

    /**
     * 問題のチェック
     */
    bool questionCheck(char * question_wk ,
                       char * question_write_ptr,
                       char * nokori_moji,
                       double ans = 0,bool first = true);
    
};

#endif /* defined(__number_ten__GameRuleManager__) */
