//
//  HelpLayer.cpp
//  number_ten
//
//  Created by ooharayukio on 2014/09/24.
//
//

#include "HelpLayer.h"

USING_NS_CC;

HelpLayer::HelpLayer()
:m_viewImg(NULL)
{
    
}
HelpLayer::~HelpLayer()
{
}

HelpLayer * HelpLayer::create(cocos2d::CCObject* target, SEL_DialogResult callback)
{
    HelpLayer * ret = new HelpLayer();
    if(ret && ret->init(target,callback))
    {
        ret->autorelease();
    }
    else
    {
        delete ret;
        ret = NULL;
    }
    return ret;
}

bool HelpLayer::init(cocos2d::CCObject* target,
                       SEL_DialogResult callback)
{
    if(!CCLayerColor::initWithColor(ccc4(0xF, 0xF, 0xF, 0x7F)))
    {
        return false;
    }
    
    CC_SAFE_RELEASE_NULL(m_target);
    this->m_target = target;
    CC_SAFE_RETAIN(m_target);
    
    this->m_callback = callback;
    
    m_window = CCLayerColor::create(ccc4(0x0,0x2F,0x2F,0xFF), 512, 640);
    this->addChild(m_window);
    m_window->ignoreAnchorPointForPosition(false);
    m_window->setAnchorPoint(ccp(0.5f,0.5f));
    m_window->setPosition(getContentSize().width * 0.5f, getContentSize().height * 0.5f);
    CCSize WinSize = m_window->getContentSize();
    
    this->m_viewImg = CCSprite::create("title/helpViewString.png");
    this->addChild(this->m_viewImg);
    this->m_viewImg->setPosition(ccp(WinSize.width * 0.5f,WinSize.height * 0.5f + 80));
    
    m_menu = CCMenu::create();
    m_menu->setContentSize(m_window->getContentSize());
    m_window->addChild(m_menu);
    m_menu->setPosition(CCPointZero);
    
    CCMenuItemLabel * ok = CCMenuItemLabel::create(
                                                   CCLabelBMFont::create("[OK]", "base/little_number2.fnt",150,
                                                                         kCCTextAlignmentCenter),
                                                   this, menu_selector(HelpLayer::onTapMenu));
    ok->setPosition(ccp(WinSize.width * 0.5f ,40));
    m_menu->addChild(ok);
    
    return true;
}