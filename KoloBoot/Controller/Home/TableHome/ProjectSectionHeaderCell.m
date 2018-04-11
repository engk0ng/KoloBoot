//
//  ProjectSectionHeaderCell.m
//  KoloBoot
//
//  Created by Abu Muhammad on 10/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "ProjectSectionHeaderCell.h"

@implementation ProjectSectionHeaderCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (IBAction)showMenuPathAction:(id)sender {
    if ([_delegate respondsToSelector:@selector(showFormInputPathWithCell:)]) {
        [_delegate showFormInputPathWithCell:self];
    }
}

- (IBAction)showEditProjectAction:(id)sender {
    if ([_delegate respondsToSelector:@selector(showFormUpdateProjectWithCell:)]) {
        [_delegate showFormUpdateProjectWithCell:self];
    }
}

- (IBAction)showAlertForDelete:(id)sender {
    if ([_delegate respondsToSelector:@selector(showAlertConfirmationDeleteWithCell:)]) {
        [_delegate showAlertConfirmationDeleteWithCell:self];
    }
}

@end
