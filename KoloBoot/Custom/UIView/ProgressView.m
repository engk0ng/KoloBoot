//
//  ProgressView.m
//  Jumpr Technologies
//
//  Created by Abu Salman on 25/10/17.
//  Copyright © 2017 KoloBoot. All rights reserved.
//

#import "ProgressView.h"

@implementation ProgressView
@synthesize progressHUD;

static ProgressView *sharedInstance = nil;

+ (ProgressView *)Instance {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}

- (void)showProgressIndicatorInView:(UIView *)view withText:(NSString *)text {
    progressHUD = [MBProgressHUD showHUDAddedTo:view animated:YES];
    progressHUD.label.text = text;
}

- (void)hideProgressIndicatorInView:(UIView *)view {
    [MBProgressHUD hideHUDForView:view animated:YES];
    progressHUD = nil;
}

- (void)hideProgressIndicator {
    progressHUD.hidden = YES;
    progressHUD = nil;
}
@end
