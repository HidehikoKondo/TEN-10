//
//  TreeTestAppDelegate.cpp
//  TreeTest
//
//  Created by ooharayukio on 2013/12/16.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "TitleScene.h"
#include "NativeCodeAst.h"
#include "SplashScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    CCEGLView * glView = CCEGLView::sharedOpenGLView();

    
    //アスタ広告
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        AstExt::NativeCodeAst::initAst();
#endif
    
    //プラットフォーム別の設定
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    switch (platform) {
        case cocos2d::kTargetIpad:
            if(glView->getFrameSize().width < glView->getFrameSize().height)
            {
                glView->setDesignResolutionSize(640, 960, kResolutionShowAll);
            }
            else
            {
                glView->setDesignResolutionSize(960, 640, kResolutionShowAll);
            }
            break;

        case cocos2d::kTargetAndroid:
        {
            bool isLong = this->isLongScreen(glView->getFrameSize().width,glView->getFrameSize().height);
            if(glView->getFrameSize().width < glView->getFrameSize().height)
            {

                if(isLong)
                {
                    glView->setDesignResolutionSize(640, 1136, kResolutionShowAll);
                }
                else
                {
                    glView->setDesignResolutionSize(640, 960, kResolutionShowAll);
                }
            }
            else
            {
                if(isLong)
                {
                    glView->setDesignResolutionSize(960, 640, kResolutionShowAll);
                }
                else
                {
                    glView->setDesignResolutionSize(1136, 640, kResolutionShowAll);
                }
            }
        }
        default:
            break;
    }
    
#if COCOS2D_DEBUG
    // turn on display FPS
    pDirector->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCScene *pScene = TitleScene::scene();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCScene *pScene = SplashScene::scene();
#endif

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCDirector::sharedDirector()->stopAnimation();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCDirector::sharedDirector()->pause();
#endif
    
    
#ifndef TARGET_OS_IPHONE
    //スリープすると効果音が鳴らなくなってしまう現象に仮対応
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
#endif
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CCDirector::sharedDirector()->startAnimation();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCDirector::sharedDirector()->resume();
#endif
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

bool AppDelegate::isLongScreen(float w , float h)
{
    float longSize;
    float shortSize;
    if(w < h)
    {
        longSize = h;
        shortSize = w;
    }
    else
    {
        longSize = w;
        shortSize = h;
    }
    
    return (longSize / shortSize) > 1.6f;
}
