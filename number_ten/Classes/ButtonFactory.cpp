//
//  ButtonFactory.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/07/12.
//
//

#include "ButtonFactory.h"

USING_NS_CC;

cocos2d::CCMenuItem * ButtonFactory::createButton(NUMBER_BUTTON_TYPE type)
{
    //数値のボタンを生成する
    CCMenuItem * ret = NULL;
    switch (type)
    {
        case NBT_0:
            ret = CCMenuItemImage::create(
                                          "button/button_0.png",
                                          "button/button_0_push.png",
                                          "button/button_0_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_1:
            ret = CCMenuItemImage::create(
                                          "button/button_1.png",
                                          "button/button_1_push.png",
                                          "button/button_1_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_2:
            ret = CCMenuItemImage::create(
                                          "button/button_2.png",
                                          "button/button_2_push.png",
                                          "button/button_2_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_3:
            ret = CCMenuItemImage::create(
                                          "button/button_3.png",
                                          "button/button_3_push.png",
                                          "button/button_3_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_4:
            ret = CCMenuItemImage::create(
                                          "button/button_4.png",
                                          "button/button_4_push.png",
                                          "button/button_4_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_5:
            ret = CCMenuItemImage::create(
                                          "button/button_5.png",
                                          "button/button_5_push.png",
                                          "button/button_5_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_6:
            ret = CCMenuItemImage::create(
                                          "button/button_6.png",
                                          "button/button_6_push.png",
                                          "button/button_6_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_7:
            ret = CCMenuItemImage::create(
                                          "button/button_7.png",
                                          "button/button_7_push.png",
                                          "button/button_7_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_8:
            ret = CCMenuItemImage::create(
                                          "button/button_8.png",
                                          "button/button_8_push.png",
                                          "button/button_8_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_9:
            ret = CCMenuItemImage::create(
                                          "button/button_9.png",
                                          "button/button_9_push.png",
                                          "button/button_9_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_TASU:
            ret = CCMenuItemImage::create(
                                          "button/button_tasu.png",
                                          "button/button_tasu_push.png",
                                          "button/button_tasu_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_HIKU:
            ret = CCMenuItemImage::create(
                                          "button/button_hiku.png",
                                          "button/button_hiku_push.png",
                                          "button/button_hiku_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_KAKERU:
            ret = CCMenuItemImage::create(
                                          "button/button_kakeru.png",
                                          "button/button_kakeru_push.png",
                                          "button/button_kakeru_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_WARU:
            ret = CCMenuItemImage::create(
                                          "button/button_waru.png",
                                          "button/button_waru_push.png",
                                          "button/button_waru_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_ENTER:
            ret = CCMenuItemImage::create(
                                          "button/btn_enter.png",
                                          "button/btn_enter_push.png",
                                          "button/btn_enter_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        case NBT_BACK:
            ret = CCMenuItemImage::create(
                                          "button/btn_bs.png",
                                          "button/btn_bs_push.png",
                                          "button/btn_bs_lock.png"
                                          );
            ret->setTag(NUMBER_TAG_OFFSET + type);
            break;
        default:
            break;
    }
    
    return ret;
}
