//
//  RequestController.h
//  KoloBoot
//
//  Created by Abu Muhammad on 11/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "ViewController.h"
#import "Path.hpp"
#import "Project.hpp"

@interface RequestController : ViewController
@property (nonatomic, assign) Model::Path path;
@property (nonatomic, assign) Model::Project project;
@property (nonatomic, weak) IBOutlet UIView *contentView;
@end
