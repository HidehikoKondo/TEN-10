//
//  RunkingScene.h
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/07.
//
//

#ifndef __number_ten__RunkingScene__
#define __number_ten__RunkingScene__

#include "cocos2d.h"

class RunkingScene : public cocos2d::CCLayer
{
public:
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    /**
     * コンストラクタ
     */
    RunkingScene();
    /**
     * デストラクタ
     */
    ~RunkingScene();
    
    CREATE_FUNC(RunkingScene);
    
    /**
     * メインメニューに戻る
     */
    void moveToTopScene(cocos2d::CCObject sender);
};

#endif /* defined(__number_ten__RunkingScene__) */
