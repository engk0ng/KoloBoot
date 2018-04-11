//
//  RequestPopupController.h
//  KoloBoot
//
//  Created by Abu Muhammad on 10/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol RequestPopupControllerDelegate <NSObject>
@optional
- (void)sendTypeSelected:(NSString *)txt;
@end

@interface RequestPopupController : UIViewController
@property (weak) id<RequestPopupControllerDelegate> delegate;
@property (nonatomic, weak) IBOutlet UITableView *typeTableView;
- (void)show;
- (void)dismiss;
@end
