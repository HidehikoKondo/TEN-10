//
//  DialogLayer.cpp
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/27.
//
//

#include "DialogLayer.h"

USING_NS_CC;

DialogLayer::DialogLayer()
:m_menu(NULL)
,m_description(NULL)
,m_title(NULL)
,m_window(NULL)
,m_target(NULL)
{
    
}
DialogLayer::~DialogLayer()
{
    CC_SAFE_RELEASE_NULL(m_target);
}
DialogLayer * DialogLayer::create(
                                  const char * title,
                                  const char * description,
                                  DIALOG_STYLE_TYPE type,
                                  cocos2d::CCObject* target, SEL_DialogResult callback)
{
    DialogLayer * ret = new DialogLayer();
    if(ret && ret->init(title,description,type,target,callback))
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
bool DialogLayer::init(const char * title,
                       const char * description ,
                       DIALOG_STYLE_TYPE type,
                       cocos2d::CCObject* target,
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
    
    m_window = CCLayerColor::create(ccc4(0x0,0x2F,0x2F,0xFF), 450, 300);
    this->addChild(m_window);
    m_window->ignoreAnchorPointForPosition(false);
    m_window->setAnchorPoint(ccp(0.5f,0.5f));
    m_window->setPosition(getContentSize().width * 0.5f, getContentSize().height * 0.5f);
    CCSize WinSize = m_window->getContentSize();
    
    m_title = CCLabelBMFont::create(title, "base/little_number2.fnt", 300, kCCTextAlignmentCenter);
    m_title->setPosition(WinSize.width * 0.5f,WinSize.height);
    m_window->addChild(m_title);
    m_description = CCLabelBMFont::create(description, "base/little_number2.fnt", 400, kCCTextAlignmentCenter);
    m_description->setPosition(WinSize.width * 0.5f,WinSize.height * 0.5f);
    m_window->addChild(m_description);
    m_menu = CCMenu::create();
    m_menu->setContentSize(m_window->getContentSize());
    m_window->addChild(m_menu);
    m_menu->setPosition(CCPointZero);
    
    switch (type) {
        case DST_YES_NO:
        {
            CCMenuItemLabel * yes = CCMenuItemLabel::create(
                                                            CCLabelBMFont::create("[YES]", "base/little_number2.fnt",150,
                                                                                  kCCTextAlignmentCenter),
                                                            this, menu_selector(DialogLayer::onTapMenu));
            yes->setPosition(ccp(WinSize.width * 0.33f ,40));
            m_menu->addChild(yes);
            CCMenuItemLabel * no = CCMenuItemLabel::create(
                                                            CCLabelBMFont::create("[NO]", "base/little_number2.fnt",150,
                                                                                  kCCTextAlignmentCenter),
                                                            this, menu_selector(DialogLayer::onTapMenu));
            no->setPosition(ccp(WinSize.width * 0.66f ,40));
            m_menu->addChild(no);
            break;
        }
        case DST_OK_CANCEL:
        {
            CCMenuItemLabel * ok = CCMenuItemLabel::create(
                                                            CCLabelBMFont::create("[OK]", "base/little_number2.fnt",150,
                                                                                  kCCTextAlignmentCenter),
                                                            this, menu_selector(DialogLayer::onTapMenu));
            ok->setPosition(ccp(WinSize.width * 0.33f ,40));
            m_menu->addChild(ok);
            CCMenuItemLabel * cancel = CCMenuItemLabel::create(
                                                           CCLabelBMFont::create("[CANCEL]", "base/little_number2.fnt",200,
                                                                                 kCCTextAlignmentCenter),
                                                           this, menu_selector(DialogLayer::onTapMenu));
            cancel->setPosition(ccp(WinSize.width * 0.66f ,40));
            m_menu->addChild(cancel);
            break;
        }
        case DST_OK:
        default:
        {
            CCMenuItemLabel * ok = CCMenuItemLabel::create(
                                                           CCLabelBMFont::create("[OK]", "base/little_number2.fnt",150,
                                                                                 kCCTextAlignmentCenter),
                                                           this, menu_selector(DialogLayer::onTapMenu));
            ok->setPosition(ccp(WinSize.width * 0.5f ,40));
            m_menu->addChild(ok);
            break;
        }    }

    return true;
}

void DialogLayer::onTapMenu(cocos2d::CCObject * sender)
{
    DIALOG_RESULT dr;
    CCMenuItemLabel * label = dynamic_cast<CCMenuItemLabel*>(sender);
    if(label)
    {
        CCLabelBMFont *bm = dynamic_cast<CCLabelBMFont*>(label->getChildren()->objectAtIndex(0));
        if(bm)
        {
            if(strcmp(bm->getString(),"[OK]")==0)
            {
                dr= DRT_OK;
            }
            else if(strcmp(bm->getString(),"[CANCEL]")==0)
            {
                dr= DRT_CANCEL;
            }
            else if(strcmp(bm->getString(),"[YES]")==0)
            {
                dr= DRT_YES;
            }
            else if(strcmp(bm->getString(),"[NO]")==0)
            {
                dr= DRT_NO;
            }
        }
    }
    
    if(m_target)
    {
        (m_target->*m_callback)(dr);
    }
}
