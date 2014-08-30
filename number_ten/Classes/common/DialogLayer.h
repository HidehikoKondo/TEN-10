//
//  DialogLayer.h
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/27.
//
//

#ifndef __number_ten__DialogLayer__
#define __number_ten__DialogLayer__

#include "cocos2d.h"

typedef enum _DIALOG_STYLE_TYPE
{
    DST_OK,
    DST_YES_NO,
    DST_OK_CANCEL,
}DIALOG_STYLE_TYPE;

typedef enum _DIALOG_RESULT
{
    DRT_OK,
    DRT_CANCEL,
    DRT_YES,
    DRT_NO,
}DIALOG_RESULT;

typedef void (cocos2d::CCObject::*SEL_DialogResult)(DIALOG_RESULT);
#define dialog_result_selecter(_SELECTOR) (SEL_DialogResult)(&_SELECTOR)

class DialogLayer : public cocos2d::CCLayerColor
{
protected:
    cocos2d::CCObject * m_target;
    SEL_DialogResult m_callback;
    
    cocos2d::CCLabelBMFont * m_title;
    cocos2d::CCLabelBMFont * m_description;
    
    cocos2d::CCMenu * m_menu;
    
    cocos2d::CCLayerColor * m_window;
    
    void onTapMenu(cocos2d::CCObject * sender);
    
public:
    DialogLayer();
    virtual ~DialogLayer();
    static DialogLayer * create(const char * title,const char * Description ,DIALOG_STYLE_TYPE type,cocos2d::CCObject* target, SEL_DialogResult callback);
    virtual bool init(const char * title,const char * description ,DIALOG_STYLE_TYPE type,cocos2d::CCObject* target, SEL_DialogResult callback);
};

#endif /* defined(__number_ten__DialogLayer__) */
