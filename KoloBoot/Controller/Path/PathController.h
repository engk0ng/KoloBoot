//
//  PathController.h
//  KoloBoot
//
//  Created by Abu Muhammad on 08/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <memory>
#import "HomeProtocol.h"

class DBManager;

@interface PathController : UIViewController
@property (assign) std::shared_ptr<DBManager> dbase;
@property (weak) id<HomeProtocol> delegate;
@property (nonatomic, weak) IBOutlet UITextField *namaRequestField;
@property (nonatomic, weak) IBOutlet UITextField *pathField;
@property (nonatomic, weak) IBOutlet UIButton *typeBtn;
@property (nonatomic, assign) int lastId;
@end
