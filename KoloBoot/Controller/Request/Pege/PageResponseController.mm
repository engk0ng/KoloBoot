//
//  PageResponseController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 11/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "PageResponseController.h"
#import "TopResView.h"
#import "ResponseView.h"
#import "ResponseHeaderView.h"

@interface PageResponseController ()
@property (nonatomic, strong) TopResView *topResView;
@property (nonatomic, strong) ResponseView *responseView;
@property (nonatomic, strong) ResponseHeaderView *resHeaderView;
@end

@implementation PageResponseController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    [self.view addSubview:self.segmentedPager];
    [self settingPralaxHeaderView:self.topResView
                             mode:MXParallaxHeaderModeFill
                           height:58
                        minHeight:5];
    self.segmentedPager.bounces = NO;
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (TopResView *)topResView {
    if (!_topResView) {
        _topResView = [self.nibBundle loadNibNamed:@"TopResView" owner:nil options:nil].firstObject;
    }
    return _topResView;
}

- (ResponseView *)responseView {
    if (!_responseView) {
        _responseView = [self.nibBundle loadNibNamed:@"ResponseView" owner:nil options:nil].firstObject;
    }
    return _responseView;
}

- (ResponseHeaderView *)resHeaderView {
    if (!_resHeaderView) {
        _resHeaderView = [self.nibBundle loadNibNamed:@"ResponseHeaderView" owner:nil options:nil].firstObject;
    }
    return _resHeaderView;
}

#pragma mark <MXSegmentedPagerDelegate>

- (CGFloat)heightForSegmentedControlInSegmentedPager:(MXSegmentedPager *)segmentedPager {
    return 40.f;
}

- (void)segmentedPager:(MXSegmentedPager *)segmentedPager didSelectViewWithTitle:(NSString *)title {
    //NSLog(@"%@ page selected.", title);
}

- (void)segmentedPager:(MXSegmentedPager *)segmentedPager didScrollWithParallaxHeader:(MXParallaxHeader *)parallaxHeader {
    //NSLog(@"progress %f", parallaxHeader.progress);
}

#pragma mark <MXSegmentedPagerDataSource>

- (NSInteger)numberOfPagesInSegmentedPager:(MXSegmentedPager *)segmentedPager {
    return 2;
}

- (NSString *)segmentedPager:(MXSegmentedPager *)segmentedPager titleForSectionAtIndex:(NSInteger)index {
    return @[@"RESPONSE", @"HEADERS"][index];
}

- (UIView *)segmentedPager:(MXSegmentedPager *)segmentedPager viewForPageAtIndex:(NSInteger)index {
    return @[self.responseView, self.resHeaderView][index];
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
