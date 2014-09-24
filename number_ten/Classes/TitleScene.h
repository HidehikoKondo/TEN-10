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
#include "HelpLayer.h"

class TitleScene : public cocos2d::CCLayer
{
protected:
    cocos2d::CCMenu * m_StartMenu;
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(TitleScene);

    void viewHelp();
    void onHelpResult(DIALOG_RESULT ret);
    void NextScene(CCObject*obj);
    void moveSceneToChallenge(CCObject*obj);
    void moveSceneToTimeTrial(CCObject*obj);
    void moveSceneToRanking(CCObject*obj);
    
    /**
     * 問題のチェック
     */
    bool questionCheck(char * nokori_moji,char * question_string);
    
};

#endif /* defined(__TreeTest__TitleScene__) */
