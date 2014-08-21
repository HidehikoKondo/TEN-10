//
//  GameOverLayer.h
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/20.
//
//

#ifndef __number_ten__GameOverLayer__
#define __number_ten__GameOverLayer__

#include "cocos2d.h"

class GameOverLayer : public cocos2d::CCLayer
{
protected:
    cocos2d::CCSprite * m_GameOverString;
    
public:
    GameOverLayer();
    virtual ~GameOverLayer();
    
    CREATE_FUNC(GameOverLayer);
    virtual bool init();
    
};
#endif /* defined(__number_ten__GameOverLayer__) */
