//
//  ShuttleModel.cpp
//  rendaPower
//
//  Created by 大原幸夫 on 2014/05/27.
//
//

#include "ShuttleModel.h"
#include "SimpleAudioEngine.h"
#include "SoundDef.h"

USING_NS_CC;
using namespace CocosDenshion;

const unsigned long ShuttleModel::CHARGE_ADD = 10;
const unsigned long ShuttleModel::CHARGE_MAX = 1500;
const unsigned long ShuttleModel::ACCELERATION = 2;
const unsigned long ShuttleModel::SPEED_MAX = 15;
const float ShuttleModel::ENERGY_CONVERT = 0.25f;

ShuttleModel::ShuttleModel()
:m_Energy(0)
,m_Speed(0)
,m_RocketSprite(NULL)
,m_runAcceleration(false)
,m_takeoffCallback(NULL)
,m_takeoffCallbackTarget(NULL)
,m_smork(NULL)
{
}

ShuttleModel::~ShuttleModel()
{
    
}

bool ShuttleModel::init()
{
    if(!CCNode::init())
    {
        return false;
    }

    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_TAKEOFF);
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_RUSH);
    SimpleAudioEngine::sharedEngine()->preloadEffect(DEF_SE_ROCKET_READY);
    
    if(this->m_RocketSprite)this->m_RocketSprite->removeFromParent();
    this->m_RocketSprite = CCSprite::create("base/rocket.png");
    this->addChild(this->m_RocketSprite,10);
    
    this->setContentSize(this->m_RocketSprite->getContentSize());
    this->setAnchorPoint(ccp(0.5f,0.5f));
    
    this->m_RocketSprite->setPosition(ccp(this->getContentSize().width * 0.5f,
                                          this->getContentSize().height * 0.5f));

    this->scheduleUpdate();
    
    this->m_smork = CCParticleSmoke::create();
    
    this->m_smork->setTexture(CCTextureCache::sharedTextureCache()->addImage("base/kumo.png"));
    this->m_smork->setAngle(270);
    this->m_smork->setAngleVar(60);
    this->m_smork->setTotalParticles(50);
    this->m_smork->setSpeed(100);
    this->m_smork->setSpeedVar(30);
    this->m_smork->setGravity(ccp(0,50));
    this->m_smork->setSourcePosition(ccp(0, 0));
    this->m_smork->setPosVar(ccp(20,0));
    this->m_smork->setLife(1.5f);
    this->m_smork->setLifeVar(3.0f);
    this->m_smork->setStartSize(50);
    this->m_smork->setEndSize(150);
    this->m_smork->setStartColor(ccc4FFromccc4B(ccc4(0xFF, 0xFF, 0xFF, 0xFF)));
    this->m_smork->setEndColor(ccc4FFromccc4B(ccc4(0x0, 0x0, 0x0, 0x0)));
    this->m_smork->setVisible(false);
    this->m_smork->setPosition(ccpSub(this->m_RocketSprite->getPosition(),ccp(0,this->m_RocketSprite->getContentSize().height * 0.5f)));
    this->addChild(this->m_smork,0);
    return true;
}
/**
 * エネルギーチャージ
 */
void ShuttleModel::chargeEnergy()
{
    if(this->m_Energy < CHARGE_MAX)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_RUSH);
        
        this->m_Energy += CHARGE_ADD;
        if(this->m_Energy > CHARGE_MAX)
        {
            this->m_Energy = CHARGE_MAX;
        }
    }
}

/**
 * 値リセット
 */
void ShuttleModel::resetParam()
{
    this->m_Energy = 0;
    this->m_Speed = 0;
    
    m_runAcceleration = false;
    this->m_smork->setGravity(ccp(0,50));
    this->m_smork->stopSystem();
}
/**
 * 飛び出そう
 */
void ShuttleModel::rocketStart(cocos2d::CCObject* takeoffCallbackTarget,cocos2d::SEL_CallFunc takeoffCallback)
{
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_ROCKET_READY);
    
    //煙吹き出し
    this->m_smork->setVisible(true);
    this->m_smork->resetSystem();

    
    CCArray * shike = CCArray::create();
    for(int index = 0; index < 30; index++)
    {
        shike->addObject(CCMoveBy::create(0.03125f, ccp(10,0)));
        shike->addObject(CCMoveBy::create(0.0625f, ccp(-20,0)));
        shike->addObject(CCMoveBy::create(0.03125f, ccp(10,0)));
    }
    
    shike->addObject(CCCallFunc::create(this, callfunc_selector(ShuttleModel::takeoff)));
    
    this->runAction(CCSequence::create(shike));

    this->m_takeoffCallbackTarget = takeoffCallbackTarget;
    this->m_takeoffCallback = takeoffCallback;
}
/**
 * 離陸
 */
void ShuttleModel::takeoff()
{
    SimpleAudioEngine::sharedEngine()->playEffect(DEF_SE_TAKEOFF);

    this->m_runAcceleration = true;

    this->m_smork->setGravity(ccp(0,0));
    
    if(this->m_takeoffCallbackTarget)
    {
        (this->m_takeoffCallbackTarget->*this->m_takeoffCallback)();
    }
}

/**
 * 加速
 */
void ShuttleModel::acceleration()
{
    if(m_Speed <= SPEED_MAX)
    {
        m_Speed += ACCELERATION;
    }
}

/**
 * 減速
 */
void ShuttleModel::slowdown()
{
    if(m_Speed >= 0)
    {
        m_Speed -= ACCELERATION;
    }
    
    if(m_Speed < 0) m_Speed = 0;
}

/**
 * 画面更新
 */
void ShuttleModel::update(float delta)
{
    CCNode::update(delta);
    
    if(m_runAcceleration)
    {
        
        this->setPosition(ccpAdd(this->getPosition(),ccp(0,m_Speed)));
        //エネルギー消費
        this->energyConsumption();
        if(this->m_Energy > 0)
        {
            this->acceleration();
        }
        else
        {
            if(this->m_smork->isActive())
            {
                this->m_smork->stopSystem();
            }
            
            this->slowdown();
        }
            
    }
    
}

/**
 * エネルギー消費
 */
void ShuttleModel::energyConsumption()
{
    if(this->m_Energy > 0)this->m_Energy -= m_Speed * ENERGY_CONVERT;
    
    if(this->m_Energy < 0)this->m_Energy = 0;
}

