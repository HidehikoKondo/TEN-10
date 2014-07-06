//
//  ShuttleModel.h
//  rendaPower
//
//  Created by 大原幸夫 on 2014/05/27.
//
//

#ifndef __rendaPower__ShuttleModel__
#define __rendaPower__ShuttleModel__

#include "cocos2d.h"
#include "cocos-ext.h"

class ShuttleModel:public cocos2d::CCNode
{
protected:
    
    cocos2d::CCObject* m_takeoffCallbackTarget;
    cocos2d::SEL_CallFunc m_takeoffCallback;
    
    static const unsigned long CHARGE_ADD;
    static const unsigned long CHARGE_MAX;
    static const unsigned long ACCELERATION;
    static const unsigned long SPEED_MAX;
    static const float ENERGY_CONVERT;
    cocos2d::CCSprite* m_RocketSprite;
    
    cocos2d::CCParticleSmoke * m_smork;

    /**
     * 画面更新
     */
    virtual void update(float delta);

    /**
     * 離陸
     */
    virtual void takeoff();
    
    /**
     * エネルギー消費
     */
    virtual void energyConsumption();
    //
    bool m_runAcceleration;
public:
    ShuttleModel();
    virtual ~ShuttleModel();
    virtual bool init();
    
    CREATE_FUNC(ShuttleModel);
    
    /**
     * エネルギーチャージ
     */
    virtual void chargeEnergy();
    
    /**
     * 値リセット
     */
    virtual void resetParam();
    
    /**
     * 飛び出そう
     */
    virtual void rocketStart(cocos2d::CCObject* takeoffCallbackTarget,cocos2d::SEL_CallFunc takeoffCallback);

    /**
     * 加速
     */
    virtual void acceleration();

    /**
     * 減速
     */
    virtual void slowdown();

    
    CC_SYNTHESIZE(long,m_Energy,Energy);
    CC_SYNTHESIZE(long,m_Speed,Speed);
    
};

#endif /* defined(__rendaPower__ShuttleModel__) */
