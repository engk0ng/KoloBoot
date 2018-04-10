//
//  RequestPopupController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 10/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "RequestPopupController.h"
#import "TypeRequestCell.h"
#import <vector>

@interface RequestPopupController () <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic, setter=setWindow:, strong) UIWindow *window;
@property (nonatomic, assign) BOOL firstTimeAppearing;
@property (nonatomic, assign) BOOL firstTimeDismissing;
@property (nonatomic, assign) CGFloat animationDuration;
@property (nonatomic, assign) std::vector<NSString *> typeReq;
@end

@implementation RequestPopupController

@synthesize typeReq;

- (instancetype)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        _animationDuration = 0.15;
        _firstTimeDismissing = YES;
        _firstTimeAppearing = YES;
    }
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    _typeTableView.delegate = self;
    _typeTableView.dataSource = self;
    [_typeTableView registerNib:[UINib nibWithNibName:@"TypeRequestCell" bundle:nil] forCellReuseIdentifier:@"typeCell"];
    _typeTableView.alpha = 0;
    typeReq.push_back(@"GET");
    typeReq.push_back(@"POST");
    typeReq.push_back(@"PUT");
    typeReq.push_back(@"DELETE");
    typeReq.push_back(@"HEAD");
    
    _typeTableView.layer.cornerRadius = 4;
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    if (_firstTimeAppearing) {
        _firstTimeAppearing = NO;
        dispatch_async(dispatch_get_main_queue(), ^{
            [UIView animateWithDuration:_animationDuration delay:0 options:UIViewAnimationCurveEaseInOut animations:^{
                _typeTableView.alpha = 1;
            } completion:^(BOOL finished) {
                
            }];
        });
        
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)show {
    if (_window == nil) {
        UIWindow *winduw = [[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
        winduw.tintColor = [UIColor darkGrayColor];
        winduw.rootViewController = self;
        for (UIWindow *win in [UIApplication sharedApplication].windows) {
            if (winduw.windowLevel < win.windowLevel) {
                winduw.windowLevel = win.windowLevel + 1;
            }
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            [winduw makeKeyAndVisible];
            _window = winduw;
        });
    }
}

- (void)dismiss {
    if (_firstTimeDismissing) {
        dispatch_async(dispatch_get_main_queue(), ^{
            _firstTimeDismissing = NO;
            [UIView animateWithDuration:_animationDuration delay:0 options:UIViewAnimationOptionCurveEaseInOut animations:^{
                _typeTableView.alpha = 0;
            } completion:^(BOOL finished) {
                [_window setHidden:YES];
                _window = nil;
            }];
        });
    }
}

#pragma mark - UITableView

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return typeReq.size();
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    TypeRequestCell *cell = [tableView dequeueReusableCellWithIdentifier:@"typeCell"];
    cell.typeLbl.text = typeReq.at(indexPath.row);
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    [self dismiss];
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
