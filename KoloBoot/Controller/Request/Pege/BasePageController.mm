//
//  BasePageController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 12/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "BasePageController.h"
#import "helper_onc.h"

@interface BasePageController ()

@end

@implementation BasePageController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    /*self.segmentedPager.parallaxHeader.view = self.topView;
    self.segmentedPager.parallaxHeader.mode = MXParallaxHeaderModeFill;
    self.segmentedPager.parallaxHeader.height = 58;
    self.segmentedPager.parallaxHeader.minimumHeight = 5; */
    
    self.segmentedPager.segmentedControl.selectionIndicatorLocation = HMSegmentedControlSelectionIndicatorLocationDown;
    self.segmentedPager.segmentedControl.backgroundColor = NAV_DEFAULT_COLOR;
    self.segmentedPager.segmentedControl.titleTextAttributes = @{NSForegroundColorAttributeName : [UIColor flatGrayColorDark], NSFontAttributeName: [UIFont systemFontOfSize:15]};
    self.segmentedPager.segmentedControl.selectedTitleTextAttributes = @{NSForegroundColorAttributeName : BLUE_DEFAULT, NSFontAttributeName: [UIFont systemFontOfSize:15]};
    self.segmentedPager.segmentedControl.selectionStyle = HMSegmentedControlSelectionStyleFullWidthStripe;
    self.segmentedPager.segmentedControl.selectionIndicatorColor = BLUE_DEFAULT;
    self.segmentedPager.segmentedControl.selectionIndicatorHeight = 2;
    //self.segmentedPager.segmentedControlEdgeInsets = UIEdgeInsetsMake(12, 12, 12, 12);
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillLayoutSubviews {
    self.segmentedPager.frame = (CGRect){
        .origin = CGPointZero,
        .size   = self.view.frame.size
    };
    [super viewWillLayoutSubviews];
}

- (void)settingPralaxHeaderView:(UIView *)vw
                           mode:(MXParallaxHeaderMode)mode
                         height:(CGFloat)height
                      minHeight:(CGFloat)minHeight {

    self.segmentedPager.parallaxHeader.view = vw;
    self.segmentedPager.parallaxHeader.mode = mode;
    self.segmentedPager.parallaxHeader.height = height;
    self.segmentedPager.parallaxHeader.minimumHeight = minHeight;
}

- (MXSegmentedPager *)segmentedPager {
    if (!_segmentedPager) {
        
        // Set a segmented pager below the cover
        _segmentedPager = [[MXSegmentedPager alloc] init];
        _segmentedPager.delegate    = self;
        _segmentedPager.dataSource  = self;
    }
    return _segmentedPager;
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/
@end
