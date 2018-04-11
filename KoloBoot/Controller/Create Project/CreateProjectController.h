//
//  CreateProjectController.h
//  KoloBoot
//
//  Created by Abu Muhammad on 03/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <map>
#import <string>
#import "HomeProtocol.h"
#import "Project.hpp"

class DBManager;

@interface CreateProjectController : UIViewController <UITextFieldDelegate>
@property (assign) std::shared_ptr<DBManager> dbase;
@property (weak) id<HomeProtocol> delegate;
@property (nonatomic, weak) IBOutlet UITextField *baseUrlField;
@property (nonatomic, weak) IBOutlet UITextField *nameField;
@property (nonatomic, weak) IBOutlet UIScrollView *scrollView;
@property (nonatomic, weak) IBOutlet UIView *contentView;
@property (nonatomic, assign) Model::Project project;

@end
