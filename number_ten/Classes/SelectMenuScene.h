//
//  SelectMenuScene.h
//  rendaPower
//
//  Created by 大原幸夫 on 2014/02/23.
//
//

#ifndef __rendaPower__SelectMenuScene__
#define __rendaPower__SelectMenuScene__

#include "cocos2d.h"

class SelectMenuScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    /**
     * 選択画面にいく
     */
    void ShuttleScene(CCObject*obj);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(SelectMenuScene);
};

#endif /* defined(__rendaPower__SelectMenuScene__) */
