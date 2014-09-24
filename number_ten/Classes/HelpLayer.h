//
//  HelpLayer.h
//  number_ten
//
//  Created by ooharayukio on 2014/09/24.
//
//

#ifndef __number_ten__HelpLayer__
#define __number_ten__HelpLayer__

#include "DialogLayer.h"

class HelpLayer : public DialogLayer
{
protected:
    cocos2d::CCSprite * m_viewImg;
public:
    HelpLayer();
    virtual ~HelpLayer();
    static HelpLayer * create(cocos2d::CCObject* target, SEL_DialogResult callback);
    virtual bool init(cocos2d::CCObject* target, SEL_DialogResult callback);
};


#endif /* defined(__number_ten__HelpLayer__) */
