//
//  TreeTestAppController.h
//  TreeTest
//
//  Created by ooharayukio on 2013/12/16.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#import "RootViewController.h"
#import <iAd/iAd.h>


@implementation RootViewController
ADBannerView *adView;
ADBannerView *adView2;

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    // バナービューの作成

}
 

// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsPortrait( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskPortrait;
#endif
}

- (BOOL) shouldAutorotate {
    
    //広告が作られていないときだけ実行。 なんかViewDidloadが呼ばれないので仕方なしにここに書いた。
    if(!adView){
        adView = [[ADBannerView alloc] init];
        adView.frame = CGRectMake(0,self.view.frame.size.height - adView.frame.size.height , adView.frame.size.width, adView.frame.size.height);
        adView.delegate = self;
        adView.autoresizesSubviews = YES;
        adView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleBottomMargin;
        [self.view addSubview:adView];
        [adView setBackgroundColor:[UIColor blackColor]];
        

    }
    return YES;
    
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}


@end
