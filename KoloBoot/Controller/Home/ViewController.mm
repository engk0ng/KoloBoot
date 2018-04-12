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
#import "AppDelegate.h"
#import <iostream>
#import "helper_oncpp.h"
#import "DBManager.hpp"
#import "ProjectSectionHeaderCell.h"
#import "PathCell.h"
#import "HomeProtocol.h"
#import "PathController.h"
#import "Utils.h"
#import "RequestController.h"

@interface ViewController () <WYPopoverControllerDelegate, HomeProtocol, ProjectSectionHeaderCellDelegate>
@property (nonatomic, strong) WYPopoverController *createProjectController;
@property (nonatomic, assign) std::shared_ptr<DBManager> manager;
@property (nonatomic, strong) UIView *messageView;
@property (nonatomic, assign) DataProject dataProject;
@end

@implementation ViewController

@synthesize createProjectController;
@synthesize manager;

- (void)viewDidLoad {
    [super viewDidLoad];
    manager = std::make_shared<DBManager>();
    auto countProject = manager->countDataProject();
    if (countProject() == 0) {
        _projectTableView.alpha = 0;
        _messageView = [[UIView alloc] initWithFrame:ScreenRect];
        [self.view addSubview:_messageView];
        _messageView.translatesAutoresizingMaskIntoConstraints = NO;
        NSDictionary *vwc = @{@"mw": _messageView};
        [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|[mw]|" options:0 metrics:nil views:vwc]];
        [self.view addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|[mw]|" options:0 metrics:nil views:vwc]];
        [self.view layoutIfNeeded];
        [self settingMessage:@"Tidak ada data project"];
        //[_messageView setBackgroundColor:[UIColor greenColor]];
        //[_messageView bringSubviewToFront:self.view];
    }
    
    [self loadDataProject];
    
    _projectTableView.delegate = self;
    _projectTableView.dataSource = self;
    
    [_projectTableView registerNib:[UINib nibWithNibName:@"ProjectSectionHeaderCell" bundle:nil] forCellReuseIdentifier:@"projectCell"];
    [_projectTableView registerNib:[UINib nibWithNibName:@"PathCell" bundle:nil] forCellReuseIdentifier:@"pathCell"];
    
    _projectTableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    //_dbase = std::make_shared<FirebaseDatabase>(new FirebaseDatabase());
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)settingMessage:(NSString *)msg {
    UILabel *lbl = [[UILabel alloc] initWithFrame:CGRectMake(0, ScreenHeight / 2, ScreenWidth - 16, 35)];
    lbl.textAlignment = NSTextAlignmentCenter;
    [lbl setFont:[UIFont systemFontOfSize:17]];
    [lbl setText:msg];
    [_messageView addSubview:lbl];
    lbl.translatesAutoresizingMaskIntoConstraints = NO;
    NSDictionary *lbvw = @{@"lbl": lbl};
    [_messageView addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-8-[lbl]-8-|" options:0 metrics:nil views:lbvw]];
    [_messageView addConstraint:[NSLayoutConstraint constraintWithItem:lbl attribute:NSLayoutAttributeCenterX relatedBy:NSLayoutRelationEqual toItem:_messageView attribute:NSLayoutAttributeCenterX multiplier:1 constant:0]];
    [_messageView addConstraint:[NSLayoutConstraint constraintWithItem:lbl attribute:NSLayoutAttributeCenterY relatedBy:NSLayoutRelationEqual toItem:_messageView attribute:NSLayoutAttributeCenterY multiplier:1 constant:0]];
    [_messageView layoutIfNeeded];
}

- (void)netralizeFromMessage {
    [_messageView removeFromSuperview];
    [_projectTableView setAlpha:1];
    [_projectTableView reloadData];
}

- (void)loadDataProject {
    auto getAllProject = manager->getAllProject();
    _dataProject = getAllProject();
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)addProjectAction:(id)sender {
    CreateProjectController *settingsViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"CreateProjectController"];
    settingsViewController.delegate = self;
    settingsViewController.dbase = manager;
    settingsViewController.preferredContentSize = CGSizeMake(320, 280);
    
    settingsViewController.title = @"Create Project";
    
    [settingsViewController.navigationItem setRightBarButtonItem:[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(close:)]];
    
    settingsViewController.modalInPopover = NO;
    
    [self settingPopover:settingsViewController];
}

- (void)close:(id)sender
{
    [createProjectController dismissPopoverAnimated:YES completion:^{
        [self popoverControllerDidDismissPopover:createProjectController];
    }];
}

- (void)settingPopover:(UIViewController *)controller {
    UINavigationController *contentViewController = [[UINavigationController alloc] initWithRootViewController:controller];
    
    createProjectController = [[WYPopoverController alloc] initWithContentViewController:contentViewController];
    createProjectController.delegate = self;
    createProjectController.popoverLayoutMargins = UIEdgeInsetsMake(10, 10, 10, 10);
    createProjectController.wantsDefaultContentAppearance = NO;
    
    [createProjectController presentPopoverAsDialogAnimated:YES
                                                    options:WYPopoverAnimationOptionFadeWithScale];
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

#pragma mark - UITableView

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return _dataProject.size();
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _dataProject.at(section).getPaths().size();
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    Model::Project proj = _dataProject.at(section);
    ProjectSectionHeaderCell *cell = [tableView dequeueReusableCellWithIdentifier:@"projectCell"];
    cell.delegate = self;
    cell.tag = section;
    cell.projectLbl.text = [NSString stringWithUTF8String:proj.getName().c_str()];
    cell.baseUrlLbl.text = [NSString stringWithUTF8String:proj.getBaseUrl().c_str()];
    return cell;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    Model::Path path = _dataProject.at(indexPath.section).getPaths().at(indexPath.row);
    PathCell *cell = [tableView dequeueReusableCellWithIdentifier:@"pathCell"];
    cell.pathNameLbl.text = [NSString stringWithUTF8String:path.getName().c_str()];
    cell.pathUrlLbl.text = [NSString stringWithFormat:@"%@ - %@", [NSString stringWithUTF8String:path.getType<std::string>().c_str()], [NSString stringWithUTF8String:path.getPath().c_str()]];
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 57;
}

- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForHeaderInSection:(NSInteger)section {
    return 44;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 55;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    Model::Path path = _dataProject.at(indexPath.section).getPaths().at(indexPath.row);
    RequestController *reqVC = [[RequestController alloc] init];
    std::string judul = "Request - ";
    reqVC.title = [Utils toNSString:judul + path.getName()];
    reqVC.path = path;
    reqVC.project = _dataProject.at(indexPath.section);
    [self.navigationController pushViewController:reqVC animated:YES];
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    Model::Path path = _dataProject.at(indexPath.section).getPaths().at(indexPath.row);
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Konfirmasi" message:[NSString stringWithFormat:@"Apakah anda yakin akan menghapus '%s'?", path.getName().c_str()] preferredStyle:UIAlertControllerStyleAlert];
        [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
            manager->deletePath(path, [&](int res) {
                if (res > 0) {
                    [[AppDelegate sharedAppdelegate] messageNotification:@"Success" description:[NSString stringWithFormat:@"Path Request '%s' berhasil dihapus", path.getName().c_str()] visible:YES delay:4 type:TWMessageBarMessageTypeSuccess errorCode:0];
                    [self refreshDataProject];
                }
                else {
                    [[AppDelegate sharedAppdelegate] messageNotification:@"Error" description:[NSString stringWithFormat:@"Path Request '%s' gagal dihapus", path.getName().c_str()] visible:YES delay:4 type:TWMessageBarMessageTypeError errorCode:0];
                }
            });
        }]];
        [alert addAction:[UIAlertAction actionWithTitle:@"NO" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
            
        }]];
        [self presentViewController:alert animated:YES completion:nil];
    }
}

