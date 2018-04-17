//
//  AuthorizationView.m
//  KoloBoot
//
//  Created by Abu Muhammad on 15/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "AuthorizationView.h"

@interface AuthorizationView ()

@end

@implementation AuthorizationView

- (void)viewDidLoad {
    [super viewDidLoad];
    if (_segmentControl.selectedSegmentIndex == 0) {
        [self showAndHideSection:YES];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 2;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (section == 0) {
        return 1;
    }
    else {
        return 3;
    }
}

- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    if (section == 0) {
        return 44;
    }
    else {
        if (_segmentControl.selectedSegmentIndex == 0) {
            return 0.1;
        }
        else {
            return [super tableView:tableView heightForHeaderInSection:section];
        }
    }
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    if (section == 0) {
        return @"Auth";
    }
    else {
        if (_segmentControl.selectedSegmentIndex == 0) {
            return @"";
        }
        else {
            return @"Basic";
        }
    }
}

#pragma mark - Action

- (IBAction)changePageAction:(id)sender {
    if (_segmentControl.selectedSegmentIndex == 0) {
        [self showAndHideSection:YES];
    }
    else {
        [self showAndHideSection:NO];
    }
    [self.tableView reloadData];
}

- (void)showAndHideSection:(BOOL)b {
    NSInteger numSec = [self.tableView numberOfRowsInSection:1];
    for (int i = 0; i < numSec; i++) {
        NSIndexPath *indexPath = [NSIndexPath indexPathForRow:i inSection:1];
        [self.tableView cellForRowAtIndexPath:indexPath].hidden = b;
    }
}

@end
