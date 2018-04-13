//
//  PageRequestController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 11/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "PageRequestController.h"
#import "MZFormSheetPresentationViewController.h"
#import "TopView.h"
#import "QueryParamView.h"
#import "HeadersView.h"
#import "AuthorizationView.h"
#import "Utils.h"
#import "InputParamController.h"
#import "MZFormSheetContentSizingNavigationController.h"

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
        _queryView.conntrollerDelegate = self;
    }
    return _queryView;
}

- (HeadersView *)headersView {
    if (!_headersView) {
        _headersView = [self.nibBundle loadNibNamed:@"HeadersView" owner:nil options:nil].firstObject;
        _headersView.conntrollerDelegate = self;
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

#pragma mark - Helper
- (UINavigationController *)formSheetControllerWithNavigationController {
    UIStoryboard *storyboard = [UIStoryboard storyboardWithName:@"Main" bundle:nil];
    InputParamController *inputVC = [storyboard instantiateViewControllerWithIdentifier:@"InputParamController"];
    MZFormSheetContentSizingNavigationController *nav = [[MZFormSheetContentSizingNavigationController alloc] initWithRootViewController:inputVC];
    nav.title = @"Add Value";
    return nav;
}

- (void)presentFormSheetControllerWithTransition:(NSInteger)transition type:(int)tp {
    UINavigationController *navigationController = [self formSheetControllerWithNavigationController];
    MZFormSheetPresentationViewController *formSheetController = [[MZFormSheetPresentationViewController alloc] initWithContentViewController:navigationController];
    formSheetController.presentationController.shouldDismissOnBackgroundViewTap = NO;
    formSheetController.contentViewControllerTransitionStyle = (MZFormSheetPresentationTransitionStyle)transition;
    formSheetController.presentationController.shouldCenterVertically = YES;
    formSheetController.presentationController.movementActionWhenKeyboardAppears = MZFormSheetActionWhenKeyboardAppearsMoveToTopInset;
    UIViewController *controllerPresented = [[navigationController viewControllers] firstObject];
    Model::Param param;
    InputParamController *inputVC = (InputParamController *)controllerPresented;
    inputVC.textFieldBecomeFirstResponder = YES;
    param.setType(tp);
    inputVC.param = param;
    __weak typeof(formSheetController) weakFormSheet = formSheetController;
    formSheetController.presentationController.frameConfigurationHandler = ^CGRect(UIView * _Nonnull presentedView, CGRect currentFrame, BOOL isKeyboardVisible) {
        return CGRectMake(CGRectGetMidX(weakFormSheet.presentationController.containerView.bounds) - (currentFrame.size.width / 2), currentFrame.origin.y, currentFrame.size.width, 190);
    };
    [self presentViewController:formSheetController animated:(transition != MZFormSheetPresentationTransitionStyleNone) completion:nil];
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
