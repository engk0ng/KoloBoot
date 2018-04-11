//
//  ProjectSectionHeaderCell.h
//  KoloBoot
//
//  Created by Abu Muhammad on 10/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ProjectSectionHeaderCell;

@protocol ProjectSectionHeaderCellDelegate <NSObject>
@optional
- (void)showFormInputPathWithCell:(ProjectSectionHeaderCell *)cell;
- (void)showFormUpdateProjectWithCell:(ProjectSectionHeaderCell *)cell;
- (void)showAlertConfirmationDeleteWithCell:(ProjectSectionHeaderCell *)cell;
@end

@interface ProjectSectionHeaderCell : UITableViewCell
@property (weak) id<ProjectSectionHeaderCellDelegate> delegate;
@property (nonatomic, weak) IBOutlet UILabel *projectLbl;
@property (nonatomic, weak) IBOutlet UILabel *baseUrlLbl;
@end
