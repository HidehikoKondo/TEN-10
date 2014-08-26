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

typedef enum _DIALOG_RESULT_TYPE
{
    DRT_OK,
    DRT_CANCEL,
    DRT_YES,
    DRT_NO,
};

class DialogLayer : public cocos2d::CCLayerColor
{
public:
    DialogLayer();
    ~DialogLayer();
    static DialogLayer * create(const char * title,const char * defein ,DIALOG_STYLE_TYPE type);
    virtual bool init(const char * title,const char * defein ,DIALOG_STYLE_TYPE type);
};

#endif /* defined(__number_ten__DialogLayer__) */
