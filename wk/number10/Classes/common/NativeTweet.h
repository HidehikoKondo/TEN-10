//
//  NativeTweet.h
//  number_ten
//
//  Created by 大原幸夫 on 2014/08/24.
//
//

#ifndef number_ten_NativeTweet_h
#define number_ten_NativeTweet_h

class NativeTweet
{
public:
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static void openTweetDialog(const char* tweet);
#else
    static void openTweetDialog(const char* tweet);
#endif
    
};

#endif
