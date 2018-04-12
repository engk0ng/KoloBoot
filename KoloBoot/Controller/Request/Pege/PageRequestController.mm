//
//  PageRequestController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 11/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "PageRequestController.h"
#import "TopView.h"
#import "QueryParamView.h"
#import "HeadersView.h"
#import "AuthorizationView.h"
#import "Utils.h"

@interface PageRequestController ()
@property (nonatomic, strong) TopView *topView;
@property (nonatomic, strong) QueryParamView *queryView;
@property (nonatomic, strong) HeadersView *headersView;
@property (nonatomic, strong) AuthorizationView *authorizationView;

@end

@implementation PageRequestController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    [self.view addSubview:self.segmentedPager];
    [self settingPralaxHeaderView:self.topView
                             mode:MXParallaxHeaderModeFill
                           height:60
                        minHeight:5];
    self.segmentedPager.bounces = NO;
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (TopView *)topView {
    if (!_topView) {
        _topView = [self.nibBundle loadNibNamed:@"TopView" owner:nil options:nil].firstObject;
        _topView.pathField.text = [Utils toNSString:self.project.getBaseUrl() + self.path.getPath()];
        [_topView.typeBtn setTitle:[Utils toNSString:self.path.getType<std::string>()] forState:UIControlStateNormal];
    }
    return _topView;
}

- (QueryParamView *)queryView {
    if (!_queryView) {
        _queryView = [self.nibBundle loadNibNamed:@"QueryParamView" owner:nil options:nil].firstObject;
    }
    return _queryView;
}

- (HeadersView *)headersView {
    if (!_headersView) {
        _headersView = [self.nibBundle loadNibNamed:@"HeadersView" owner:nil options:nil].firstObject;
    }
    return _headersView;
}

- (AuthorizationView *)authorizationView {
    if (!_authorizationView) {
        _authorizationView = [self.nibBundle loadNibNamed:@"AuthorizationView" owner:nil options:nil].firstObject;
    }
    return _authorizationView;
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
    return 3;
}

- (NSString *)segmentedPager:(MXSegmentedPager *)segmentedPager titleForSectionAtIndex:(NSInteger)index {
    return @[@"QUERY PARAMS", @"HEADERS", @"AUTHORIZATION"][index];
}

- (UIView *)segmentedPager:(MXSegmentedPager *)segmentedPager viewForPageAtIndex:(NSInteger)index {
    return @[self.queryView, self.headersView, self.authorizationView][index];
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
