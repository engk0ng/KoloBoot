//
//  ProgressView.h
//  Jumpr Technologies
//
//  Created by Abu Salman on 25/10/17.
//  Copyright © 2017 KoloBoot. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MBProgressHUD.h"

@interface ProgressView : NSObject
@property (nonatomic, strong) MBProgressHUD *progressHUD;
+ (ProgressView *)Instance;
- (void)showProgressIndicatorInView:(UIView *)view withText:(NSString *)text;
- (void)hideProgressIndicatorInView:(UIView *)view;
- (void)hideProgressIndicator;
@end
