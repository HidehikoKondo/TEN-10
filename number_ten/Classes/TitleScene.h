//
//  TitleScene.h
//  TreeTest
//
//  Created by ooharayukio on 2013/12/16.
//
//

#ifndef __TreeTest__TitleScene__
#define __TreeTest__TitleScene__

#include "cocos2d.h"

class TitleScene : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    void NextScene(CCObject*obj);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__TreeTest__TitleScene__) */