#pragma mark - CreateProjectControllerDelegate

- (void)refreshDataProject {
    [self netralizeFromMessage];
    [self loadDataProject];
    [_projectTableView reloadData];
}

#pragma mark - ProjectSectionHeaderCellDelegate

- (void)showFormInputPathWithCell:(ProjectSectionHeaderCell *)cell {
    Model::Project proj = _dataProject.at(cell.tag);
    PathController *pathVC = [self.storyboard instantiateViewControllerWithIdentifier:@"PathController"];
    pathVC.preferredContentSize = CGSizeMake(320, 280);
    pathVC.title = [NSString stringWithUTF8String:proj.getName().c_str()];
    pathVC.lastId = proj.getId();
    pathVC.dbase = manager;
    pathVC.delegate = self;
    
    [pathVC.navigationItem setRightBarButtonItem:[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(close:)]];
    
    pathVC.modalInPopover = NO;
    
    [self settingPopover:pathVC];
}

- (void)showFormUpdateProjectWithCell:(ProjectSectionHeaderCell *)cell {
    CreateProjectController *settingsViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"CreateProjectController"];
    settingsViewController.delegate = self;
    settingsViewController.dbase = manager;
    settingsViewController.project = _dataProject.at(cell.tag);
    settingsViewController.preferredContentSize = CGSizeMake(320, 280);
    
    settingsViewController.title = @"Edit Project";
    
    [settingsViewController.navigationItem setRightBarButtonItem:[[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemDone target:self action:@selector(close:)]];
    
    settingsViewController.modalInPopover = NO;
    
    [self settingPopover:settingsViewController];
}

- (void)showAlertConfirmationDeleteWithCell:(ProjectSectionHeaderCell *)cell {
    Model::Project proj = _dataProject.at(cell.tag);
    NSString *str = [NSString stringWithFormat:@"Apakah anda yakin akan menghapus project %@?", [Utils toNSString:proj.getName()]];
    UIAlertController *alertVC = [UIAlertController alertControllerWithTitle:@"Konfirmasi" message:str preferredStyle:UIAlertControllerStyleAlert];
    [alertVC addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        manager->deleteProject(proj, [&](int res){
            if (res > 0) {
                [[AppDelegate sharedAppdelegate] messageNotification:@"Success" description:[NSString stringWithFormat:@"Project '%s' berhasil dihapus", proj.getName().c_str()] visible:YES delay:4 type:TWMessageBarMessageTypeSuccess errorCode:0];
                [self refreshDataProject];
            }
            else {
                [[AppDelegate sharedAppdelegate] messageNotification:@"Error" description:[NSString stringWithFormat:@"Project '%s' gagal dihapus", proj.getName().c_str()] visible:YES delay:4 type:TWMessageBarMessageTypeError errorCode:0];
            }
        });
    }]];
    [alertVC addAction:[UIAlertAction actionWithTitle:@"NO" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        
    }]];
    [self presentViewController:alertVC animated:YES completion:nil];
}

- (void)dealloc {
    _dataProject.clear();
    manager.reset();
}

@end
