//
//  ViewController.m
//  KoloBoot
//
//  Created by Abu Muhammad on 31/03/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "ViewController.h"
#import "WYPopoverController.h"
#import "CreateProjectController.h"

@interface ViewController () <WYPopoverControllerDelegate>
@property (nonatomic, strong) WYPopoverController *createProjectController;
@end

@implementation ViewController

@synthesize createProjectController;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)addProjectAction:(id)sender {
    CreateProjectController *settingsViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"CreateProjectController"];
    settingsViewController.preferredContentSize = CGSizeMake(320, 280);
    
    settingsViewController.title = @"Create Project";
    
    [settingsViewController.navigationItem setLeftBarButtonItem:[[UIBarButtonItem alloc] initWithTitle:@"Next" style:UIBarButtonItemStylePlain target:self action:@selector(change:)]];
    
    [settingsViewController.navigationItem setRightBarButtonItem:[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(close:)]];
    
    settingsViewController.modalInPopover = NO;
    
    UINavigationController *contentViewController = [[UINavigationController alloc] initWithRootViewController:settingsViewController];
    
    createProjectController = [[WYPopoverController alloc] initWithContentViewController:contentViewController];
    createProjectController.delegate = self;
    createProjectController.popoverLayoutMargins = UIEdgeInsetsMake(10, 10, 10, 10);
    createProjectController.wantsDefaultContentAppearance = NO;
    
    [createProjectController presentPopoverAsDialogAnimated:YES
                                                      options:WYPopoverAnimationOptionFadeWithScale];
}

- (void)close:(id)sender
{
    [createProjectController dismissPopoverAnimated:YES completion:^{
        [self popoverControllerDidDismissPopover:createProjectController];
    }];
}

#pragma mark - WYPopoverControllerDelegate

- (void)popoverControllerDidPresentPopover:(WYPopoverController *)controller
{
    NSLog(@"popoverControllerDidPresentPopover");
}

- (BOOL)popoverControllerShouldDismissPopover:(WYPopoverController *)controller
{
    return YES;
}

- (void)popoverControllerDidDismissPopover:(WYPopoverController *)controller
{
    createProjectController.delegate = nil;
    createProjectController = nil;
}

- (BOOL)popoverControllerShouldIgnoreKeyboardBounds:(WYPopoverController *)popoverController
{
    return YES;
}

- (void)popoverController:(WYPopoverController *)popoverController willTranslatePopoverWithYOffset:(float *)value
{
    // keyboard is shown and the popover will be moved up by 163 pixels for example ( *value = 163 )
    *value = 0; // set value to 0 if you want to avoid the popover to be moved
}

@end
