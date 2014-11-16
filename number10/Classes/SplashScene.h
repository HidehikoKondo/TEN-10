//
//  SplashScene.h
//  TreeTest
//
//  Created by ooharayukio on 2013/12/16.
//
//

#ifndef __TreeTest__SplashScene__
#define __TreeTest__SplashScene__

#include "cocos2d.h"

USING_NS_CC;

class SplashScene : public cocos2d::CCLayer
{
protected:
    void nextScene();
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(SplashScene);
};

#endif /* defined(__TreeTest__SplashScene__) */
