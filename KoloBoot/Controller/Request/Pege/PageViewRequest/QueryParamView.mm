//
//  QueryParamView.m
//  KoloBoot
//
//  Created by Abu Muhammad on 11/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "QueryParamView.h"

@implementation QueryParamView

- (void)awakeFromNib {
    [super awakeFromNib];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return _dataParam.size();
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}



@end
