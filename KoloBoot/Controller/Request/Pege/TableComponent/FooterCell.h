//
//  FooterCell.h
//  KoloBoot
//
//  Created by Abu Muhammad on 12/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>

@class FooterCell;

@protocol FooterCellDelegate <NSObject>
@optional
- (void)showFormInputParam:(FooterCell *)cell;
@end

@interface FooterCell : UITableViewCell
@property (weak) id<FooterCellDelegate> delegate;
- (IBAction)showFormInputParamAction:(id)sender;
@end
