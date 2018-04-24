//
//  BasePageController.h
//  KoloBoot
//
//  Created by KoloBoot on 4/23/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#ifndef BasePageController_h
#define BasePageController_h

#import <UIKit/UIKit.h>
#import <MXSegmentedPager.h>
#import "Path.hpp"
#import "Project.hpp"
#import <Chameleon.h>

@interface BasePageController : UIViewController <MXSegmentedPagerDelegate, MXSegmentedPagerDataSource>
@property (nonatomic, assign) Model::Path path;
@property (nonatomic, assign) Model::Project project;
@property (nonatomic, strong) MXSegmentedPager *segmentedPager;
- (void)settingPralaxHeaderView:(UIView *)vw
                           mode:(MXParallaxHeaderMode)mode
                         height:(CGFloat)height
                      minHeight:(CGFloat)minHeight;
@end


#endif /* BasePageController_h */
