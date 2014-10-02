//
//  GameRuleManager.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#include "GameRuleManager.h"
#include "AppCCloudPlugin.h"

#define DEF_CHALENGE_LEADER_BOARD   (1108)
#define DEF_TIME_TRIAL_LEADER_BOARD (1109)

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
        if( mode == GM_CHALENGE)
        {
            unsigned long a = CCUserDefault::sharedUserDefault()->getIntegerForKey(buff, 0);
            if( a < value)
            {
                newRecordIndex = index;
                break;
            }
        }
        else if( mode == GM_TIME_TRIAL)
        {
            unsigned long a = CCUserDefault::sharedUserDefault()->getIntegerForKey(buff, ULONG_MAX);
            if( a > value)
            {
                newRecordIndex = index;
                break;
            }
        }
    }
    
    //書き換え
    if(newRecordIndex == 0)
    {
        if(mode == GM_CHALENGE)
        {
            AppCCloudPlugin::Gamers::setLeaderBoard(DEF_CHALENGE_LEADER_BOARD, static_cast<int>(value));
        }
        else if(mode == GM_TIME_TRIAL)
        {
            AppCCloudPlugin::Gamers::setLeaderBoard(DEF_TIME_TRIAL_LEADER_BOARD, static_cast<float>(value));
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
/**
 * ランキングの登録がされるか
 */
bool GameRuleManager::isNewRecordScore(GAME_MODE mode,long value)
{
    bool ret = false;
    char buff[256];
    for(int index = 0; index < 10 ; index++)
    {
        sprintf(buff,"ranking_%02d_%02d",mode,index);
        int a = CCUserDefault::sharedUserDefault()->getIntegerForKey(buff, 0);
        if(a < value)
        {
            ret = true;
            break;
        }
    }
    
    return ret;
}

/**
 * 問題のチェック
 * @note 再起呼び出しによる、問題の作成
 * @param question_wk 回答一例の出力先のポインタ
 * @param question_write_ptr 回答一例の書き出しポインタ
 * @param nokori_moji 残りの問題文字列
 */
bool GameRuleManager::questionCheck(char * question_wk ,char * question_write_ptr,char * nokori_moji,double ans,bool first)
{
    bool ret = false;
    long index = 0;
    
    //取り出す数値が無い場合最後の文字
    if(*nokori_moji == '\0')
    {
        if(ans != 10)
        {
            return false;
        }
        CCLOG("%s OK",question_wk);
        //問題が合っている
        return true;
    }
    
    //残りの数値を全パターンチェックする
    while(nokori_moji[index]!='\0')
    {
        char buff[10] = "";
        if(index > 0)strncpy(buff, nokori_moji, index);
        if(nokori_moji[index+1]!='\0')strcpy(&buff[index], &nokori_moji[index+1]);
        
        double num = nokori_moji[index] - '0';
        //================
        //+
        //================
        double wk = ans + num;
        if(first)
        {
            *(question_write_ptr) = nokori_moji[index];
            ret = this->questionCheck(question_wk,question_write_ptr+1,buff,wk,false);
            if(ret)break;
        }
        else
        {
            *(question_write_ptr) = '+';
            *(question_write_ptr+1) = nokori_moji[index];
            ret = this->questionCheck(question_wk,question_write_ptr+2,buff,wk,false);
            if(ret)break;
        }
        
        //最初の桁の場合足すのみ
        index++;
        if(first)continue;
        
        //================
        //-
        //================
        wk = ans - num;
        *(question_write_ptr) = '-';
        ret = this->questionCheck(question_wk,question_write_ptr+2,buff,wk,false);
        if(ret)break;
        
        //================
        //*
        //================
        wk = ans * num;
        *(question_write_ptr) = '*';
        ret = this->questionCheck(question_wk,question_write_ptr+2,buff,wk,false);
        if(ret)break;
        
        //================
        //÷
        //================
        if(ans != 0 && num != 0)wk = ans / num;
        else wk = 0;
        wk = ans - num;
        *(question_write_ptr) = '/';
        ret = this->questionCheck(question_wk,question_write_ptr+2,buff,wk,false);
        if(ret)break;
        
    }
    
    if(first && ret == false)
    {
        CCLOG("解き方が見つからない: %s",nokori_moji);
    }
    
    return ret;
}


