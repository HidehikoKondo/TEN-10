//
//  ButtonFactory.h
//  number_ten
//
//  Created by 大原幸夫 on 2014/07/12.
//
//

#ifndef __number_ten__ButtonFactory__
#define __number_ten__ButtonFactory__

#include "cocos2d.h"

typedef enum _NUMBER_BUTTON_TYPE
{
    NBT_0,
    NBT_1,
    NBT_2,
    NBT_3,
    NBT_4,
    NBT_5,
    NBT_6,
    NBT_7,
    NBT_8,
    NBT_9,
    NBT_TASU,
    NBT_HIKU,
    NBT_KAKERU,
    NBT_WARU,
    NBT_ENTER,
    NBT_BACK,
}NUMBER_BUTTON_TYPE;

#define NUMBER_TAG_OFFSET (100)

class ButtonFactory : cocos2d::CCObject
{
public:
    static cocos2d::CCMenuItem * createButton(NUMBER_BUTTON_TYPE type);
    
};

#endif /* defined(__number_ten__ButtonFactory__) */
