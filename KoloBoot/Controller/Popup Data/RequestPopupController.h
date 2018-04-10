//
//  RequestPopupController.h
//  KoloBoot
//
//  Created by Abu Muhammad on 10/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface RequestPopupController : UIViewController
@property (nonatomic, weak) IBOutlet UITableView *typeTableView;
- (void)show;
- (void)dismiss;
@end
