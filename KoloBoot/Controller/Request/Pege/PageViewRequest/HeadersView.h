//
//  HeadersView.h
//  KoloBoot
//
//  Created by Abu Muhammad on 11/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Param.hpp"
#import <vector>

@interface HeadersView : UIView <UITableViewDelegate, UITableViewDataSource>
@property (weak) id conntrollerDelegate;
@property (nonatomic, weak) IBOutlet UITableView *headersTableView;
@property (nonatomic, assign) std::vector<Model::Param> dataParam;
@end
