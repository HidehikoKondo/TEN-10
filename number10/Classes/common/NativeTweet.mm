

#include "NativeTweet.h"
#import <Social/Social.h>


//using namespace Cocos2dExt;
void NativeTweet::openTweetDialog(const char *$tweet){
    
    NSString* tweetString = [NSString stringWithUTF8String:$tweet];
//    tweetString = [tweetString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    
    SLComposeViewController *twitterPostVC = [SLComposeViewController composeViewControllerForServiceType:SLServiceTypeTwitter];
    [twitterPostVC setInitialText:[NSString stringWithFormat:@"%@　#udonkonet",tweetString]];
    [twitterPostVC addImage:[UIImage imageNamed:@"icon.png"]];
//    [twitterPostVC addURL:[NSURL URLWithString:APPURL]];
    
    // 処理終了後に呼び出されるコールバックを指定する
    [twitterPostVC setCompletionHandler:^(SLComposeViewControllerResult result) {
        
        switch (result) {
            case SLComposeViewControllerResultDone:
                NSLog(@"Done!!");
//                [NSTimer scheduledTimerWithTimeInterval:0.3f target:self selector:@selector(interstitalAdd:) userInfo:nil repeats:NO];
                break;
            case SLComposeViewControllerResultCancelled:
                NSLog(@"Cancel!!");
//                [NSTimer scheduledTimerWithTimeInterval:0.3f target:self selector:@selector(interstitalAdd:) userInfo:nil repeats:NO];
                break;
        }
    }];
    
    UIViewController *myViewController = [UIApplication sharedApplication].keyWindow.rootViewController;

    [myViewController presentViewController:twitterPostVC animated:YES completion:nil];
}