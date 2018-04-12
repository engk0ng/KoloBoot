//
//  RequestController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 11/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "RequestController.h"
#import <vector>
#import "PageRequestController.h"
#import "PageResponseController.h"

@interface RequestController ()
@property (nonatomic, strong) NSMutableArray *controllers;
@property (nonatomic, assign) NSInteger selectedIndex;
@end

@implementation RequestController

- (void)viewDidLoad {
    [super viewDidLoad];
    _controllers = [NSMutableArray array];
    PageRequestController *page1 = [[PageRequestController alloc] init];
    page1.path = _path;
    page1.project = _project;
    PageResponseController *page2 = [[PageResponseController alloc] init];
    page2.path = _path;
    page2.project = _project;
    [_controllers addObject:page1];
    [_controllers addObject:page2];
    self.selectedIndex = 0;
    [self moveToControllerAtIndex:self.selectedIndex animated:YES];
    // Do any additional setup after loading the view from its nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc {
    [_controllers removeAllObjects];
}

#pragma mark - Helper

- (void)moveToControllerAtIndex:(NSInteger)index animated:(BOOL)animated {
    UIViewController *controller = self.controllers[index];
    
    if (controller != nil) {
        // Deselect all the buttons excepting the selected one.
        
        if (self.selectedIndex >= 0) {
            // Remove the current controller's view.
            UIViewController *currentController = self.controllers[self.selectedIndex];
            [currentController.view removeFromSuperview];
        }
        
        if (![self.childViewControllers containsObject:controller]) {
            // If I haven't added the controller to the childs yet...
            [self addChildViewController:controller];
            [controller didMoveToParentViewController:self];
        }
        
        if (NSFoundationVersionNumber <= NSFoundationVersionNumber_iOS_7_1) {
            // Table views have an issue when disabling autoresizing
            // constraints in iOS 7.
            // Their width is set to zero initially and then it's not able to
            // adjust it again, causing constraint conflicts with the cells
            // inside the table.
            // For this reason, we just adjust the frame to the container
            // bounds leaving the autoresizing constraints enabled.
            [self.contentView addSubview:controller.view];
            controller.view.frame = self.contentView.bounds;
        } else {
            controller.view.translatesAutoresizingMaskIntoConstraints = NO;
            [self.contentView addSubview:controller.view];
            [self setupConstraintsForChildController:controller];
        }
        
        _selectedIndex = index;
    }
}

- (void)setupConstraintsForChildController:(UIViewController *)controller {
    NSDictionary *views = @{@"view": controller.view};
    
    NSArray *horizontalConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"H:|[view]|"
                                                                             options:0
                                                                             metrics:nil
                                                                               views:views];
    [self.contentView addConstraints:horizontalConstraints];
    
    NSArray *verticalConstraints = [NSLayoutConstraint constraintsWithVisualFormat:@"V:|[view]|"
                                                                           options:0
                                                                           metrics:nil
                                                                             views:views];
    [self.contentView addConstraints:verticalConstraints];
}

- (IBAction)changePage:(UISegmentedControl *)sender {
    _selectedIndex = sender.selectedSegmentIndex;
    [self moveToControllerAtIndex:_selectedIndex animated:YES];
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
