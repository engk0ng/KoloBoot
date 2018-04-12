//
//  QueryParamView.h
//  KoloBoot
//
//  Created by Abu Muhammad on 11/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Param.hpp"
#import <vector>

@interface QueryParamView : UIView <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic, weak) IBOutlet UITableView *queryTableView;
@property (nonatomic, assign) std::vector<Model::Param> dataParam;
@end
