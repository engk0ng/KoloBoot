//
//  UILabel+Extended.m
//  KoloBoot
//
//  Created by Abu Muhammad on 13/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#import "UILabel+Extended.h"

@implementation UILabel (Extended)
- (CGSize)sizeLbl {
    CGSize sizeOfText = [self.text boundingRectWithSize:CGSizeMake(self.bounds.size.width, CGFLOAT_MAX) options:(NSStringDrawingUsesLineFragmentOrigin) attributes:@{NSFontAttributeName: self.font} context:nil].size;
    return sizeOfText;
}
@end
