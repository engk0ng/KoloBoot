//
//  QueryParamView.m
//  KoloBoot
//
//  Created by Abu Muhammad on 11/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "QueryParamView.h"
#import "FooterCell.h"
#import "HeaderCell.h"
#import "QueryParamCell.h"
#import "helper_onc.h"
#import "PageRequestController.h"

@interface QueryParamView() <FooterCellDelegate>
@end

@implementation QueryParamView

- (void)awakeFromNib {
    [super awakeFromNib];
    _queryTableView.delegate = self;
    _queryTableView.delegate = self;
    [_queryTableView registerNib:[UINib nibWithNibName:@"QueryParamCell" bundle:nil] forCellReuseIdentifier:@"queryCell"];
    [_queryTableView registerNib:[UINib nibWithNibName:@"FooterCell" bundle:nil] forCellReuseIdentifier:@"footerCell"];
    [_queryTableView registerNib:[UINib nibWithNibName:@"HeaderCell" bundle:nil] forCellReuseIdentifier:@"headerCell"];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _dataParam.size();
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    HeaderCell *cell = [tableView dequeueReusableCellWithIdentifier:@"headerCell"];
    cell.backgroundColor = NAV_DEFAULT_COLOR;
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForHeaderInSection:(NSInteger)section {
    return 44;
}

- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return 44;
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section {
    FooterCell *cell = [tableView dequeueReusableCellWithIdentifier:@"footerCell"];
    cell.delegate = self;
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForFooterInSection:(NSInteger)section {
    return 44;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section {
    return 44;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    QueryParamCell *cell = [tableView dequeueReusableCellWithIdentifier:@"queryCell"];
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

#pragma mark - FooterCellDelegate

- (void)showFormInputParam:(FooterCell *)cell {
    if ([_conntrollerDelegate isKindOfClass:[PageRequestController class]]) {
        PageRequestController *page = (PageRequestController *)_conntrollerDelegate;
        [page presentFormSheetControllerWithTransition:0];
    }
}

@end
